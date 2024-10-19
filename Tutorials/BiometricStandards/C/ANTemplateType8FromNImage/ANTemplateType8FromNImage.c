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

const NChar title[] = N_T("ANTemplateType8FromNImage");
const NChar description[] = N_T("Demonstrates creation of ANTemplate with type 8 record in it");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2009-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [Signature] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tSignature  - filename with signature image\n"));
	printf(N_T("\tANTemplate - filename for ANTemplate\n"));
	printf(N_T("\tTot - specifies type of transaction\n"));
	printf(N_T("\tDai - specifies destination agency identifier\n"));
	printf(N_T("\tOri - specifies originating agency identifier\n"));
	printf(N_T("\tTcn - specifies transaction control number\n"));
	printf(N_T("\tEncoding - specifies ANTemplate encoding type\n"));
	printf(N_T("\t\t0 - Traditional binary encoding \n"));
	printf(N_T("\t\t1 - NIEM-conformant XML encoding\n"));

	return 1;
}

NResult ANTemplateAddRecordType8(
	NChar * szFileNameIn, // pointer to string that specifies filename of signature file
	NChar * szFileNameOut, // pointer to string that specifies filename to store ANTemplate
	const NChar * szTot, // pointer to tring that specifies type of transaction
	const NChar * szDai, // pointer to string that specifies destination agency identifier
	const NChar * szOri, // pointer to string that specifies originating agency identifier
	const NChar * szTcn, // pointer to string that specifies transaction control number
	const NChar * szEncoding // pointer to string that specifies encoding type
	)
{
	HANTemplate hANTemplate = NULL; // handle to ANTemplate object
	HNImage hImage = NULL; // handle to NImage object
	HNImage hlrBinImage = NULL; // handle to low resolution binary image
	HANType8Record hRecord = NULL; // handle to ANRecord object
	NResult result;
	ANSignatureType st = anstSubject;
	NBool isr = NTrue;
	//NUInt isrValue = AN_TYPE_1_RECORD_MIN_SCANNING_RESOLUTION; // Default value
	ANSignatureRepresentationType srt = ansrtScannedUncompressed; // value for signature representation type
	NFloat horizontalResolution = 0.0;
	NFloat verticalResolution = 0.0;
	NBool resolutionIsAspectRatio = NFalse;
	BdifEncodingType encoding = strcmp(szEncoding, N_T("1")) == 0 ? betXml : betTraditional;

	// Create empty ANTemplate object with only type 1 record in it
	result = ANTemplateCreateWithTransactionInformation(AN_TEMPLATE_VERSION_CURRENT, szTot, szDai, szOri, szTcn, 0, &hANTemplate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateCreate, error code: %d"), result);
		goto FINALLY;
	}

	// Create NImage object from image file
	result = NImageCreateFromFileEx(szFileNameIn, NULL, 0, NULL, &hImage);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NImageCreateFromFile, error code: %d"), result);
		goto FINALLY;
	}

	// Create low resolution binary image from an image
	result = NImageGetHorzResolution(hImage, &horizontalResolution);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get horizontal resolution for image, error %d\n"), result);
		goto FINALLY;
	}

	result = NImageGetVertResolution(hImage, &verticalResolution);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get vertical resolution for image, error %d\n"), result);
		goto FINALLY;
	}

	if (verticalResolution < 250)
	{
		printf(N_T("vertical resolution is less than 250 (resolution %f), forcing 500 resolution\n"), verticalResolution);
		verticalResolution = 500;
	}

	if (horizontalResolution < 250)
	{
		printf(N_T("horizontal resolution is less than 250 (resolution %f), forcing 500 resolution\n"), horizontalResolution);
		horizontalResolution = 500;
	}

	result = NImageGetResolutionIsAspectRatio(hImage, &resolutionIsAspectRatio);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get resolution is aspect ratio for image, error %d\n"), result);
		goto FINALLY;
	}

	result = NImagesRecolorImage(hImage, NPF_GRAYSCALE_1U, NULL, NULL, &hlrBinImage);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NImagesRecolorImage, error code: %d"), result);
		goto FINALLY;
	}

	result = NImageSetHorzResolution(hlrBinImage, horizontalResolution);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to set horizontal resolution, error %d\n"), result);
		goto FINALLY;
	}

	result = NImageSetVertResolution(hlrBinImage, verticalResolution);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to set vertical resolution, error %d\n"), result);
		goto FINALLY;
	}

	if(resolutionIsAspectRatio)
	{
		result = NImageSetResolutionIsAspectRatio(hlrBinImage, NFalse);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to set resolution is aspect ratio for image, error %d\n"), result);
			goto FINALLY;
		}
	}

	// Create Type 8 record
	result = ANTemplateAddType8RecordFromNImage(hANTemplate, st, srt, isr, hlrBinImage, &hRecord);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateAddType8RecordFromNImage, error code: %d"), result);
		goto FINALLY;
	}

	// Store ANTemplate object with type 8 record in file
	result = ANTemplateSaveToFileEx(hANTemplate, szFileNameOut, encoding, 0);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateSaveToFile, error code: %d"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hANTemplate);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hImage);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hlrBinImage);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
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
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * licenses = N_T("FingerClient,PalmClient,FaceClient,IrisClient");
	//const NChar * licenses = N_T("FingerFastExtractor,FaceFastExtractor,IrisFastExtractor");

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

	result = ANTemplateAddRecordType8(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
	if (NFailed(result))
	{
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	OnExit();
	return result;
}
