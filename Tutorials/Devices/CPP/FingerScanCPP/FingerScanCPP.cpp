#include <TutorialUtils.hpp>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NMedia/NMedia.hpp>
	#include <NDevices/NDevices.hpp>
	#include <NBiometrics/NBiometrics.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NMedia.hpp>
	#include <NDevices.hpp>
	#include <NBiometrics.hpp>
	#include <NLicensing.hpp>
#endif

using namespace std;
using namespace Neurotec;
using namespace Neurotec::Licensing;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Devices;

const NChar title[] = N_T("FingerScan");
const NChar description[] = N_T("Demonstrates fingerprint image capturing from scanner");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [imageCount]" << endl << endl;
	cout << "\t[imageCount] - count of fingerprint images to be scanned." << endl << endl << endl;
	cout << "example: " << endl;
	cout << "\t" << title << " 3" << endl;
	return 1;
}

int main(int argc, NChar ** argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 2)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NString license = N_T("FingerExtractor");
	//const NString license = N_T("FingerClient");
	//const NString license = N_T("FingerFastExtractor");

	//=========================================================================

	//=========================================================================
	// TRIAL MODE
	//=========================================================================
	// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
	// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
	// Also you can just set TRUE to "TrialMode" property in code.

	NLicenseManager::SetTrialMode(GetTrialModeFlag());
	cout << "Trial mode: " << NLicenseManager::GetTrialMode() << endl;

	//=========================================================================

	try
	{
		// Obtain license
		if (!NLicense::Obtain(N_T("/local"), N_T("5000"), license))
		{
			NThrowException(NString::Format(N_T("Could not obtain license: {S}"), license.GetBuffer())); 
		}

		int imageCount = atoi(argv[1]);
		if (imageCount <= 0)
		{
			cout << "No frames will be captured as frame count is not specified";
			return -1;
		}

		NDeviceManager deviceManager;
		deviceManager.SetDeviceTypes(ndtFScanner);
		deviceManager.SetAutoPlug(true);
		deviceManager.Initialize();

		cout << "Device manager created. Found scanners: " << deviceManager.GetDevices().GetCount() << endl;
		for (int i = 0; i < deviceManager.GetDevices().GetCount(); i++)
		{
			NDevice device = deviceManager.GetDevices().Get(i);
			NFScanner scanner = NObjectDynamicCast<NFScanner>(device);
			cout << "Found scanner " << scanner.GetDisplayName()<< ", capturing fingerprints" << endl;
			for (int j = 0; j < imageCount; j++)
			{
				cout << "\tImage " <<  j + 1 << " of " << imageCount << ". Please put your finger on scanner: ";
				NString fileName = NString::Format("{S}_{I}.jpg", scanner.GetDisplayName().GetBuffer(), j);
				NFinger finger;
				finger.SetPosition(nfpUnknown);
				NBiometricStatus status = scanner.Capture(finger, -1);
				if (status != nbsOk)
				{
					cout << "Failed to capture from scanner, status: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status) << endl;
					continue;
				}
				finger.GetImage().Save(fileName);
				cout << "Image captured" << endl;
			}
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
