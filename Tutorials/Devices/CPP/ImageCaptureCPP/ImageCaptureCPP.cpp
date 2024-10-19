#include <TutorialUtils.hpp>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NMedia/NMedia.hpp>
	#include <NDevices/NDevices.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NMedia.hpp>
	#include <NDevices.hpp>
	#include <NLicensing.hpp>
#endif

using namespace std;
using namespace Neurotec;
using namespace Neurotec::Images;
using namespace Neurotec::Licensing;
using namespace Neurotec::Devices;

const NChar title[] = N_T("ImageCapture");
const NChar description[] = N_T("Demonstrates capturing images from cameras");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [frameCount]" << endl << endl;
	cout << "\tframeCount - number of frames to capture from each camera to current directory" << endl;
	return 1;
}

int main(int argc, NChar **argv)
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

	const NString license = N_T("FaceExtractor");
	//const NString license = N_T("FaceClient");
	//const NString license = N_T("FaceFastExtractor");

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

		int frameCount = atoi(argv[1]);
		if (frameCount <= 0)
		{
			cout << "No frames will be captured as frame count is not specified";
			return -1;
		}

		NDeviceManager deviceManger;
		deviceManger.SetDeviceTypes(ndtCamera);
		deviceManger.SetAutoPlug(true);
		deviceManger.Initialize();
		cout << "Device manager created found cameras: " << deviceManger.GetDevices().GetCount() << endl;
		for (int i = 0; i < deviceManger.GetDevices().GetCount(); i++)
		{
			NDevice device = deviceManger.GetDevices().Get(i);
			NCamera camera = NObjectDynamicCast<NCamera>(device);
			cout << "Found camera " << camera.GetDisplayName();
			camera.StartCapturing();
			cout << ", capturing" << endl;
			for (int j = 0; j < frameCount; j++)
			{
				NImage image = camera.GetFrame();
				NString fileName = NString::Format("{S}_{I}.jpg", camera.GetDisplayName().GetBuffer(), j);
				image.Save(fileName);
			}
			camera.StopCapturing();
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
