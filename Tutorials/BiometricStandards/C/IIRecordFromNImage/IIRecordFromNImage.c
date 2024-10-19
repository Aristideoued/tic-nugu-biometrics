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

const NChar title[] = N_T("IIRecordFromNImage");
const NChar description[] = N_T("Demonstrates creation of IIRecord from image");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage: %s [IIRecord] [Standard] [Version] {[image...]}\n"), title);
	printf(N_T("\tIIRecord - output IIRecord\n"));
	printf(N_T("\t[Standard] - standard for the record (ISO or ANSI)\n"));
	printf(N_T("\t[Version] - version for the record\n"));
	printf(N_T("\t\t 1 - ANSI/INCITS 379-2004\n"));
	printf(N_T("\t\t 1 - ISO/IEC 19794-6:2005n"));
	printf(N_T("\t\t 2 - ISO/IEC 19794-6:2011\n"));
	printf(N_T("\timage    - one or more images\n"));
	return 1;
}

int main(int argc, NChar *argv[])
{
	HIIRecord hIIRecord = NULL;
	HIirIrisImage hIrisImage = NULL;
	HNBuffer hImageBuffer = NULL;
	HNBuffer hBuffer = NULL;
	NInt i;
	NResult result = N_OK;
	NBool available = NFalse;
	BdifStandard standard = bsIso;
	NVersion standardVersion = IIR_VERSION_ISO_2_0;
	BdifEyePosition position = bepLeft;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("IrisClient");
	//const NChar * license = N_T("IrisFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 5)
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
		standardVersion = standard == bsAnsi ? IIR_VERSION_ANSI_1_0 : IIR_VERSION_ISO_1_0;
	}
	else if (!strcmp(argv[3], N_T("2")))
	{
		if (standard != bsIso)
		{
			printf(N_T("standard and version is incompatible!"));
			result = N_E_FAILED;
			goto FINALLY;
		}
		standardVersion = IIR_VERSION_ISO_2_0;
	}
	else
	{
		printf(N_T("wrong version!"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	for (i = 4; i < argc; i++)
	{
		/*
			Image must be compressed using valid compression algorithm for IIRecord.
			How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
		*/
		result = NFileReadAllBytesCN(argv[i], &hImageBuffer);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in NFileReadAllBytesCN, error code: %d"), result);
			goto FINALLY;
		}

		if (!hIIRecord)
		{
			result = IIRecordCreateFromImageDataN(standard, standardVersion, position, hImageBuffer, &hIIRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("error in IIRecordCreateFromImageDataN, error code: %d\n"), result);
				goto FINALLY;
			}
		}
		else
		{
			result = IIRecordAddIrisImageFromImageDataN(hIIRecord, position, hImageBuffer, &hIrisImage);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("error in IIRecordAddIrisImageFromImageDataN, error code: %d\n"), result);
				goto FINALLY;
			}
		}

		result = NObjectSet(NULL, &hImageBuffer);
		if NFailed((result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
			goto FINALLY;
		}

		result = NObjectSet(NULL, &hIrisImage);
		if NFailed((result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
			goto FINALLY;
		}
	}

	result = NObjectSaveToMemoryN(hIIRecord, 0, &hBuffer);
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

	printf(N_T("IIRecord successfully saved to file %s\n"), argv[1]);

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hImageBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hIIRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hIrisImage);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	OnExit();
	return result;
}
