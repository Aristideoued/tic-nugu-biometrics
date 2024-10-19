#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NBiometrics/NBiometrics.h>
	#include <NMedia/NMedia.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NBiometrics.h>
	#include <NMedia.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("FIRecordFromImage");
const NChar description[] = N_T("Demonstrates creation of FIRecord from image data");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage: %s [FIRecord] [Standard] [Version] [Encoding] {[image]}\n"), title);
	printf(N_T("\tFIRecord - output FIRecord\n"));
	printf(N_T("\t[Standard] - standard for the record (ISO or ANSI)\n"));
	printf(N_T("\t[Version] - version for the record\n"));
	printf(N_T("\t\t 1 - ANSI/INCITS 381-2004\n"));
	printf(N_T("\t\t 1 - ISO/IEC 19794-4:2005\n"));
	printf(N_T("\t\t 2 - ISO/IEC 19794-4:2011\n"));
	printf(N_T("\t\t 2.5 - ANSI/INCITS 381-2009\n"));
	printf(N_T("\t[Encoding] - encoding format\n"));
	printf(N_T("\t\t bin - Traditional binary encoding \n"));
	printf(N_T("\t\t xml - XML encoding (supported only for ISO v2)\n"));
	printf(N_T("\timage    - one or more images\n"));

	return 1;
}

int main(int argc, NChar *argv[])
{
	int i;
	HFIRecord hFIRecord = NULL;
	HFirFingerView hFirFingerView = NULL;
	HNBuffer hImageBuffer = NULL;
	HNBuffer hBuffer = NULL;
	NUShort vertScanResolution = 500;//ppi
	NUShort horzScanResolution = 500;//ppi
	NResult result = N_OK;
	NBool available = NFalse;
	BdifStandard standard = bsIso;
	NVersion standardVersion = FIR_VERSION_ISO_2_0;
	BdifEncodingType encoding = betTraditional;
	BdifFPPosition fPosition = bfppRightThumb;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("FingerClient");
	//const NChar * license = N_T("FingerFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 6)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// TRIAL MODE
	//=========================================================================
	// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
	// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
	// Also you can just set TRUE to "TrialMode" property in code.
	{
		NBool isTrialMode = NFalse;
		result = GetTrialModeFlag(&isTrialMode);
		if (NFailed(result))
		{
			goto FINALLY;
		}
		result = NLicManSetTrialMode(isTrialMode);
		if (NFailed(result))
		{
			goto FINALLY;
		}
		printf(N_T("Trial mode: %d\n"), (int)isTrialMode);
	}
	//=========================================================================

	// check the license first
	result = NLicenseObtain(N_T("/local"), N_T("5000"), license, &available);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseObtain() failed, result = %d\n"), result);
		goto FINALLY;
	}

	if (!available)
	{
		printf(N_T("License %s not available\n"), license);
		result = N_E_NOT_ACTIVATED;
		goto FINALLY;
	}

	if (!strcmp(argv[2], N_T("ANSI")))
	{
		standard = bsAnsi;
	}
	else if (!strcmp(argv[2], N_T("ISO")))
	{
		standard = bsIso;
	}
	else
	{
		printf(N_T("wrong standard!"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	if (!strcmp(argv[3], N_T("1")))
	{
		standardVersion = standard == bsAnsi ? FIR_VERSION_ANSI_1_0 : FIR_VERSION_ISO_1_0;
	}
	else if (!strcmp(argv[3], N_T("2")))
	{
		if (standard != bsIso)
		{
			printf(N_T("standard and version is incompatible!"));
			result = N_E_FAILED;
			goto FINALLY;
		}
		standardVersion = FIR_VERSION_ISO_2_0;
	}
	else if (!strcmp(argv[3], N_T("2.5")))
	{
		if (standard != bsAnsi)
		{
			printf(N_T("standard and version is incompatible!"));
			result = N_E_FAILED;
			goto FINALLY;
		}
		standardVersion = FIR_VERSION_ANSI_2_5;
	}
	else
	{
		printf(N_T("wrong version!"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	if (!strcmp(argv[4], N_T("bin")))
	{
		encoding = betTraditional;
	}
	else if (!strcmp(argv[4], N_T("xml")))
	{
		if (standard != bsIso || standardVersion != FIR_VERSION_ISO_2_0)
		{
			printf(N_T("xml encoding is only availaable for ISO v2.0"));
			result = N_E_FAILED;
			goto FINALLY;
		}
		encoding = betXml;
	}
	else
	{
		printf(N_T("wrong encoding!"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	for (i = 5; i < argc; i++)
	{
		/*	
			Image must be compressed using valid compression algorithm for FIRecord.
			How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
		*/
		result = NFileReadAllBytesCN(argv[i], &hImageBuffer);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in NFileReadAllBytesCN, error code: %d"), result);
			goto FINALLY;
		}

		if (!hFIRecord)
		{
			result = FIRecordCreateFromImageDataN(standard, standardVersion, 10, fPosition, horzScanResolution, vertScanResolution, hImageBuffer, &hFIRecord);
			if(NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("error in FIRecordCreateFromImageDataN, error code: %d\n"), result);
				goto FINALLY;
			}
		}
		else
		{
			result = FIRecordAddFingerViewFromImageDataN(hFIRecord, fPosition, horzScanResolution, vertScanResolution, hImageBuffer, &hFirFingerView);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("error in FIRecordAddFingerViewFromImageDataN, error code: %d\n"), result);
				goto FINALLY;
			}
		}

		result = NObjectSet(NULL, &hImageBuffer);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
			goto FINALLY;
		}

		result = NObjectSet(NULL, &hFirFingerView);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
			goto FINALLY;
		}
	}

	result = FIRecordSaveToMemoryN(hFIRecord, encoding, 0, &hBuffer);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NObjectSaveToMemoryN, error code: %d\n"), result);
		goto FINALLY;
	}

	result = NFileWriteAllBytesCN(argv[1], hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFileWriteAllBytesCN, error code: %d\n"), result);
		goto FINALLY;
	}

	printf(N_T("FIRecord successfully saved to file %s\n"), argv[1]);

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hImageBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFIRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFirFingerView);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	OnExit();
	return result;
}
