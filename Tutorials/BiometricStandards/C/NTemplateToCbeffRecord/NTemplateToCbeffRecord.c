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

const NChar title[] = N_T("NTemplateToCbeffRecord");
const NChar description[] = N_T("Converting NTemplate to CbeffRecord");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2014-2024 Neurotechnology");

#define MAX_LICENSES 4

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [NTemplate] [CbeffRecord] [PatronFormat]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\t[NTemplate] - filename of NTemplate\n"));
	printf(N_T("\t[CbeffRecord] - filename for CbeffRecord\n"));
	printf(N_T("\t[PatronFormat] - hex number identifying patron format (all supported values can be found in CbeffRecord class documentation)\n"));
	return 1;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	HNBuffer hBuffer = NULL;
	HNBuffer hCbeffBuffer = NULL;
	HCbeffRecord hCbeffRecord = NULL; // handle to CbeffRecord object
	NUInt bdbformat = 0;
	NUInt patronFormat = 0;
	NInt obtainedLicensesCount = 0, i = 0;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * Licenses[MAX_LICENSES] = { N_T("FingerClient"), N_T("PalmClient"), N_T("FaceClient"), N_T("IrisClient") };
	//const NChar * Licenses[MAX_LICENSES] = { N_T("FingerFastExtractor"), N_T("PalmClient"), N_T("FaceFastExtractor"), N_T("IrisFastExtractor") };

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc != 4)
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
	for (i = 0; i < MAX_LICENSES; i++)
	{
		NBool available;
		result = NLicenseObtain(N_T("/local"), N_T("5000"), Licenses[i], &available);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NLicenseObtain() failed, result = %d\n"), result);
			goto FINALLY;
		}
		if (available)
		{
			obtainedLicensesCount++;
		}
	}

	if (obtainedLicensesCount == 0)
	{
		printf(N_T("Could not obtain any matching license\n"));
		result = N_E_NOT_ACTIVATED;
		goto FINALLY;
	}

	result = NFileReadAllBytesCN(argv[1], &hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFileReadAllBytesN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// combine NTemplate BDB format
	bdbformat = BdifMakeFormat(CBEFF_BO_NEUROTECHNOLOGIJA, CBEFF_BDBFI_NEUROTECHNOLOGIJA_NTEMPLATE);

	// get CbeffRecord patron format
	result = NUInt32Parse(argv[3], N_T("X"), &patronFormat);
	if (NFailed(result))
	{ 
		result = PrintErrorMsgWithLastError(N_T("NUInt32Parse() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// create CbeffRecord from NTemplate buffer
	result = CbeffRecordCreateFromDataN(bdbformat, hBuffer, patronFormat, &hCbeffRecord);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("CbeffRecordCreateFromDataN() failed, result = %d\n"), result);
		goto FINALLY;
	}
	
	// get CbeffRecord buffer
	result = NObjectSaveToMemoryN(hCbeffRecord, 0, &hCbeffBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectSaveToMemoryN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// save CbeffRecord buffer to file
	result = NFileWriteAllBytesCN(argv[2], hCbeffBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFileWriteAllBytesCN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hCbeffBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hCbeffRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	OnExit();
	return result;
}
