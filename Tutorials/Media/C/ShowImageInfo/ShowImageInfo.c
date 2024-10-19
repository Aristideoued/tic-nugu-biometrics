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

const NChar title[] = N_T("ShowImageInfo");
const NChar description[] = N_T("Displays information about an image");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2013-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [filename]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tfilename - image filename.\n"));
	printf(N_T("\n"));
	return 1;
}

#define VALUE_LENGTH 128

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	HNImage hImage = NULL;
	HNImageFormat hSrcImageFormat = NULL;
	HNImageFormat hImageFormat = NULL;
	HNImageInfo hImageInfo = NULL;
	HNString hName = NULL;
	NBool available = NFalse;
	NBool areSame = NFalse;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("FingerClient");
	//const NChar * license = N_T("FingerFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 2)
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
	
	// obtain license (optional)
	result = NLicenseObtain(N_T("/local"), N_T("5000"), license, &available);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseObtain() failed, result = %d\n"), result);
		goto FINALLY;
	}

	if (!available)
	{
		printf(N_T("License %s not available\n"), license);
	}

	// create NImage with info from file
	result = NImageCreateFromFileEx(argv[1], NULL, 0, NULL, &hImage);
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

	// get image format
	result = NImageInfoGetFormatEx(hImageInfo, &hSrcImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageInfoGetFormatEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// print info common to all formats
	result = NImageFormatGetNameN(hSrcImageFormat, &hName);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatGetNameN() failed, result = %d\n"), result);
		goto FINALLY;
	}
	{
		const NChar * szName;
		result = NStringGetBuffer(hName, NULL, &szName);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed, result = %d\n"), result);
			goto FINALLY;
		}
		printf(N_T("format: %s\n"), szName);
	}
	result = NStringSet(NULL, &hName);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to clear name (result = %d)!\n"), result);
		goto FINALLY;
	}

	// print format specific info.
	result = NImageFormatGetJpeg2KEx(&hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatGetJpeg2KEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = NObjectEquals(hSrcImageFormat, hImageFormat, &areSame);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectEquals() failed, result = %d\n"), result);
		goto FINALLY;
	}
	result = NObjectSet(NULL, &hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed, result = %d\n"), result);
		goto FINALLY;
	}

	if (areSame) // if is Jpeg2K
	{
		Jpeg2KProfile profile = jpeg2kpNone;
		const NChar * szProfile;
		NFloat ratio = 0;

		result = Jpeg2KInfoGetProfile((HJpeg2KInfo)hImageInfo, &profile);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("Jpeg2KInfoGetProfile() failed, result = %d\n"), result);
			goto FINALLY;
		}
		switch(profile)
		{
			case jpeg2kpNone: szProfile = N_T("None"); break;
			case jpeg2kpFingerprint1000Ppi: szProfile = N_T("Fingerprint1000Ppi"); break;
			case jpeg2kpFaceLossy: szProfile = N_T("FaceLossy"); break;
			case jpeg2kpFaceLossless: szProfile = N_T("FaceLossless"); break;
			default: szProfile = N_T("Unknown");
		}
		printf(N_T("profile: %s\n"), szProfile);

		result = Jpeg2KInfoGetRatio((HJpeg2KInfo)hImageInfo, &ratio);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("Jpeg2KInfoGetRatio() failed, result = %d\n"), result);
			goto FINALLY;
		}
		printf(N_T("ratio: %.2f\n"), ratio);

		goto FINALLY;
	}

	result = NImageFormatGetJpegEx(&hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatGetJpegEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = NObjectEquals(hSrcImageFormat, hImageFormat, &areSame);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectEquals() failed, result = %d\n"), result);
		goto FINALLY;
	}
	result = NObjectSet(NULL, &hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed, result = %d\n"), result);
		goto FINALLY;
	}

	if (areSame) // if is Jpeg
	{
		NBool isLossless = NFalse;
		NInt quality = 0;

		result = JpegInfoIsLossless((HJpegInfo)hImageInfo, &isLossless);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("JpegInfoIsLossless() failed, result = %d\n"), result);
			goto FINALLY;
		}
		printf(N_T("lossless: %s\n"), isLossless ? N_T("True") : N_T("False"));

		result = JpegInfoGetQuality((HJpegInfo)hImageInfo, &quality);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("JpegInfoGetQuality() failed, result = %d\n"), result);
			goto FINALLY;
		}
		printf(N_T("quality: %d\n"), quality);

		goto FINALLY;
	}

	result = NImageFormatGetPngEx(&hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatGetPngEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = NObjectEquals(hSrcImageFormat, hImageFormat, &areSame);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectEquals() failed, result = %d\n"), result);
		goto FINALLY;
	}
	result = NObjectSet(NULL, &hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed, result = %d\n"), result);
		goto FINALLY;
	}

	if (areSame) // if is Png
	{
		NInt compressionLevel = 0;

		result = PngInfoGetCompressionLevel((HPngInfo)hImageInfo, &compressionLevel);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("PngInfoGetCompressionLevel() failed, result = %d\n"), result);
			goto FINALLY;
		}
		printf(N_T("compression level: %d\n"), compressionLevel);

		goto FINALLY;
	}

	result = NImageFormatGetWsqEx(&hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NImageFormatGetWsqEx() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = NObjectEquals(hSrcImageFormat, hImageFormat, &areSame);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectEquals() failed, result = %d\n"), result);
		goto FINALLY;
	}
	result = NObjectSet(NULL, &hImageFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed, result = %d\n"), result);
		goto FINALLY;
	}

	if (areSame) // if is Wsq
	{
		NFloat bitRate = 0;
		NUInt16 nr = 0;

		result = WsqInfoGetBitRate((HWsqInfo)hImageInfo, &bitRate);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("WsqInfoGetBitRate() failed, result = %d\n"), result);
			goto FINALLY;
		}
		printf(N_T("bit rate: %.2f\n"), bitRate);

		result = WsqInfoGetImplementationNumber((HWsqInfo)hImageInfo, &nr);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("WsqInfoGetImplementationNumber() failed, result = %d\n"), result);
			goto FINALLY;
		}
		printf(N_T("impementation number: %u\n"), nr);

		goto FINALLY;
	}

FINALLY:
	{
		NResult result2;

		result2 = NObjectSet(NULL, &hImage);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hImageFormat);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hSrcImageFormat);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hImageInfo);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NStringSet(NULL, &hName);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet() failed, result = %d\n"), result2);
	}

	OnExit();

	return result;
}
