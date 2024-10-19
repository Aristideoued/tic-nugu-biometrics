#include <TutorialUtils.h>

#include <NCore.h>
#include <bioapi.h>

#define BioAPI_PRINTABLE_UUID_LENGTH	(40)
#define BioAPI_PRINTABLE_VERSION_LENGTH	( 8 )
#define BioAPI_UUID_FORMAT_STRING		N_T("{%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x}")

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

static const NChar gs_title[] = N_T("Neurotechnology BioAPI Info tutorial 5.1\n");
static const NChar gs_description[] = N_T("Description: this tutorial shows how to obtain information about \n")
		N_T("BioAPI framework and installed BSPs and BFPs.\n");

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

int main(int argc, NChar * argv[])
{
	NChar printableUUID[BioAPI_PRINTABLE_UUID_LENGTH];
	NChar printableVersion[BioAPI_PRINTABLE_UUID_LENGTH];
	uint32_t i, j, numElements, numElementsUnits;
	BioAPI_BSP_SCHEMA *sSchema;
	BioAPI_BFP_SCHEMA *fSchema;
	BioAPI_UNIT_SCHEMA *uSchema;
	BioAPI_RETURN bioReturn;

	printf(gs_title);
	printf(gs_description);

	bioReturn = init_framework();
	if (BioAPI_OK == bioReturn) 
	{
		printf(N_T("\nEnumerating BSPs:\n"));
		bioReturn = BioAPI_EnumBSPs(&sSchema, &numElements);
		if(BioAPI_OK == bioReturn)
		{
			for (i = 0; i < numElements; i++)
			{
				BioAPI_GetPrintableUUID(&sSchema[i].BSPUuid, printableUUID);
				printf(N_T("  BSP UUID: %s\n"), printableUUID);

				PrintBioAPIString(N_T("  Description: "), sSchema[i].BSPDescription);
				PrintBioAPIString(N_T("  Module path: "), sSchema[i].Path);
				BioAPI_Free(sSchema[i].Path);

				BioAPI_GetPrintableVersion(&sSchema[i].SpecVersion, printableVersion);
				printf(N_T("  BSP Specification version: %s\n"), printableVersion);

				PrintBioAPIString(N_T("  Product version: "), sSchema[i].ProductVersion);
				PrintBioAPIString(N_T("  Vendor: "), sSchema[i].Vendor);

				printf(N_T("  Supported formats:\n"));
				for (j = 0; j < sSchema[i].NumSupportedFormats; j++)
				{
					printf(N_T("    {Owner: %i, Type %i}\n"),
						(int) sSchema[i].BSPSupportedFormats[j].FormatOwner,
						(int) sSchema[i].BSPSupportedFormats[j].FormatType);
				}
				BioAPI_Free(sSchema[i].BSPSupportedFormats);

				printf(N_T("  Factors Mask: %08x\n"), sSchema[i].FactorsMask);
				printf(N_T("  Operations: %08x\n"), sSchema[i].Operations);
				printf(N_T("  Options: %08x\n"), sSchema[i].Options);
				printf(N_T("  Payload Policy: %08x\n"), sSchema[i].PayloadPolicy);
				printf(N_T("  Max Payload size: %d\n"), sSchema[i].MaxPayloadSize);
				printf(N_T("  Default verify timeout: %d\n"), sSchema[i].DefaultVerifyTimeout);
				printf(N_T("  Default identify timeout: %d\n"), sSchema[i].DefaultIdentifyTimeout);
				printf(N_T("  Default Capture timeout: %d\n"), sSchema[i].DefaultCaptureTimeout);
				printf(N_T("  Default Enroll timeout: %d\n"), sSchema[i].DefaultEnrollTimeout);
				printf(N_T("  Default Calibrate timeout: %d\n"), sSchema[i].DefaultCalibrateTimeout);
				printf(N_T("  Max BSP Db Size: %d\n"), sSchema[i].MaxBSPDbSize);
				printf(N_T("  Max Identity: %d\n"), sSchema[i].MaxIdentify);
				printf(N_T("Supported units:\n"));

				printf(N_T("  Loading BSP...\n"));
				bioReturn = BioAPI_BSPLoad(&sSchema[i].BSPUuid, NULL, NULL);
				if (BioAPI_OK == bioReturn)
				{
					Sleep(3000);
					bioReturn = BioAPI_QueryUnits(&sSchema[i].BSPUuid, &uSchema, &numElementsUnits);
					if (BioAPI_OK == bioReturn)
					{
						for (j = 0; j < numElementsUnits; j++)
						{
							printf(N_T(" UnitId: %d\n"), (int)uSchema[j].UnitId);
							BioAPI_GetPrintableUUID(&uSchema[j].UnitManagerUuid, printableUUID);
							printf(N_T("  Unit manager Id: %s\n"), printableUUID);
							printf(N_T("  Unit category: %d\n"), uSchema[j].UnitCategory);
							BioAPI_GetPrintableUUID(&uSchema[j].UnitProperties, printableUUID);
							printf(N_T("  Unit properties: %s\n"), printableUUID); 
							PrintBioAPIString(N_T("  Vendor information: "), uSchema[j].VendorInformation);
							printf(N_T("  Supported events: %08x\n"), uSchema[j].SupportedEvents);
							BioAPI_GetPrintableUUID(&uSchema[j].UnitPropertyID, printableUUID);
							printf(N_T("  Unit property Id: %s\n"), printableUUID);
							if (uSchema[j].UnitProperty.Data != NULL)
							{
								BioAPI_Free(uSchema[j].UnitProperty.Data);
							}
							PrintBioAPIString(N_T("  Hardware version: "), uSchema[j].HardwareVersion);
							PrintBioAPIString(N_T("  Firmware version: "), uSchema[j].FirmwareVersion);
							PrintBioAPIString(N_T("  Software version: "), uSchema[j].SoftwareVersion);
							PrintBioAPIString(N_T("  Hardware serial number: "), uSchema[j].HardwareSerialNumber);
							printf(N_T("  Authenticated hardware: %s\n"), uSchema[j].AuthenticatedHardware ? N_T("True") : N_T("False"));
							printf(N_T("  Max Db size: %d\n"), uSchema[j].MaxBSPDbSize);
							printf(N_T("  Max Identify population size: %d\n"), uSchema[j].MaxIdentify);
						}

						if (numElementsUnits == 0)
						{
							printf(N_T("  empty\n"));
						}

						BioAPI_Free(uSchema);
						BioAPI_BSPUnload(&sSchema[i].BSPUuid, NULL, NULL);
					}
					else
					{
						printf(N_T("  error\n"));
					}
				}
				else
				{
					printf(N_T("  error\n"));
				}

				printf(N_T("\n"));
			}
			if (numElements == 0)
			{
				printf(N_T("  empty\n"));
			}
			BioAPI_Free(sSchema);
		}

		printf(N_T("\nEnumerating BFPs:\n"));
		bioReturn = BioAPI_EnumBFPs(&fSchema, &numElements);
		if(BioAPI_OK == bioReturn)
		{
			for (i = 0; i < numElements; i++)
			{
				BioAPI_GetPrintableUUID(&fSchema[i].BFPUuid, printableUUID);
				printf(N_T("  BFP UUID: %s\n"), printableUUID);
				printf(N_T("  Description: %hs\n"), fSchema[i].BFPDescription); 
				printf(N_T("  Module path: %hs\n"), fSchema[i].Path); 
				BioAPI_Free(fSchema[i].Path);

				BioAPI_GetPrintableVersion(&fSchema[i].SpecVersion, printableVersion);
				printf(N_T("  BFP Specification version: %s\n"), printableVersion);

				printf(N_T("  Product version: %hs\n"), fSchema[i].ProductVersion);
				printf(N_T("  Vendor: %hs\n"), fSchema[i].Vendor);

				printf(N_T("  Supported formats:\n"));
				for (j = 0; j < fSchema[i].NumSupportedFormats; j++)
				{
					printf(N_T("    {Owner: %i, Type %i}\n"),
						(int) fSchema[i].BFPSupportedFormats[j].FormatOwner,
						(int) fSchema[i].BFPSupportedFormats[j].FormatType);
				}

				BioAPI_Free(fSchema[i].BFPSupportedFormats);
				printf(N_T("  Factors Mask: %08x\n"), fSchema[i].FactorsMask);
				BioAPI_GetPrintableUUID(&fSchema[i].BFPPropertyID, printableUUID);
				printf(N_T("  Property UUID: %s\n"), printableUUID);
				printf(N_T("\n"));
				BioAPI_Free(fSchema[i].BFPProperty.Data);
			}
			if (numElements == 0)
			{
				printf(N_T("  empty\n"));
			}
			BioAPI_Free(fSchema);
		}
	}

	if(BioAPI_OK != bioReturn)
	{
		printf(N_T("BioAPI Error Code: %d\n"), bioReturn);
	}

	BioAPI_Terminate();

	argv;
	argc;
	return bioReturn;
}

