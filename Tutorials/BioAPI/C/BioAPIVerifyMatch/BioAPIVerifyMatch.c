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

void BioAPI_GetPrintableUUID(const BioAPI_UUID * pUUID,
		NChar * PrintableUUID)
{
	/* Format the output */
	sprintf(PrintableUUID, 
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

void BioAPI_GetPrintableVersion(const BioAPI_VERSION * pVersion,
		NChar * PrintableVersion)
{
	/* format the output: any minor version number other than 0 will format as two chars
	   ie. 1.01 rather than 1.1, which is easily confused with 1.10 */
	if ((*pVersion) & 0x0f)
		sprintf(PrintableVersion, N_T("%d.%02d"), ((*pVersion) & 0xf0)>>4, (*pVersion) & 0x0f);
	else
		sprintf(PrintableVersion, N_T("%d.%d"), ((*pVersion) & 0xf0)>>4, (*pVersion) & 0x0f);
}

int BioAPI_GetStructuredUUID(const NChar * PrintableUUID,
		BioAPI_UUID * pUUID)
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

	/* Copy the integers into the chars */
	for (nCount = 0; nCount < 16; nCount ++)
	{
		pbUUID[nCount] = (uint8_t)tempUUID[nCount];
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

static const NChar gs_title[] = N_T("Neurotechnology BioAPI VerifyMatch tutorial 5.1\n");

int print_usage(NChar * argv[])
{
	printf(N_T("Usage: %s <bsp module Uuid> <Processing Unit ID> <Matching Unit ID> <template1 fname> <template2 fname>\n"), argv[0]);
	printf(N_T("\t<bsp module Uuid> - the Uuid of the BSP module to attach\n"));
	printf(N_T("\t<Processor UnitID> - Numeric Unit ID value. Refer to BioAPI2.0 specs for more info\n"));
	printf(N_T("\t<Matching UnitID> - Numeric Unit ID value. Refer to BioAPI2.0 specs for more info\n"));
	printf(N_T("\t<template1 fname>,<template2 fname> - the file names of template file to match\n"));
	printf(N_T("Description:\n"));
	printf(N_T("This tutorial uses BioAPI to verify single BIR against reference BIR.\n"));
	printf(N_T("Saved files are serialized BioAPI_BIR structures.\n"));
	printf(N_T("\nUuid is of following format: {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}\n"));
	printf(N_T("\nPossible UnitID values:\n"));
	printf(N_T("  0\tBioAPI_DONT_CARE\n"));
	printf(N_T("  -1\tBioAPI_DONT_INCLUDE\n"));
	printf(N_T("  any positive value of unit id\n"));
	printf(N_T("\nExample:\n"));
	printf(N_T("%s {AD1BC423-E3C2-4eed-B5DB-1C4A53170ED6} 0 0 for_verification.bir reference.bir\n"), argv[0]);
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
			printf (N_T("Framework UUID: %s\n"), printableUUID);
			PrintBioAPIString(N_T("Description: "), FrameworkSchema.FwDescription);
			PrintBioAPIString(N_T("Module path: "), FrameworkSchema.Path);

			BioAPI_GetPrintableVersion(&FrameworkSchema.SpecVersion, printableVersion);
			printf (N_T("BioAPI Specification version: %s\n"), printableVersion);

			PrintBioAPIString(N_T("Product Version: "), FrameworkSchema.ProductVersion);
			PrintBioAPIString(N_T("Vendor: "), FrameworkSchema.Vendor);
			BioAPI_GetPrintableUUID(&FrameworkSchema.FwPropertyId, printableUUID);
			printf (N_T("Property UUID: %s\n"), printableUUID);
			//BioAPI_DATA FwProperty;       // Address and length of a memory buffer containing the Framework property..
			BioAPI_Free(FrameworkSchema.Path);
			BioAPI_Free(FrameworkSchema.FwProperty.Data);
		}
	}

	return bioReturn;
}

BioAPI_RETURN load_BSP(NChar * uuidString, NChar * unitidString1, NChar * unitidString2, BioAPI_HANDLE * hBSP, BioAPI_UUID * BSP_uuid)
{
	BioAPI_RETURN bioReturn;
	BioAPI_UNIT_LIST_ELEMENT units[2] = 
	{
		{BioAPI_CATEGORY_PROCESSING_ALG, BioAPI_DONT_CARE},
		{BioAPI_CATEGORY_MATCHING_ALG, BioAPI_DONT_CARE},
	}; 

	NChar printableUUID[40];

	BioAPI_GetStructuredUUID(uuidString, BSP_uuid);
	BioAPI_GetPrintableUUID(BSP_uuid, printableUUID);

	units[0].UnitId = atoi(unitidString1);
	units[1].UnitId = atoi(unitidString2);

	printf(N_T("\nLoading BSP, Uuid=%s\n"), printableUUID);
	printf(N_T("\nLoading BSP, Processing UnitID=%d\n"), units[0].UnitId);
	printf(N_T("\nLoading BSP, Matching UnitID=%d\n"), units[1].UnitId);

	bioReturn = BioAPI_BSPLoad(BSP_uuid, Bio_EventHandler, NULL);
	if ( bioReturn == BioAPI_OK )
	{
		printf(N_T("Waiting 1s...\n")); // let's wait so that every unit insert itself
		Sleep(1000);
		printf(N_T("Attaching loaded BSP...\n"));

		bioReturn = BioAPI_BSPAttach(BSP_uuid, (BioAPI_MAJOR << 4) | BioAPI_MINOR, units, 2, hBSP);
		if (bioReturn != BioAPI_OK)
		{
			BioAPI_BSPUnload(BSP_uuid, Bio_EventHandler, NULL);
			BioAPI_Terminate();
		}
	}

	return bioReturn;
}

int ReadTemplate(FILE * fp, BioAPI_BIR * BIR)
{
	fread(&BIR->Header, sizeof(BIR->Header), 1, fp);
	fread(&BIR->BiometricData.Length, sizeof(BIR->BiometricData.Length), 1, fp);
	fread(&BIR->SecurityBlock.Length, sizeof(BIR->SecurityBlock.Length), 1, fp);

	if (NFailed(NAlloc(BIR->BiometricData.Length, &BIR->BiometricData.Data)))
	{
		printf(N_T("Memory error occoured\n"));
		return -1;
	}
	if (NFailed(NAlloc(BIR->SecurityBlock.Length, &BIR->SecurityBlock.Data)))
	{
		printf(N_T("Memory error occoured\n"));
		NFree(BIR->BiometricData.Data);
		BIR->BiometricData.Data = NULL;
		return -1;
	}

	fread(BIR->BiometricData.Data, BIR->BiometricData.Length, 1, fp);
	fread(BIR->SecurityBlock.Data, BIR->SecurityBlock.Length, 1, fp);

	return 0;
}

int main(int argc, NChar * argv[])
{
	BioAPI_HANDLE hBSP;
	BioAPI_RETURN bioReturn;
	BioAPI_UUID BSP_uuid;

	printf(gs_title);
	if (argc < 6)
	{
		return print_usage(argv);
	}

	bioReturn = init_framework();
	if (BioAPI_OK == bioReturn) 
	{
		bioReturn = load_BSP(argv[1], argv[2], argv[3], &hBSP, &BSP_uuid);
		if (bioReturn == BioAPI_OK)
		{
			// The maximum False Match Rate that is acceptable for the application. 
			// We specify something around 33% of acceptance (max value / 3).
			BioAPI_FMR  MaxFMRRequested = 0x7fffffff / 7;
			BioAPI_BOOL verified = BioAPI_FALSE; // The result of verification
			BioAPI_FMR FMRAchieved = 0; // Actual FAR for the Verify operations
			BioAPI_INPUT_BIR birTemplate1; // The biometric template to compare with
			BioAPI_INPUT_BIR birTemplate2; // The biometric template to compare with
			FILE *fp;
			BioAPI_BIR BIR1 = {0,};
			BioAPI_BIR BIR2 = {0,};
			BioAPI_BIR_HANDLE hbirProcessed1;
			BioAPI_BIR_HANDLE hbirProcessed2;

			printf (N_T("Loading 1st templates...\n"));
			fopen_s(&fp, argv[4], N_T("rb"));
			if (fp)
			{
				if (ReadTemplate(fp, &BIR1) < 0)
				{
					bioReturn = BioAPIERR_MEMORY_ERROR;
				}
				fclose(fp);
			}
			else
			{
				printf(N_T("Could not load input template\n"));
				bioReturn = BioAPIERR_INTERNAL_ERROR;
			}

			if (bioReturn == BioAPI_OK)
			{
				printf(N_T("Loading 2nd template...\n"));
				fopen_s(&fp, argv[5], N_T("rb"));
				if (fp)
				{
					if (ReadTemplate(fp, &BIR2) < 0)
					{
						bioReturn = BioAPIERR_MEMORY_ERROR;
					}
					fclose(fp);
				}
				else
				{
					printf(N_T("Could not load input template\n"));
					bioReturn = BioAPIERR_INTERNAL_ERROR;
				}

				if (bioReturn == N_OK)
				{
					birTemplate1.InputBIR.BIR = &BIR1;
					birTemplate1.Form = BioAPI_FULLBIR_INPUT;
					birTemplate2.InputBIR.BIR = &BIR2;
					birTemplate2.Form = BioAPI_FULLBIR_INPUT;

					if (BIR1.Header.Type & BioAPI_BIR_DATA_TYPE_INTERMEDIATE)
					{
						printf(N_T("Processing 1...\n"));
						bioReturn = BioAPI_Process(hBSP, &birTemplate1, NULL, &hbirProcessed1);
						birTemplate1.Form = BioAPI_BIR_HANDLE_INPUT;
						birTemplate1.InputBIR.BIRinBSP = &hbirProcessed1;
						NFree(BIR1.BiometricData.Data);
						NFree(BIR1.SecurityBlock.Data);
						BIR1.BiometricData.Data = NULL;
						BIR1.SecurityBlock.Data = NULL;
					}

					if (bioReturn == BioAPI_OK && BIR2.Header.Type & BioAPI_BIR_DATA_TYPE_INTERMEDIATE)
					{
						printf(N_T("Processing 2...\n"));
						bioReturn = BioAPI_Process(hBSP, &birTemplate2, NULL, &hbirProcessed2);
						birTemplate2.Form = BioAPI_BIR_HANDLE_INPUT;
						birTemplate2.InputBIR.BIRinBSP = &hbirProcessed2;
						NFree(BIR2.BiometricData.Data);
						NFree(BIR2.SecurityBlock.Data);
						BIR2.BiometricData.Data = NULL;
						BIR2.SecurityBlock.Data = NULL;
					}
				}
			}

			if (bioReturn == BioAPI_OK) 
			{
				printf(N_T("Verifying...\n"));
				bioReturn = BioAPI_VerifyMatch(hBSP, MaxFMRRequested, &birTemplate1, &birTemplate2, 
									NULL, &verified, &FMRAchieved, NULL);
			
			
				NFree(BIR1.BiometricData.Data);
				NFree(BIR1.SecurityBlock.Data);
				NFree(BIR2.BiometricData.Data);
				NFree(BIR2.SecurityBlock.Data);
			}
			else
				printf(N_T("processing failed...\n"));

			if (bioReturn == BioAPI_OK)
			{
				if (verified)
					printf(N_T("Verification succeeded, FMR: %d / %d\n"), FMRAchieved, MaxFMRRequested);
				else
					printf(N_T("Verification failed, FMR: %d / %d\n"), FMRAchieved, MaxFMRRequested);
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
