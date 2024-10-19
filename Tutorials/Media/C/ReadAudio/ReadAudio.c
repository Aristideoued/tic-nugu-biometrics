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

const NChar title[] = N_T("ReadAudio");
const NChar description[] = N_T("Demonstrates reading sound from specified filename or url");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2011-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [source] [bufferCount] <optional: is url>\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tsource - filename or url sound buffers should be captured from\n"));
	printf(N_T("\tbufferCount - number of sound buffers to capture from specified filename or url\n"));
	printf(N_T("\tis url - specifies that passed source parameter is url (value: 1) or filename (value: 0)\n"));
	printf(N_T("\n"));
	return 1;
}

static NResult ReadSoundBuffers(HNMediaSource hSource, NInt bufferCount);

int main(int argc, NChar **argv)
{
	HNString hDisplayName = NULL;
	NResult result = N_OK;
	NInt bufferCount = 0;
	NBool available = NFalse;
	HNMediaReader hReader = NULL;
	NChar * szUri = NULL;
	NBool isUrl = NFalse;
	HNMediaSource hSource = NULL;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("VoiceExtractor");
	//const NChar * license = N_T("VoiceClient");
	//const NChar * license = N_T("VoiceFastExtractor");

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

	szUri = argv[1];
	bufferCount = atoi(argv[2]);
	if (bufferCount == 0)
	{
		printf(N_T("no sound buffers will be read as sound buffer count is not specified"));
	}

	if (argc > 3)
	{
		isUrl = atoi(argv[3]) == 1;
	}

	// create media source
	result = isUrl ? NMediaSourceCreateFromUrl(szUri, 0, &hSource) : NMediaSourceCreateFromFile(szUri, 0, &hSource);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to create media source (result = %d)!\n"), result);
		goto FINALLY;
	}

	// get source settings
	result = NMediaSourceGetDisplayNameN(hSource, &hDisplayName);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get display name (result = %d)!\n"), result);
		goto FINALLY;
	}
	{
		const NChar * szDisplayName;
		result = NStringGetBuffer(hDisplayName, 0, &szDisplayName);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get display name (result = %d)!\n"), result);
			goto FINALLY;
		}

		printf(N_T("display name: %s\n"), szDisplayName);
	}
	result = NStringSet(NULL, &hDisplayName);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to clear display name (result = %d)!\n"), result);
		goto FINALLY;
	}

	result = NMediaReaderCreate(hSource, nmtAudio, NTrue, 0, &hReader);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to create media reader from media source (result = %d)!\n"), result);
		goto FINALLY;
	}

	result = ReadSoundBuffers(hReader, bufferCount);
	if (NFailed(result)) goto FINALLY;
	
	printf(N_T("done\n"));

	result = N_OK;
FINALLY:
	{
		NResult result2;

		result2 = NObjectSet(NULL, &hReader);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NObjectSet(NULL, &hSource);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed, result = %d\n"), result2);
		result2 = NStringSet(NULL, &hDisplayName);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet() failed, result = %d\n"), result2);
	}

	OnExit();

	return result;
}

static void DumpMediaFormat(HNMediaFormat hFormat)
{
	NMediaType formatMediaType;
	NResult result;

	if (hFormat == NULL) return;

	result = NMediaFormatGetMediaType(hFormat, &formatMediaType);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get media type for specified format (result = %d)!\n"), result);
		return;
	}

	switch (formatMediaType)
	{
	case nmtVideo:
		{
			NUInt width, height;
			NURational frameRate;
			NVideoInterlaceMode interlaceMode;
			NURational aspectRatio;

			result = NVideoFormatGetWidth(hFormat, &width);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get width for specified format (result = %d)!\n"), result);
				return;
			}
			result = NVideoFormatGetHeight(hFormat, &height);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get height for specified format (result = %d)!\n"), result);
				return;
			}
			result = NVideoFormatGetFrameRate(hFormat, &frameRate);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get frame rate for specified format (result = %d)!\n"), result);
				return;
			}
			result = NVideoFormatGetInterlaceMode(hFormat, &interlaceMode);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get interlace mode for specified format (result = %d)!\n"), result);
				return;
			}
			result = NVideoFormatGetPixelAspectRatio(hFormat, &aspectRatio);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get aspect ratio for specified format (result = %d)!\n"), result);
				return;
			}
			printf(N_T("video format .. %dx%d @ %d/%d (interlace: %d, aspect ratio: %d/%d)\n"), width, height,
				frameRate.Numerator, frameRate.Denominator, interlaceMode, aspectRatio.Numerator, aspectRatio.Denominator);
		}
		break;
	case nmtAudio:
		{
			NInt channelCount, sampleRate, bitsPerChannel;

			result = NAudioFormatGetChannelCount(hFormat, &channelCount);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get channel count for specified format (result = %d)!\n"), result);
				return;
			}
			result = NAudioFormatGetSampleRate(hFormat, &sampleRate);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get sample rate for specified format (result = %d)!\n"), result);
				return;
			}
			result = NAudioFormatGetBitsPerChannel(hFormat, &bitsPerChannel);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get bits per sample for specified format (result = %d)!\n"), result);
				return;
			}
			printf(N_T("audio format .. channels: %d, samples/second: %d, bits/channel: %d\n"),
					channelCount, sampleRate, bitsPerChannel);
		}
		break;
	default:
		printf(N_T("unknown media type specified in format!\n"));
		return;
	}
}

