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

const NChar title[] = N_T("ANTemplateType6FromNImage");
const NChar description[] = N_T("Demonstrates creation of ANTemplate with type 6 record in it");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2009-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [NImage] [ANTemplate] [Tot] [Dai] [Ori] [Tcn]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tNImage     - filename with image file\n"));
	printf(N_T("\tANTemplate - filename for ANTemplate\n"));
	printf(N_T("\tTot - specifies type of transaction\n"));
	printf(N_T("\tDai - specifies destination agency identifier\n"));
	printf(N_T("\tOri - specifies originating agency identifier\n"));
	printf(N_T("\tTcn - specifies transaction control number\n"));

	return 1;
}

NResult ANTemplateAddRecordType6(
	NChar * szFileNameIn, // pointer to string that specifies filename of image file
	NChar * szFileNameOut, // pointer to string that specifies filename to store ANTemplate
	const NChar * szTot, // pointer to tring that specifies type of transaction
	const NChar * szDai, // pointer to string that specifies destination agency identifier
	const NChar * szOri, // pointer to string that specifies originating agency identifier
	const NChar * szTcn // pointer to string that specifies transaction control number
	)
{
	HANTemplate hANTemplate = NULL; // handle to ANTemplate object
	HNImage hImage = NULL; // handle to NImage object
	HNImage hBinImage = NULL; // handle to monochrome image
	HANType6Record hRecord = NULL; // handle to ANRecord object
	HANType1Record type1 = NULL; // handle to ANRecord object
	NResult result;
	NBool isr = NTrue;
	ANBinaryImageCompressionAlgorithm ca = anbicaNone; // value for image compresion algorithm
	NFloat horizontalResolution = 0.0;
	NFloat verticalResolution = 0.0;
	NBool resolutionIsAspectRatio = NFalse;
	NVersion templateVersion = AN_TEMPLATE_VERSION_4_0;

	// Create empty ANTemplate object with only type 1 record in it
	result = ANTemplateCreateWithTransactionInformation(templateVersion, szTot, szDai, szOri, szTcn, 0, &hANTemplate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateCreateWithTransactionInformation, error code: %d"), result);
		goto FINALLY;
	}

	// Create NImage object from image file
	result = NImageCreateFromFileEx(szFileNameIn, NULL, 0, NULL, &hImage);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NImageCreateFromFile, error code: %d"), result);
		goto FINALLY;
	}

	// Create monochrome binary image
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

	result = NImagesRecolorImage(hImage, NPF_GRAYSCALE_1U, NULL, NULL, &hBinImage);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NImagesRecolorImage, error code: %d"), result);
		goto FINALLY;
	}

	result = NImageSetHorzResolution(hBinImage, horizontalResolution);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to set horizontal resolution, error %d\n"), result);
		goto FINALLY;
	}

	result = NImageSetVertResolution(hBinImage, verticalResolution);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to set vertical resolution, error %d\n"), result);
		goto FINALLY;
	}

	if(resolutionIsAspectRatio)
	{
		result = NImageSetResolutionIsAspectRatio(hBinImage, NFalse);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to set resolution is aspect ratio for image, error %d\n"), result);
			goto FINALLY;
		}
	}

	// Create Type 6 record and add to ANTemplate object
	result = ANTemplateAddType6RecordFromNImage(hANTemplate, isr, ca, hBinImage, &hRecord);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateAddType6RecordFromNImage, error code: %d"), result);
		goto FINALLY;
	}

	// obtain type 1 record from template
	result = ANTemplateGetRecordEx(hANTemplate, 0, &type1);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANTemplateGetRecordEx, error code: %d"), result);
		goto FINALLY;
	}

	result = ANType1RecordSetNativeScanningResolution(type1, AN_TYPE_1_RECORD_MIN_SCANNING_RESOLUTION);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANType1RecordSetNativeScanningResolution, error code: %d"), result);
		goto FINALLY;
	}

	result = ANType1RecordSetNominalTransmittingResolutionPpi(type1, horizontalResolution);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in ANType1RecordSetNominalTransmittingResolutionPpi, error code: %d"), result);
		goto FINALLY;
	}

	// Store ANTemplate object with type 6 record in file
	result = ANTemplateSaveToFile(hANTemplate, szFileNameOut, 0);
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
		result2 = NObjectSet(NULL, &hBinImage);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &type1);
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
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("FingerClient");
	//const NChar * license = N_T("FingerFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 7)
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

	result = ANTemplateAddRecordType6(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
	if (NFailed(result))
	{
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	OnExit();
	return result;
}
