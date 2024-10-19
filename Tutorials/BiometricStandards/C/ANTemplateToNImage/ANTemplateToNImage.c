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

const NChar title[] = N_T("ANTemplateToNImage");
const NChar description[] = N_T("Demonstrates how to save images stored in ANTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2009-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [ANTemplate]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tANTemplate - filename of ANTemplate\n"));

	return 1;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	NBool available = NFalse;
	HANTemplate hTemplate = NULL;
	HANRecord hRecord = NULL;
	HANRecordType hRecordType = NULL;
	HNImage hImage = NULL;
	NInt recordNumber;
	NInt count;
	NInt i;
	NBool isValid;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * licenses = N_T("FingerClient,PalmClient,FaceClient,IrisClient");
	//const NChar * licenses = N_T("FingerFastExtractor,PalmClient,FaceFastExtractor,IrisFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 2)
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
	result = NLicenseObtain(N_T("/local"), N_T("5000"), licenses, &available);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseObtain() failed, result = %d\n"), result);
		goto FINALLY;
	}

	if (!available)
	{
		printf(N_T("Licenses %s not available\n"), licenses);
		result = N_E_NOT_ACTIVATED;
		goto FINALLY;
	}

	result = ANTemplateCreateFromFileEx2(argv[1], 0, &hTemplate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("ANTemplateCreateFromFileEx2() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = ANTemplateIsValidated(hTemplate, &isValid);
	if (!isValid)
	{
		result = PrintErrorMsg(N_T("ANSI/NIST template is not valid"), N_E_FAILED);
		goto FINALLY;
	}

	result = ANTemplateGetRecordCount(hTemplate, &count);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("ANTemplateGetRecordCount() failed, result = %d\n"), result);
		goto FINALLY;
	}

	for (i = 0; i < count; i++)
	{
		NChar szFileName[1024];

		result = ANTemplateGetRecordEx(hTemplate, i, &hRecord);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("ANTemplateGetRecord() failed, result = %d\n"), result);
			goto FINALLY;
		}

		result = ANRecordGetRecordTypeEx(hRecord, &hRecordType);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("ANRecordGetRecordTypeEx() failed, result = %d\n"), result);
			goto FINALLY;
		}

		result = ANRecordTypeGetNumber(hRecordType, &recordNumber);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("ANRecordTypeGetNumber() failed, result = %d\n"), result);
			goto FINALLY;
		}

		if (recordNumber >= 3 && recordNumber <= 8 && recordNumber != 7)
		{
			result = ANImageBinaryRecordToNImage((HANImageBinaryRecord)hRecord, 0, &hImage);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("ANImageBinaryRecordToNImage() failed, result = %d\n"), result);
				goto FINALLY;
			}
		}
		else if (recordNumber >= 10 && recordNumber <= 17)
		{
			result = ANImageAsciiBinaryRecordToNImage((HANImageAsciiBinaryRecord)hRecord, 0, &hImage);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("ANImageAsciiBinaryRecordToNImage() failed, result = %d\n"), result);
				goto FINALLY;
			}
		}

		if (hImage)
		{
			sprintf(szFileName, N_T("record%d_type%d.jpg"), i + 1, recordNumber);
			result = NImageSaveToFileEx(hImage, szFileName, NULL, NULL, 0);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("NImageSaveToFileEx() failed, result = %d\n"), result);
				goto FINALLY;
			}
			printf(N_T("image saved to %s\n"), szFileName);
		}

		// free hRecord
		result = NObjectSet(NULL, &hRecord);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
			goto FINALLY;
		}

		// free hRecordType
		result = NObjectSet(NULL, &hRecordType);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
			goto FINALLY;
		}

		// free hImage
		result = NObjectSet(NULL, &hImage);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
			goto FINALLY;
		}
	}
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hImage);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hRecordType);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hTemplate);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	OnExit();
	return result;
}
