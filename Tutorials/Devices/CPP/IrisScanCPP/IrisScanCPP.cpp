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
using namespace Neurotec::Images;
using namespace Neurotec::Licensing;
using namespace Neurotec::Devices;
using namespace Neurotec::Biometrics;

const NChar title[] = N_T("IrisScan");
const NChar description[] = N_T("Demonstrates capturing iris image from iris scanner");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int main()
{
	OnStart(title, description, version, copyright, 0, NULL);

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NString license = N_T("IrisExtractor");
	//const NString license = N_T("IrisClient");
	//const NString license = N_T("IrisFastExtractor");

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

		NDeviceManager deviceManager;
		deviceManager.SetDeviceTypes(ndtIrisScanner);
		deviceManager.SetAutoPlug(true);
		deviceManager.Initialize();

		cout << "Device manager created. Found scanners: " << deviceManager.GetDevices().GetCount() << endl;
		for (int i = 0; i < deviceManager.GetDevices().GetCount(); i++)
		{
			NDevice device = deviceManager.GetDevices().Get(i);
			NIrisScanner scanner = NObjectDynamicCast<NIrisScanner>(device);
			cout << "Found scanner " << scanner.GetDisplayName() << endl;
			cout << "\tCapturing right iris: ";
			NIris rightIris;
			rightIris.SetPosition(nepRight);
			NBiometricStatus status = scanner.Capture(rightIris, -1);
			if (status != nbsOk)
			{
				cout << "Failed to capture from scanner, status: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status) << endl;
				continue;
			}

			NString fileName = NString::Format("{S}_iris_right.jpg", scanner.GetDisplayName().GetBuffer());
			rightIris.GetImage().Save(fileName);
			cout << "Done" << endl << "\tCapturing left eye: ";
			NIris leftIris;
			leftIris.SetPosition(nepLeft);
			status = scanner.Capture(leftIris, -1);
			if (status != nbsOk)
			{
				cout << "Failed to capture from scanner, status: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status) << endl;
				continue;
			}
			fileName = NString::Format("{S}_iris_left.jpg", scanner.GetDisplayName().GetBuffer());
			leftIris.GetImage().Save(fileName);
			cout << "Done" << endl;
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
