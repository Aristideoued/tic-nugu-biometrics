#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NMedia/NMedia.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NMedia.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("WsqToNImage");
const NChar description[] = N_T("Demonstrates WSQ to NImage conversion");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2013-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [srcImage] [dstImage]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tsrcImage - filename of source WSQ image.\n"));
	printf(N_T("\tdstImage - name of a file to save converted image to.\n"));
	printf(N_T("\n"));
	return 1;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	NBool available = NFalse;
	HNImage hImage = NULL;
	HNImageFormat hImageFormat = NULL;
	HNImageFormat hDstImageFormat = NULL;
	HNImageInfo hImageInfo = NULL;
	NFloat bitRate = 0;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("FingerClient");
	//const NChar * license = N_T("FingerFastExtractor");

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

	// get WSQ image format
	result = NImageFormatGetWsqEx(&hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatGetWsqEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// create an NImage from a WSQ image file
	result = NImageCreateFromFileEx(argv[1], hImageFormat, 0, NULL, &hImage);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageCreateFromFileEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = NImageGetInfo(hImage, &hImageInfo);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageGetInfo() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = WsqInfoGetBitRate((HWsqInfo)hImageInfo, &bitRate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("WsqInfoGetBitRate() failed, result = %d\n"), result);
		goto FINALLY;
	}
	printf(N_T("loaded wsq bitrate: %.2f\n"), bitRate);

	// pick a format to save in, e.g. JPEG
	result = NImageFormatGetJpegEx(&hDstImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatGetJpegEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// save image to specified file
	result = NImageSaveToFileEx(hImage, argv[2], hDstImageFormat, NULL, 0);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageSaveToFileEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2;

		result2 = NObjectSet(NULL, &hImage);
		if (NFailed(result2))
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hImageFormat);
		if (NFailed(result2))
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hDstImageFormat);
		if (NFailed(result2))
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hImageInfo);
		if (NFailed(result2))
			result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed, result = %d\n"), result2);
	}

	OnExit();

	return result;
}
