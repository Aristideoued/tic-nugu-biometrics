#include <TutorialUtils.h>

#include <NCore.h>
#include <bioapi.h>

#define BioAPI_PRINTABLE_UUID_LENGTH	(40)
#define BioAPI_PRINTABLE_VERSION_LENGTH	( 8 )
#define BioAPI_UUID_FORMAT_STRING		N_T("{%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x}")

#define UNIT_ID 0

BioAPI_RETURN BioAPI Bio_EventHandler(const BioAPI_UUID * BSPUuid,
					BioAPI_UNIT_ID UnitId,
					void * AppNotifyCallbackCtx, // the main windows handle
					const BioAPI_UNIT_SCHEMA * UnitSchema,
					BioAPI_EVENT eventType);

void BioAPI_GetPrintableUUID(const BioAPI_UUID * pUUID, NChar * PrintableUUID)
{
	/* Format the output */
	sprintf( PrintableUUID, 
			 BioAPI_UUID_FORMAT_STRING,
			 (*pUUID)[0], (*pUUID)[1], (*pUUID)[2], (*pUUID)[3],
			 (*pUUID)[4], (*pUUID)[5],
			 (*pUUID)[6], (*pUUID)[7],
			 (*pUUID)[8], (*pUUID)[9],
			 (*pUUID)[10],
			 (*pUUID)[11],
			 (*pUUID)[12],
			 (*pUUID)[13],
			 (*pUUID)[14],
			 (*pUUID)[15]);
}

void BioAPI_GetPrintableVersion(const BioAPI_VERSION * pVersion, NChar * PrintableVersion)
{
	/* format the output: any minor version number other than 0 will format as two chars
	   ie. 1.01 rather than 1.1, which is easily confused with 1.10 */
	if ((*pVersion) & 0x0f)
		sprintf( PrintableVersion, N_T("%d.%02d"), ((*pVersion) & 0xf0) >> 4, (*pVersion) & 0x0f);
	else
		sprintf( PrintableVersion, N_T("%d.%d"), ((*pVersion) & 0xf0) >> 4, (*pVersion) & 0x0f);
}

int BioAPI_GetStructuredUUID(const NChar * PrintableUUID, BioAPI_UUID * pUUID)
{
	int nCount;
	int tempUUID[16];
	uint8_t *pbUUID = (uint8_t *)pUUID;

	/* Scan the input into a temporary integer array */
	nCount = sscanf(PrintableUUID, 
					 BioAPI_UUID_FORMAT_STRING,
					 &(tempUUID)[0], &(tempUUID)[1], &(tempUUID)[2], &(tempUUID)[3],
					 &(tempUUID)[4], &(tempUUID)[5],
					 &(tempUUID)[6], &(tempUUID)[7],
					 &(tempUUID)[8], &(tempUUID)[9],
					 &(tempUUID)[10],
					 &(tempUUID)[11],
					 &(tempUUID)[12],
					 &(tempUUID)[13],
					 &(tempUUID)[14],
					 &(tempUUID)[15]);

	if (nCount != 16)
	{
		printf(N_T("Invalid BioAPI UUID data\n"));
		return -1;
	}

	/* Copy integers into chars */
	for (nCount = 0; nCount < 16; nCount++)
	{
		pbUUID[nCount] = (uint8_t) tempUUID[nCount];
	}

	return 0;
}

void PrintBioAPIString(const NChar * Str, BioAPI_STRING bioapiString)
{
#ifdef N_UNICODE
	NChar Str1[sizeof(BioAPI_STRING) + 1] = N_T("\0");
	mbstowcs(Str1, (char *)bioapiString, sizeof(BioAPI_STRING));
	printf(N_T("%s%s\n"), Str, Str1);
#else
	printf(N_T("%s%s\n"), Str, biapiString);
#endif
}

static const NChar gs_title[] = N_T("Neurotechnology BioAPI Capture tutorial 5.1\n");

