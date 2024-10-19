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

const NChar title[] = N_T("IrisScan");
const NChar description[] = N_T("Demonstrates capturing iris image from iris scanner");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

int main()
{
	HNDeviceManager hDeviceManager = NULL;
	HNDevice hDevice = NULL;
	HNImage hImage = NULL;
	HNIris hIris = NULL;
	HNString hDisplayName = NULL;
	NResult result = N_OK;
	NInt scannerCount;
	NInt i;
	NBool available = NFalse;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("IrisExtractor");
	//const NChar * license = N_T("IrisClient");
	//const NChar * license = N_T("IrisFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, 0, NULL);

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

	printf(N_T("creating device manager ...\n"));
	result = NDeviceManagerCreateEx(&hDeviceManager);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to create device manager failed (result = %d)\n"), result);
		goto FINALLY;
	}
	result = NDeviceManagerSetDeviceTypes(hDeviceManager, ndtIrisScanner);
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

	result = NDeviceManagerGetDeviceCount(hDeviceManager, &scannerCount);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to get number of scanners (result = %d)!\n"), result);
		goto FINALLY;
	}

	for (i = 0; i < scannerCount; i++)
	{
		NBiometricStatus status;
		const NChar * szDisplayName;

		result = NDeviceManagerGetDevice(hDeviceManager, i, &hDevice);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get device (result = %d)!\n"), result);
			continue;
		}

		result = NDeviceGetDisplayNameN(hDevice, &hDisplayName);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get device name (result = %d)!\n"), result);
			goto FINALLY;
		}
		result = NStringGetBuffer(hDisplayName, NULL, &szDisplayName);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to get device name (result = %d)!\n"), result);
			goto FINALLY;
		}

		printf(N_T("found scanner: %s\n"), szDisplayName);

		printf(N_T("\tcapturing right iris: "));

		result = NIrisCreate(&hIris);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to create capture biometric (result = %d)!\n"), result);
			goto FINALLY;
		}
		// set position we want to capture
		result = NIrisSetPosition(hIris, nepRight);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to set capture biometric position (result = %d)!\n"), result);
			goto FINALLY;
		}

		// if you want to know th capture status - use NIrisScannerCaptureEx instead
		result = NBiometricDeviceCapture(hDevice, hIris, -1, &status);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to capture image from scanner (result = %d)!\n"), result);
			goto FINALLY;
		}

		if (status == nbsOk)
		{
			NChar szFilename[1024];
			sprintf(szFilename, N_T("%s_%d_iris_right.jpg"), szDisplayName, i);

			result = NIrisGetImage(hIris, &hImage);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get image from biometric (result = %d)!\n"), result);
				goto FINALLY;
			}

			result = NImageSaveToFileEx(hImage, szFilename, NULL, NULL, 0);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to save image to file (result = %d)!\n"), result);
				goto FINALLY;
			}

			result = NObjectSet(NULL, &hImage);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to clear image (result = %d)!\n"), result);
				goto FINALLY;
			}

			printf(N_T("done\n"));
		}
		else
		{
			printf(N_T(" image capture failed, status: %d\n"), status);
		}

		result = NObjectSet(NULL, &hIris);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to clear iris biometric (result = %d)!\n"), result);
			goto FINALLY;
		}

		printf(N_T("\tcapturing left iris: "));

		result = NIrisCreate(&hIris);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to create capture biometric (result = %d)!\n"), result);
			goto FINALLY;
		}
		// set position we want to capture
		result = NIrisSetPosition(hIris, nepLeft);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to set capture biometric position (result = %d)!\n"), result);
			goto FINALLY;
		}

		// if you want to know th capture status - use NIrisScannerCaptureEx instead
		result = NBiometricDeviceCapture(hDevice, hIris, -1, &status);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to capture image from scanner (result = %d)!\n"), result);
			goto FINALLY;
		}

		if (status == nbsOk)
		{
			NChar szFilename[1024];
			sprintf(szFilename, N_T("%s_%d_iris_left.jpg"), szDisplayName, i);

			result = NIrisGetImage(hIris, &hImage);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to get image from biometric (result = %d)!\n"), result);
				goto FINALLY;
			}

			result = NImageSaveToFileEx(hImage, szFilename, NULL, NULL, 0);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to save image to file (result = %d)!\n"), result);
				goto FINALLY;
			}

			result = NObjectSet(NULL, &hImage);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("failed to clear image (result = %d)!\n"), result);
				goto FINALLY;
			}

			printf(N_T("done\n"));
		}
		else
		{
			printf(N_T(" image capture failed, status: %d\n"), status);
		}

		result = NObjectSet(NULL, &hIris);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to clear iris biometric (result = %d)!\n"), result);
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
		result2 = NObjectSet(NULL, &hIris);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hImage);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NStringSet(NULL, &hDisplayName);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result2);
	}

	OnExit();

	return result;
}
