#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NMedia/NMedia.h>
	#include <NDevices/NDevices.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NMedia.h>
	#include <NDevices.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("SoundCapture");
const NChar description[] = N_T("Demonstrates capturing sound from microphones");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2011-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [bufferCount]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tbufferCount - number of sound buffers to capture from each microphone to current directory\n"));
	printf(N_T("\n"));
	return 1;
}

int main(int argc, NChar **argv)
{
	HNDeviceManager hDeviceManager = NULL;
	HNDevice hDevice = NULL;
	HNSoundBuffer hSoundSample = NULL;
	HNString hDisplayName = NULL;
	NResult result;
	NInt deviceCount, bufferCount = 0;
	NInt i;
	NBool available = NFalse;
	
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

	bufferCount = atoi(argv[1]);
	if (bufferCount == 0)
	{
		printf(N_T("no sound buffers will be captured as sound buffer count is not specified"));
	}

	printf(N_T("creating device manager ...\n"));
	result = NDeviceManagerCreateEx(&hDeviceManager);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to create device manager failed (result = %d)\n"), result);
		goto FINALLY;
	}
	result = NDeviceManagerSetDeviceTypes(hDeviceManager, ndtMicrophone);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to set device types (result = %d)!\n"), result);
		goto FINALLY;
	}
	result = NDeviceManagerSetAutoPlug(hDeviceManager, NTrue);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to set auto plug (result = %d)!\n"), result);
		goto FINALLY;
	}

	result = NDeviceManagerInitialize(hDeviceManager);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to initialize device manager (result = %d)!\n"), result);
		goto FINALLY;
	}
	printf(N_T("done\n"));

	/** get number of cameras in the system */
	result = NDeviceManagerGetDeviceCount(hDeviceManager, &deviceCount);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get number of microphones (result = %d)!\n"), result);
		goto FINALLY;
	}

	/** enumerate cameras */
	for (i = 0; i < deviceCount; i++)
	{
		NInt j;
		const NChar * szDisplayName;

		result = NDeviceManagerGetDevice(hDeviceManager, i, &hDevice);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get device (result = %d)!\n"), result);
			goto FINALLY;
		}

		/** get camera settings */
		result = NDeviceGetDisplayNameN(hDevice, &hDisplayName);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get device name (result = %d)!\n"), result);
			continue;
		}

		result = NStringGetBuffer(hDisplayName, NULL, &szDisplayName);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get device name (result = %d)!\n"), result);
			goto FINALLY;
		}

		printf(N_T("found microphone: %s"), szDisplayName);

		result = NCaptureDeviceStartCapturing(hDevice);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("\nfailed to start microphone (result = %d)!\n"), result);
			goto FINALLY;
		}

		printf(N_T(", capturing:\n"));
		for (j = 0; j < bufferCount; j++)
		{
			NInt sampleRate, length;

			/** get sound buffer from microphone */
			result = NMicrophoneGetSoundSample(hDevice, &hSoundSample);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get sound buffer from microphone (result = %d)!\n"), result);
				goto FINALLY;
			}

			result = NSoundBufferGetSampleRate(hSoundSample, &sampleRate);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get sound buffer sample rate (result = %d)!\n"), result);
				goto FINALLY;
			}

			result = NSoundBufferGetLength(hSoundSample, &length);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get sound buffer sample length (result = %d)!\n"), result);
				goto FINALLY;
			}

			printf(N_T("sample buffer received. sample rate: %d, sample length: %d\n"), sampleRate, length);

			printf(N_T(" ... "));

			result = NObjectSet(NULL, &hSoundSample);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to sound buffer (result = %d)!\n"), result);
				goto FINALLY;
			}
		}

		result = NCaptureDeviceStopCapturing(hDevice);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to stop microphone (result = %d)!\n"), result);
			goto FINALLY;
		}

		result = NStringSet(NULL, &hDisplayName);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to clear display name (result = %d)!\n"), result);
			goto FINALLY;
		}

		result = NObjectSet(NULL, &hDevice);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to clear device (result = %d)!\n"), result);
			goto FINALLY;
		}

		printf(N_T(" done\n"));
	}
	printf(N_T("done\n"));

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hDevice);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hDeviceManager);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hSoundSample);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NStringSet(NULL, &hDisplayName);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result2);
	}

	OnExit();

	return result;
}