int print_usage(NChar * argv[])
{
	printf(N_T("Usage: %s <bsp module Uuid> <Sensor Unit ID> <Purpose ID> <template fname>\n"), argv[0]);
	printf(N_T("\t<bsp module Uuid> - the Uuid of the BSP module to attach\n"));
	printf(N_T("\t<Sensor UnitID> - Numeric Unit ID value. Refer to BioAPI2.0 specs for more info\n"));
	printf(N_T("\t<Purpose ID> - Numeric Purpose ID value. Refer to BioAPI2.0 specs for more info\n"));
	printf(N_T("\t<template fname> - the file name of template file to save the template to\n"));
	printf(N_T("Description:\n"));
	printf(N_T("This tutorial uses BioAPI to capture single BIR for specified purpose,\n"));
	printf(N_T("then it saves captured BIR to specified file.\n"));
	printf(N_T("Saved file is a serialized BioAPI_BIR structure.\n"));
	printf(N_T("\nUuid is of following format: {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}\n"));
	printf(N_T("\nPossible PurposeID values and corresponding BioAPI names:\n"));
	printf(N_T("  0\tBioAPI_NO_PURPOSE_AVAILABLE\n"));
	printf(N_T("  1\tBioAPI_PURPOSE_VERIFY\n"));
	printf(N_T("  2\tBioAPI_PURPOSE_IDENTIFY\n"));
	printf(N_T("  3\tBioAPI_PURPOSE_ENROLL\n"));
	printf(N_T("  4\tBioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY\n"));
	printf(N_T("  5\tBioAPI_PURPOSE_ENROLL_FOR_IDENTIFICATION_ONLY\n"));
	printf(N_T("  6\tBioAPI_PURPOSE_AUDIT\n"));
	printf(N_T("\nPossible UnitID values:\n"));
	printf(N_T("  0\tBioAPI_DONT_CARE\n"));
	printf(N_T("  -1\tBioAPI_DONT_INCLUDE\n"));
	printf(N_T("  any positive value\n"));
	printf(N_T("\nExamples:\n"));
	printf(N_T("%s {AD1BC423-E3C2-4eed-B5DB-1C4A53170ED6} 0 2 for_identification.bir\n"), argv[0]);
	printf(N_T("%s {AD1BC423-E3C2-4eed-B5DB-1C4A53170ED6} 0 1 for_verification.bir\n"), argv[0]);
	printf(N_T("%s {AD1BC423-E3C2-4eed-B5DB-1C4A53170ED6} 0 4 reference.bir\n"), argv[0]);

	return 1;
}

BioAPI_RETURN init_framework()
{
	BioAPI_VERSION bioVersion;
	BioAPI_RETURN bioReturn;

	bioVersion = (BioAPI_VERSION)((BioAPI_MAJOR << 4) | BioAPI_MINOR);
	bioReturn = BioAPI_Init(bioVersion);

	if(BioAPI_OK != bioReturn)
	{
		if(BioAPIERR_INCOMPATIBLE_VERSION == bioReturn)
		{
			printf(N_T("This application is not compatible with the installed version of BioAPI\n"));
		}
		else
		{
			printf(N_T("BioAPI Error Code: %d\n"), bioReturn);
		}
	}
	else
	{
		BioAPI_FRAMEWORK_SCHEMA FrameworkSchema;

		printf(N_T("BioAPI initialization succeeded\n"));

		bioReturn = BioAPI_GetFrameworkInfo(&FrameworkSchema);
		if(BioAPI_OK == bioReturn)
		{
			NChar printableUUID[BioAPI_PRINTABLE_UUID_LENGTH];
			NChar printableVersion[BioAPI_PRINTABLE_VERSION_LENGTH];

			BioAPI_GetPrintableUUID(&FrameworkSchema.FrameworkUuid, printableUUID);
			printf(N_T("Framework UUID: %s\n"), printableUUID);
			PrintBioAPIString(N_T("Description: "), FrameworkSchema.FwDescription);
			PrintBioAPIString(N_T("Module path: "), FrameworkSchema.Path);

			BioAPI_GetPrintableVersion(&FrameworkSchema.SpecVersion, printableVersion);
			printf (N_T("BioAPI Specification version: %s\n"), printableVersion);

			PrintBioAPIString(N_T("Product Version: "), FrameworkSchema.ProductVersion);
			PrintBioAPIString(N_T("Vendor: "), FrameworkSchema.Vendor);
			BioAPI_GetPrintableUUID(&FrameworkSchema.FwPropertyId, printableUUID);
			printf (N_T("Property UUID: %s\n"), printableUUID);
			BioAPI_Free(FrameworkSchema.Path);
			BioAPI_Free(FrameworkSchema.FwProperty.Data);
		}
	}

	return bioReturn;
}

BioAPI_RETURN load_BSP(NChar * uuidString, NChar * unitidString, BioAPI_HANDLE * hBSP, BioAPI_UUID * BSP_uuid)
{
	BioAPI_RETURN bioReturn;
	BioAPI_UNIT_LIST_ELEMENT units[1] = 
	{
		{BioAPI_CATEGORY_SENSOR, BioAPI_DONT_CARE}
	}; 

	NChar printableUUID[40];

	BioAPI_GetStructuredUUID(uuidString, BSP_uuid);
	BioAPI_GetPrintableUUID(BSP_uuid, printableUUID);

	units[0].UnitId = atoi(unitidString);

	printf(N_T("\nLoading BSP, Uuid=%s\n"), printableUUID);
	printf(N_T("\nLoading BSP, UnitID=%d\n"), units[0].UnitId);
	bioReturn = BioAPI_BSPLoad(BSP_uuid, Bio_EventHandler, NULL);
	if (bioReturn == BioAPI_OK)
	{
		printf(N_T("Waiting 1s...\n")); 
		Sleep(1000);	// let's wait so that every unit insert itself
		printf(N_T("Attaching loaded BSP...\n"));

		bioReturn = BioAPI_BSPAttach(BSP_uuid, (BioAPI_MAJOR << 4) | BioAPI_MINOR, units, 1, hBSP);
		if (bioReturn != BioAPI_OK)
		{
			BioAPI_BSPUnload(BSP_uuid, Bio_EventHandler, NULL);
		}
	}

	return bioReturn;
}

