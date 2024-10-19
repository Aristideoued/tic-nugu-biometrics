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

const NChar title[] = N_T("NTemplateToANTemplate");
const NChar description[] = N_T("Demonstrates creation of ANTemplate from NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2009-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [NTemplate] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tNTemplate   - filename with NTemplate\n"));
	printf(N_T("\tANTemplate  - filename for NTemplate\n"));
	printf(N_T("\tTot - specifies type of transaction\n"));
	printf(N_T("\tDai - specifies destination agency identifier\n"));
	printf(N_T("\tOri - specifies originating agency identifier\n"));
	printf(N_T("\tTcn - specifies transaction control number\n"));
	printf(N_T("\tEncoding - specifies ANTemplate encoding type\n"));
	printf(N_T("\t\t0 - Traditional binary encoding \n"));
	printf(N_T("\t\t1 - NIEM-conformant XML encoding\n"));

	return 1;
}

NResult NTemplateToANTemplateFile(
	HNBuffer hTemplateBuffer, // buffer that contains packed NTemplate
	NChar * szFileName, // pointer to string that specifies filename to store ANTemplate
	const NChar * szTot, // pointer to tring that specifies type of transaction
	const NChar * szDai, // pointer to string that specifies destination agency identifier
	const NChar * szOri, // pointer to string that specifies originating agency identifier
	const NChar * szTcn, // pointer to string that specifies transaction control number
	const NChar * szEncoding // pointer to string that specifies encoding type
)
{
	HNTemplate hNTemplate = NULL; // handle to NTemplate object
	HNFTemplate hNFTemplate = NULL; // handle to NFTemplate object
	HANTemplate hANTemplate = NULL; // handle to ANTemplate object
	NResult result;
	BdifEncodingType encoding = strcmp(szEncoding, N_T("1")) == 0 ? betXml : betTraditional;
	NBool type9RecordFmtStd = NFalse;//sets minutia format: true - if standard, false - otherwise.

	// Create NTemplate object from packed NTemplate
	result = NTemplateCreateFromMemoryN(hTemplateBuffer, 0, NULL, &hNTemplate);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NTemplateCreateFromMemory, error code: %d\n"), result);
		goto FINALLY;
	}

	result = NTemplateGetPalmsEx(hNTemplate, &hNFTemplate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NTemplateGetPalmsEx, error code: %d\n"), result);
		goto FINALLY;
	}

	//For palms only standard minutia format is supported
	if (hNFTemplate != NULL)
	{
		NInt count = 0;
		result = NFTemplateGetRecordCount(hNFTemplate, &count);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in NFTemplateGetRecordCount, error code: %d\n"), result);
			goto FINALLY;
		}
		if (count > 0)
		{ 
			type9RecordFmtStd = NTrue;
		}
	}

	// Create ANTemplate object from NFRecord object
	result = ANTemplateCreateFromNTemplateEx(AN_TEMPLATE_VERSION_CURRENT, szTot, szDai, szOri, szTcn, type9RecordFmtStd, hNTemplate, 0, &hANTemplate);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateCreateFromNTemplate, error code: %d\n"), result);
		goto FINALLY;
	}

	// Store ANTemplate object in file
	result = ANTemplateSaveToFileEx(hANTemplate, szFileName, encoding, 0);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateSaveToFile, error code: %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hNTemplate);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hNFTemplate);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hANTemplate);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	return result;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	HNBuffer hBuffer = NULL;
	NBool available = NFalse;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * licenses = N_T("FingerClient,PalmClient");
	//const NChar * licenses = N_T("FingerFastExtractor,PalmClient");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 8)
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

	result = NFileReadAllBytesCN(argv[1], &hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFileReadAllBytesN() failed, result = %d\n"), result);
		goto FINALLY;
	}
	
	if ((strlen(argv[3]) < 3) || (strlen(argv[3]) > 4))
	{
		printf(N_T("tot parameter should be 3 or 4 characters length\n"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	result = NTemplateToANTemplateFile(hBuffer, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
	if(NFailed(result))
	{
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	OnExit();
	return result;
}
