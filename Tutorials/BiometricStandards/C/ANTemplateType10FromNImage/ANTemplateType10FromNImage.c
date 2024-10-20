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

const NChar title[] = N_T("ANTemplateType10FromNImage");
const NChar description[] = N_T("Demonstrates creation of ANTemplate with current version and type 10 record in it");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2009-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [NImage] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Src] [Encoding]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tNImage     - filename with image file\n"));
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

NResult ANTemplateAddRecordType10(
	NChar * szFileNameIn, // pointer to string that specifies filename of image file
	NChar * szFileNameOut, // pointer to string that specifies filename to store ANTemplate
	const NChar * szTot, // pointer to tring that specifies type of transaction
	const NChar * szDai, // pointer to string that specifies destination agency identifier
	const NChar * szOri, // pointer to string that specifies originating agency identifier
	const NChar * szTcn, // pointer to string that specifies transaction control number
	const NChar * szSrc,	// pointer to string that specifies source agency name
	const NChar * szEncoding // pointer to string that specifies encoding type
	)
{
	HANTemplate hANTemplate;	// handle to ANTemplate object
	HANType10Record hRecord = NULL;	// handle to ANRecord object
	HNBuffer hImageBuffer = NULL;	// handle to image NBuffer object
	HNString hSrc = NULL;
	HNString hSmt = NULL;
	NResult result;
	ANImageType imt = anitFace; //image type contained in file, currently face
	BdifEncodingType encoding = strcmp(szEncoding, N_T("1")) == 0 ? betXml : betTraditional;

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

	/*
		Reads image data from file.
		Image must be compressed using valid compression algorithm for Type-10 record.
		How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
	*/
	result = NFileReadAllBytesCN(szFileNameIn, &hImageBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFileReadAllBytesCN, error code: %d"), result);
		goto FINALLY;
	}

	// Create Type 10 record and add record to ANTemplate object
	result = ANTemplateAddType10RecordFromImageDataN(hANTemplate, imt, hSrc, hImageBuffer, 0, &hRecord);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateAddType10RecordFromImageDataN, error code: %d"), result);
		goto FINALLY;
	}

	// Sets additional optional fields for face modality
	if (imt == anitFace)
	{
		//Sets distortion
		ANDistortion distortion = {andcBarrel, andmcEstimated, andscMild};
		result = ANType10RecordSetDistortion(hRecord, &distortion);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in ANType10RecordSetDistortion, error code: %d"), result);
			goto FINALLY;
		}

		//Adds lighting artifact
		result = ANType10RecordAddLightingArtifact(hRecord, anlaFaceShadows, NULL);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in ANType10RecordAddLightingArtifact, error code: %d"), result);
			goto FINALLY;
		}

		//Sets subject pose
		result = ANType10RecordSetSubjectPose(hRecord, anspFullFaceFrontal);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in ANType10RecordSetSubjectPose, error code: %d"), result);
			goto FINALLY;
		}

		//Sets tiered markup collection - specifies face feature points that shall be contained in 2D facial feauture point collection.
		result = ANType10RecordSetTieredMarkupCollection(hRecord, antmcEyeCenters);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in ANType10RecordSetTieredMarkupCollection, error code: %d"), result);
			goto FINALLY;
		}

		//Sets image tranformations
		result = ANType10RecordSetImageTransformation(hRecord, (BdifFacePostAcquisitionProcessing)(bfpapPoseCorrected | bfpapContrastStretched));
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in ANType10RecordSetImageTransformation, error code: %d"), result);
			goto FINALLY;
		}
	}

	// Store ANTemplate object with type 10 record in file
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
		result2 = NObjectSet(NULL, &hImageBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NStringSet(NULL, &hSrc);
		if NFailed((result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result2);
		result2 = NStringSet(NULL, &hSmt);
		if NFailed((result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result2);
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

	const NChar * license = N_T("FaceClient");
	//const NChar * license = N_T("FaceFastExtractor");

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

	result = ANTemplateAddRecordType10(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
	if (NFailed(result))
	{
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	OnExit();
	return result;
}