#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NBiometricClient/NBiometricClient.h>
	#include <NBiometrics/NBiometrics.h>
	#include <NMedia/NMedia.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NBiometricClient.h>
	#include <NBiometrics.h>
	#include <NMedia.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("FCRecordToNTemplate");
const NChar description[] = N_T("Demonstrates creation of NTemplate from FCRecord");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage: %s [FCRecord] [NTemplate]\n"), title);
	printf(N_T("\tFCRecord  - input FCRecord\n"));
	printf(N_T("\tNTemplate - output NTemplate\n"));

	return 1;
}

int main(int argc, NChar *argv[])
{
	HNBuffer hBuffer = NULL;
	HFCRecord hFCRecord = NULL;
	HFcrFaceImage hFcrFaceImage = NULL;
	HNImage hImage = NULL;
	HNSubject hSubject = NULL;
	HNFace hFace = NULL;
	HNBiometricClient hBiometricClient = NULL;
	HNString hBiometricStatus = NULL;

	NBiometricStatus biometricStatus = nbsNone;
	const NChar * szBiometricStatus = NULL;
	NResult result = N_OK;
	NInt fv_count;
	NInt i;
	NBool available = NFalse;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("FaceClient");
	//const NChar * license = N_T("FaceFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 3)
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

	result = NFileReadAllBytesCN(argv[1], &hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFileReadAllBytesCN, error code: %d\n"), result);
		goto FINALLY;
	}

	result = FCRecordCreateFromMemoryN(hBuffer, 0, bsIso, NULL, &hFCRecord);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in FCRecordCreateFromMemory, error code: %d\n"), result);
		goto FINALLY;
	}

	result = NObjectSet(NULL, &hBuffer);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NObjectSet, error code: %d\n"), result);
		goto FINALLY;
	}

	result = FCRecordGetFaceImageCount(hFCRecord, &fv_count);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in FCRecordGetFaceImageCount, error code: %d\n"), result);
		goto FINALLY;
	}

	// create biometric client
	result = NBiometricClientCreate(&hBiometricClient);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NBiometricClientCreate() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// create subject
	result = NSubjectCreate(&hSubject);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NSubjectCreate() failed (result = %d)!"), result);
		goto FINALLY;
	}

	for (i = 0; i < fv_count; i++)
	{
		result = FCRecordGetFaceImage(hFCRecord, i, &hFcrFaceImage);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in FCRecordGetFaceImage, error code: %d\n"), result);
			goto FINALLY;
		}

		result = FcrFaceImageToNImage(hFcrFaceImage, 0, &hImage);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in FcrFaceImageToNImage, error code: %d\n"), result);
			goto FINALLY;
		}

		// create face for the subject
		result = NFaceCreate(&hFace);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NFaceCreate() failed (result = %d)!"), result);
			goto FINALLY;
		}

		result = NFaceSetImage(hFace, hImage);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in NFaceSetImage, error code: %d\n"), result);
			goto FINALLY;
		}

		// set the face for the subject
		result = NSubjectAddFace(hSubject, hFace, NULL);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NSubjectAddFace() failed (result = %d)!"), result);
			goto FINALLY;
		}

		result = NObjectSet(NULL, &hFcrFaceImage);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in NObjectSet, error code: %d\n"), result);
			goto FINALLY;
		}

		result = NObjectSet(NULL, &hImage);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in NObjectSet, error code: %d\n"), result);
			goto FINALLY;
		}

		result = NObjectSet(NULL, &hFace);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in NObjectSet, error code: %d\n"), result);
			goto FINALLY;
		}
	}

	// create the template
	result = NBiometricEngineCreateTemplate(hBiometricClient, hSubject, &biometricStatus);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NBiometricEngineCreateTemplate() failed (result = %d)!"), result);
		goto FINALLY;
	}

	if (biometricStatus != nbsOk)
	{
		// retrieve biometric status
		result = NEnumToStringP(N_TYPE_OF(NBiometricStatus), biometricStatus, NULL, &hBiometricStatus);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NEnumToStringP() failed (result = %d)!"), result);
			goto FINALLY;
		}

		result = NStringGetBuffer(hBiometricStatus, NULL, &szBiometricStatus);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
			goto FINALLY;
		}

		printf(N_T("template extraction failed!\n"));
		printf(N_T("biometric status: %s\n"), szBiometricStatus);

		result = N_E_FAILED;
		goto FINALLY;
	}

	// retrieve template
	result = NSubjectGetTemplateBuffer(hSubject, &hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NSubjectGetTemplateBuffer() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NFileWriteAllBytesCN(argv[2], hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to write template to file (result = %d)!"), result);
		goto FINALLY;
	}

	printf(N_T("NTemplate successfully saved to file \"%s\"\n"), argv[2]);

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hBuffer);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFCRecord);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFcrFaceImage);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hImage);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hSubject);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFace);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hBiometricClient);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NStringSet(NULL, &hBiometricStatus);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result2);
	}

	OnExit();
	return result;
}
