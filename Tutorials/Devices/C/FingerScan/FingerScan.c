#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NMedia/NMedia.h>
	#include <NDevices/NDevices.h>
	#include <NBiometrics/NBiometrics.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NMedia.h>
	#include <NDevices.h>
	#include <NBiometrics.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("FingerScan");
const NChar description[] = N_T("Demonstrates fingerprint image capturing from scanner");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [imageCount]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\t[imageCount] - count of fingerprint images to be scanned.\n"));
	printf(N_T("\n\nexample:\n"));
	printf(N_T("\t%s 3\n"), title);

	return 1;
}

int main(int argc, NChar **argv)
{
	HNDeviceManager hDeviceManager = NULL;
	HNDevice hDevice = NULL;
	HNImage hImage = NULL;
	HNFinger hFinger = NULL;
	NInt imageCount;
	NResult result = N_OK;
	NInt scannerCount = 0;
	NInt i;
	NBool available = NFalse;
	HNString hDisplayName = NULL;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("FingerExtractor");
	//const NChar * license = N_T("FingerClient");
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

	imageCount = atoi(argv[1]);
	if (imageCount == 0)
	{
		printf(N_T("no images will be captured as images count is not specified"));
	}

	printf(N_T("creating device manager ...\n"));
	result = NDeviceManagerCreateEx(&hDeviceManager);
	if (NFailed(result))
	{
		PrintErrorMsgWithLastError(N_T("failed to create device manager failed (result = %d)\n"), result);
		goto FINALLY;
	}
	result = NDeviceManagerSetDeviceTypes(hDeviceManager, ndtFScanner);
	if (NFailed(result))
	{
		PrintErrorMsgWithLastError(N_T("failed to set device types (result = %d)!\n"), result);
		goto FINALLY;
	}
	result = NDeviceManagerSetAutoPlug(hDeviceManager, NTrue);
	if (NFailed(result))
	{
		PrintErrorMsgWithLastError(N_T("failed to set auto plug (result = %d)!\n"), result);
		goto FINALLY;
	}

	result = NDeviceManagerInitialize(hDeviceManager);
	if (NFailed(result))
	{
		PrintErrorMsgWithLastError(N_T("failed to initialize device manager (result = %d)!\n"), result);
		goto FINALLY;
	}

	result = NDeviceManagerGetDeviceCount(hDeviceManager, &scannerCount);
	if (NFailed(result))
	{
		PrintErrorMsgWithLastError(N_T("failed to get number of scanners (result = %d)!\n"), result);
		goto FINALLY;
	}
	printf(N_T("done\n"));

	for (i = 0; i < scannerCount; i++)
	{
		NInt j;
		const NChar * szDisplayName;

		result = NDeviceManagerGetDevice(hDeviceManager, i, &hDevice);
		if (NFailed(result))
		{
			PrintErrorMsgWithLastError(N_T("failed to get device (result = %d)!\n"), result);
			goto FINALLY;
		}

		result = NDeviceGetDisplayNameN(hDevice, &hDisplayName);
		if (NFailed(result))
		{
			PrintErrorMsgWithLastError(N_T("failed to get device name (result = %d)!\n"), result);
			goto FINALLY;
		}

		result = NStringGetBuffer(hDisplayName, NULL, &szDisplayName);
		if (NFailed(result))
		{
			PrintErrorMsgWithLastError(N_T("failed to get device name (result = %d)!\n"), result);
			goto FINALLY;
		}

		printf(N_T("capturing from scanner: %s\n"), szDisplayName);

		for (j = 0; j < imageCount; j++)
		{
			NBiometricStatus status;
			NChar szFilename[1024];
			sprintf(szFilename, N_T("%s_%.4d.png"), szDisplayName, j);

			result = NFingerCreate(&hFinger);
			if (NFailed(result))
			{
				PrintErrorMsgWithLastError(N_T("failed to create capture biometric (result = %d)!\n"), result);
				goto FINALLY;
			}
			// set position we want to capture
			result = NFrictionRidgeSetPosition(hFinger, nfpUnknown);
			if (NFailed(result))
			{
				PrintErrorMsgWithLastError(N_T("failed to set capture biometric position (result = %d)!\n"), result);
				goto FINALLY;
			}

			printf(N_T("\timage %d of %d. please put your fingerprint on scanner:"), j + 1, imageCount);
			result = NBiometricDeviceCapture(hDevice, hFinger, -1, &status);
			if (NFailed(result))
			{
				PrintErrorMsgWithLastError(N_T("failed to capture image from scanner (result = %d)!\n"), result);
				goto FINALLY;
			}

			if (status == nbsOk)
			{
				result = NFrictionRidgeGetImage(hFinger, &hImage);
				if (NFailed(result))
				{
					PrintErrorMsgWithLastError(N_T("failed to get image from biometric (result = %d)!\n"), result);
					goto FINALLY;
				}

				result = NImageSaveToFileEx(hImage, szFilename, NULL, NULL, 0);
				if (NFailed(result))
				{
					PrintErrorMsgWithLastError(N_T("failed to  save image to file (result = %d)!\n"), result);
					goto FINALLY;
				}

				printf(N_T(" image captured\n"));
			}
			else
			{
				printf(N_T(" image capture failed, status: %d\n"), status);
			}

			result = NObjectSet(NULL, &hImage);
			if (NFailed(result))
			{
				PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
				goto FINALLY;
			}

			result = NObjectSet(NULL, &hFinger);
			if (NFailed(result))
			{
				PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
				goto FINALLY;
			}
		}
		result = NStringSet(NULL, &hDisplayName);
		if (NFailed(result))
		{
			PrintErrorMsgWithLastError(N_T("NStringSet() failed (result = %d)!"), result);
			goto FINALLY;
		}
		result = NObjectSet(NULL, &hDevice);
		if (NFailed(result))
		{
			PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
			goto FINALLY;
		}
		printf(N_T("\tdone\n"));
	}
	printf(N_T("done\n"));

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hDevice);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hDeviceManager);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hImage);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFinger);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NStringSet(NULL, &hDisplayName);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result2);
	}

	OnExit();

	return result;
}
