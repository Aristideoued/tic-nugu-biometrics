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

const NChar title[] = N_T("CreateWsq");
const NChar description[] = N_T("Demonstrates WSQ format image creation from another image");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2013-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [srcImage] [dstImage] <optional: bitRate>\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tsrcImage- filename of source finger image.\n"));
	printf(N_T("\tdstImage - name of a file to save the created WSQ image to.\n"));
	printf(N_T("\ttbitRate  - specifies WSQ image compression level. Typical bit rates: 0.75, 2.25.\n"));
	printf(N_T("\n"));
	return 1;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	NBool available = NFalse;
	HNImage hImage = NULL;
	HNImageFormat hImageFormat = NULL;
	HNImageInfo hImageInfo = NULL;
	NFloat bitRate = WSQ_DEFAULT_BIT_RATE;
	
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

	if (argc > 3)
	{
		bitRate = (NFloat)atof(argv[3]);
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

	// create an NImage from file
	result = NImageCreateFromFileEx(argv[1], NULL, 0, NULL, &hImage);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageCreateFromFileEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = NImageFormatGetWsqEx(&hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatGetWsqEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = NImageFormatCreateInfo(hImageFormat, hImage, 0, &hImageInfo);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatCreateInfo() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// set specified bit rate (or default if bit rate was not specified).
	result = WsqInfoSetBitRate((HWsqInfo)hImageInfo, bitRate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("WsqInfoSetBitRate() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// save image in WSQ format and bitrate to file.
	result = NImageSaveToFileEx(hImage, argv[2], NULL, hImageInfo, 0);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageSaveToFileEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	printf(N_T("WSQ image with bit rate %.2f was saved to %s\n"), bitRate, argv[2]);

	result = N_OK;
FINALLY:
	{
		NResult result2;

		result2 = NObjectSet(NULL, &hImage);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hImageFormat);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hImageInfo);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
	}

	OnExit();

	return result;
}