int main(int argc, NChar * argv[])
{
	BioAPI_HANDLE hBSP;
	BioAPI_BIR_HANDLE hbirTemplate;
	BioAPI_RETURN bioReturn;
	BioAPI_UUID BSP_uuid;

	printf(gs_title);
	if (argc < 5)
	{
		return print_usage(argv);
	}

	bioReturn = init_framework();
	if (BioAPI_OK == bioReturn) 
	{
		bioReturn = load_BSP(argv[1], argv[2], &hBSP, &BSP_uuid);
		if (bioReturn == BioAPI_OK)
		{

			printf(N_T("Capture...\n"));
			bioReturn = BioAPI_Capture(hBSP, (BioAPI_BIR_PURPOSE)atoi(argv[3]), BioAPI_NO_SUBTYPE_AVAILABLE, NULL,
							&hbirTemplate, -1, NULL);
			if (bioReturn == BioAPI_OK)
			{
				FILE *fp = NULL;
				BioAPI_BIR BIR;

				BioAPI_GetBIRFromHandle(hBSP, hbirTemplate, &BIR); // invalidates hbirTemplate handle

				printf(N_T("Captured template quality: %d\n"), BIR.Header.Quality);

				fopen_s(&fp, argv[5], N_T("wb"));
				if (fp)
				{

					fwrite(&BIR.Header, sizeof(BIR.Header), 1, fp);
					fwrite(&BIR.BiometricData.Length, sizeof(BIR.BiometricData.Length), 1, fp);
					fwrite(&BIR.SecurityBlock.Length, sizeof(BIR.SecurityBlock.Length), 1, fp);

					fwrite(BIR.BiometricData.Data, BIR.BiometricData.Length, 1, fp);
					fwrite(BIR.SecurityBlock.Data, BIR.SecurityBlock.Length, 1, fp);

					fclose(fp);

					BioAPI_Free(BIR.BiometricData.Data);
					BioAPI_Free(BIR.SecurityBlock.Data);
				}
				else
				{
					if (argc > 1)
						printf(N_T("could not save %s\n"), argv[1]);
					else
						printf(N_T("could not save template.bir\n"));
				}
			}

			printf(N_T("Detaching BSP\n"));
			BioAPI_BSPDetach(hBSP);
			printf(N_T("Unloading BSP\n"));
			BioAPI_BSPUnload(&BSP_uuid, Bio_EventHandler, NULL);
		}
	}

	if(BioAPI_OK != bioReturn)
	{
		printf(N_T("BioAPI Error Code: %d\n"), bioReturn);
	}

	BioAPI_Terminate();

	return bioReturn;
}

// Application's module event handler. Being called by loaded BSPs to notify
// about unit events, i.e. attachment of a unit for biometric operations.
// This event handler can be called either syncronously (i.e. during ModuleLoad)
// or asynchronously on a separate thread. Keep this in mind when communicating 
// with the GUI thread/objects for proper sysncronization and objects passing.
BioAPI_RETURN BioAPI Bio_EventHandler(const BioAPI_UUID * BSPUuid,
					BioAPI_UNIT_ID UnitId,
					void * AppNotifyCallbackCtx, // the main windows handle
					const BioAPI_UNIT_SCHEMA * UnitSchema,
					BioAPI_EVENT  eventType)
{
	// to display event types as user friendly strings 
	const NChar *szEvents[] = {	(N_T("unknown")),
							(N_T("BioAPI_NOTIFY_INSERT")),
							(N_T("BioAPI_NOTIFY_REMOVE")),
							(N_T("BioAPI_NOTIFY_FAULT")),
							(N_T("BioAPI_NOTIFY_SOURCE_PRESENT")),
							(N_T("BioAPI_NOTIFY_SOURCE_REMOVED"))};

	printf(N_T("%d, BSP event received (unit=%d, event=%s)\n"), GetCurrentThreadId(), UnitId, 
						eventType < 6 ? szEvents[eventType] : N_T("unknown") ) ;
	
	switch (eventType)
	{
		case BioAPI_NOTIFY_INSERT:

			// add new units only

			break;

		case BioAPI_NOTIFY_REMOVE:

			// we assume that no Attach should exist for the removed unit, 
			// hence just remove it from the list and don't call any Detach here

			break;

		default:
			;
	}

	BSPUuid;
	AppNotifyCallbackCtx;
	UnitSchema;
	return BioAPI_OK;
}
