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

const NChar title[] = N_T("ANTemplateToNTemplate");
const NChar description[] = N_T("Demonstrates ANTemplate conversion to NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2009-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [ANTemplate] [NTemplate]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tANTemplate - filename with ANTemplate\n"));
	printf(N_T("\tNTemplate  - filename for NTemplate\n"));
	printf(N_T("example:\n"));
	printf(N_T("\t%s anTemplate.ANTemplate template.NTemplate\n"), title);

	return 1;
}

NResult ANTemplateFileToPackedNTemplate(
	NChar * szFileName, // pointer to string that specifies name of file were ANTemplate is stored
	HNBuffer * hBuffer // packed NTemplate buffer
)
{
	HANTemplate hANTemplate = NULL; // handle to ANTemplate object
	HNTemplate hNTemplate = NULL; // handle to NTemplate object
	NResult result;
	NBool isValid;

	// Create ANTemplate object from file
	result = ANTemplateCreateFromFileEx2(szFileName, 0, &hANTemplate);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateCreateFromFileEx2, error code: %d\n"), result);
		goto FINALLY;
	}

	result = ANTemplateIsValidated(hANTemplate, &isValid);
	if (!isValid)
	{
		result = PrintErrorMsg(N_T("ANSI/NIST template is not valid"), N_E_FAILED);
		goto FINALLY;
	}

	// Convert ANTemplate object to NTemplate object
	result = ANTemplateToNTemplate(hANTemplate, 0, &hNTemplate);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateToNTemplate, error code: %d\n"), result);
		goto FINALLY;
	}

	// Pack NTemplate object
	result = NObjectSaveToMemoryN(hNTemplate, 0, hBuffer);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NObjectSaveToMemoryN, error code: %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hANTemplate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hNTemplate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
	}

	return result;
}

int main(int argc, NChar **argv)
{
	HNBuffer hBuffer = NULL;
	NResult result = N_OK;
	NBool available = NFalse;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("FingerClient");
	//const NChar * license = N_T("FingerFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 3)
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

	result = ANTemplateFileToPackedNTemplate(argv[1], &hBuffer);
	if (NFailed(result))
	{
		goto FINALLY;
	}

	result = NFileWriteAllBytesCN(argv[2], hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFileWriteAllBytesCN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hBuffer);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
	}

	OnExit();
	return result;
}