static NResult ReadSoundBuffers(HNMediaReader hReader, NInt bufferCount)
{
	HNSoundBuffer hSoundBuffer = NULL;
	NResult result;
	HNMediaFormat * arFormats = NULL;
	HNMediaFormat hCurrentFormat = NULL;
	NLong length;
	NInt formatCount = 0, j;
	HNMediaSource hSource = NULL;
	NBool finishCapture = NFalse;

	result = NMediaReaderGetSource(hReader, &hSource);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get media source from media reader (result = %d)!\n"), result);
		goto FINALLY;
	}

	result = NMediaReaderGetLength(hReader, &length);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get media length from media reader (result = %d)!\n"), result);
		goto FINALLY;
	}
	printf(N_T("media length: %lld\n"), length);

	result = NMediaSourceGetFormats(hSource, nmtAudio, &arFormats, &formatCount);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get media formats from media source (result = %d)!\n"), result);
		goto FINALLY;
	}
	printf(N_T("format count: %d\n"), formatCount);
	for (j = 0; j < formatCount; j++)
	{
		printf(N_T("[%d] "), j);
		DumpMediaFormat(arFormats[j]);
	}

	result = NMediaSourceGetCurrentFormat(hSource, nmtAudio, &hCurrentFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get media formats from media source (result = %d)!\n"), result);
		goto FINALLY;
	}
	if (hCurrentFormat)
	{
		printf(N_T("current media format:\n"));
		DumpMediaFormat(hCurrentFormat);

		printf(N_T("set the last supported format (optional) ... "));
		result = NMediaSourceSetCurrentFormat(hSource, nmtAudio, arFormats[formatCount - 1]);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get media formats from media source (result = %d)!\n"), result);
			goto FINALLY;
		}
		printf(N_T("format setted\n"));
	}
	else
	{
		printf(N_T("current media format is not yet available (will be available after media reader start)\n"));
	}

	result = NObjectSet(NULL, &hCurrentFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to clear format (result = %d)!\n"), result);
		goto FINALLY;
	}

	printf(N_T("starting capture ... "));
	result = NMediaReaderStart(hReader);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to start media reader (result = %d)!\n"), result);
		goto FINALLY;
	}
	finishCapture = NTrue;
	printf(N_T("capture started\n"));

	result = NMediaSourceGetCurrentFormat(hSource, nmtAudio, &hCurrentFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get current format (result = %d)!\n"), result);
		goto FINALLY;
	}
	if (!hCurrentFormat)
	{
		printf(N_T("current media format is not set even after media reader start!\n"));
		goto FINALLY;
	}
	DumpMediaFormat(hCurrentFormat);

	for (j = 0; j < bufferCount; j++)
	{
		NLong timespan = -1, duration = 0;
		NInt sampleRate, length;
		
		result = NMediaReaderReadAudioSample(hReader, &timespan, &duration, &hSoundBuffer);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to read audio sample from media reader (result = %d)!\n"), result);
			goto FINALLY;
		}
		if (!hSoundBuffer)
		{
			break;
		}

		result = NSoundBufferGetSampleRate(hSoundBuffer, &sampleRate);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get sound buffer sample rate (result = %d)!\n"), result);
			goto FINALLY;
		}

		result = NSoundBufferGetLength(hSoundBuffer, &length);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get sound buffer sample length (result = %d)!\n"), result);
			goto FINALLY;
		}

		printf(N_T("[%llu %llu] sample rate: %d, sample length: %d\n"), timespan, duration, sampleRate, length);
		
		result = NObjectSet(NULL, &hSoundBuffer);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to clear sound buffer (result = %d)!\n"), result);
			goto FINALLY;
		}
		fflush(stdout);
	}
	result = N_OK;
FINALLY:
	if (finishCapture)
	{
		result = NMediaReaderStop(hReader);
		if (NFailed(result)) PrintErrorMsg(N_T("failed to stop media reader (result = %d)!\n"), result);
	}
	{
		NResult result2;
		result2 = NObjectSet(NULL, &hSoundBuffer);
		if (NFailed(result2)) PrintErrorMsg(N_T("failed to clear sound buffer (result = %d)!\n"), result2);
		result2 = NObjectSet(NULL, &hCurrentFormat);
		if (NFailed(result2)) PrintErrorMsg(N_T("failed to clear current format (result = %d)!\n"), result2);
		result2 = NObjectUnrefArray(arFormats, formatCount);
		if (NFailed(result2)) PrintErrorMsg(N_T("failed to clear formats (result = %d)!\n"), result2);
		result2 = NObjectSet(NULL, &hSource);
		if (NFailed(result2)) PrintErrorMsg(N_T("failed to clear source (result = %d)!\n"), result2);
	}
	return result;
}
