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

const NChar title[] = N_T("ANTemplateType11FromNSoundBuffer");
const NChar description[] = N_T("Demonstrates creation of ANTemplate with current version and type 11 record in it");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2009-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [NSoundBuffer] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Src] [Encoding]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tNSoundBuffer - filename with sound buffer file\n"));
	printf(N_T("\tANTemplate - filename for ANTemplate\n"));
	printf(N_T("\tTot - specifies type of transaction\n"));
	printf(N_T("\tDai - specifies destination agency identifier\n"));
	printf(N_T("\tOri - specifies originating agency identifier\n"));
	printf(N_T("\tTcn - specifies transaction control number\n"));
	printf(N_T("\tSrc - specifies source agency name\n"));
	printf(N_T("\tEncoding - specifies ANTemplate encoding type\n"));
	printf(N_T("\t\t0 - Traditional binary encoding \n"));
	printf(N_T("\t\t1 - NIEM-conformant XML encoding\n"));
	return 1;
}

NResult ANTemplateAddRecordType11(
	NChar * szFileNameIn, // pointer to string that specifies filename of sound buffer file
	NChar * szFileNameOut, // pointer to string that specifies filename to store ANTemplate
	const NChar * szTot, // pointer to tring that specifies type of transaction
	const NChar * szDai, // pointer to string that specifies destination agency identifier
	const NChar * szOri, // pointer to string that specifies originating agency identifier
	const NChar * szTcn, // pointer to string that specifies transaction control number
	const NChar * szSrc,	// pointer to string that specifies source agency name
	const NChar * szEncoding // pointer to string that specifies encoding type
	)
{
	HANTemplate hANTemplate = NULL;	// handle to ANTemplate object
	HANType11Record hRecord = NULL;	// handle to ANRecord object
	HNSoundBuffer hSoundBuffer = NULL;	// handle to sound NBuffer object
	HNString hSrc = NULL;
	NResult result;
	BdifEncodingType encoding = strcmp(szEncoding, N_T("1")) == 0 ? betXml : betTraditional;
	ANAcquisitionSourceType acqSourceType = anastDigitalAudioRecordingDevice;
	const NChar * analogToDigital = NULL;
	const NChar * radioTransmissionFormat = NULL;
	const NChar * specialCharacteristics = NULL;
	ANAcquisitionSource acqSource = {0};

	// Create ANTemplate object with current version and only type 1 record in it
	result = ANTemplateCreateWithTransactionInformation(AN_TEMPLATE_VERSION_CURRENT, szTot, szDai, szOri, szTcn, 0, &hANTemplate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateCreateWithTransactionInformationEx, error code: %d"), result);
		goto FINALLY;
	}

	result = NStringCreate(szSrc, &hSrc);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NStringCreate, error code: %d"), result);
		goto FINALLY;
	}

	//Reads sound buffer data from file
	result = NSoundBufferCreateFromFile(szFileNameIn, 0, &hSoundBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NSoundBufferCreateFromFile, error code: %d"), result);
		goto FINALLY;
	}

	// Sample acquisition source (11.008), which is mandatory when record has associated voice data. Must be updated with actual data.
	result = ANAcquisitionSourceCreate(acqSourceType, analogToDigital, radioTransmissionFormat, specialCharacteristics, &acqSource);
	if (NFailed(result))
	{

		result = PrintErrorMsgWithLastError(N_T("error in ANAcquisitionSourceCreate, error code: %d"), result);
		goto FINALLY;
	}

	// Creates Type 11 record and adds record to ANTemplate object
	result = ANTemplateAddType11RecordFromNSoundBufferN(hANTemplate, hSrc, &acqSource, hSoundBuffer, 0, &hRecord);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateAddType11RecordFromNSoundBufferN, error code: %d"), result);
		goto FINALLY;
	}

	// XML encoding is not supported currently
	if (encoding != betTraditional)
	{
		result = PrintErrorMsgWithLastError(N_T("Currently only traditional encoding is supported for voice record: %d"), N_E_FAILED);
		goto FINALLY;
	}

	// Store ANTemplate object with type 11 record in file
	result = ANTemplateSaveToFileEx(hANTemplate, szFileNameOut, encoding, 0);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateSaveToFileEx, error code: %d"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hANTemplate);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hSoundBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NStringSet(NULL, &hSrc);
		if NFailed((result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result2);
		result2 = ANAcquisitionSourceDispose(&acqSource);
		if NFailed((result2)) PrintErrorMsg(N_T("ANAcquisitionSourceDispose() failed (result = %d)!"), result2);
	}

	return result;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	NBool available = NFalse;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("VoiceClient");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 9)
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

	result = ANTemplateAddRecordType11(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
	if (NFailed(result))
	{
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	OnExit();
	return result;
}
