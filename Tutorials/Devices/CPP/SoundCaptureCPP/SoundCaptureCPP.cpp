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
using namespace Neurotec::Licensing;
using namespace Neurotec::Devices;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Sound;

const NChar title[] = N_T("SoundCapture");
const NChar description[] = N_T("Demonstrates capturing sound from microphones");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [bufferCount]" << endl << endl;
	cout << "\tbufferCount - number of sound buffers to capture from each microphone to current directory" << endl;
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

	const NString license = N_T("VoiceExtractor");
	//const NString license = N_T("VoiceClient");
	//const NString license = N_T("VoiceFastExtractor");

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
		
		int bufferCount = atoi(argv[1]);
		if (bufferCount <= 0)
		{
			cout << "No sound buffers will be captured as sound buffer count is not specified";
			return -1;
		}

		NDeviceManager deviceManager;
		deviceManager.SetDeviceTypes(ndtMicrophone);
		deviceManager.SetAutoPlug(true);
		deviceManager.Initialize();

		cout << "Device manager created. Found microphones: " << deviceManager.GetDevices().GetCount() << endl;
		for (int i = 0; i < deviceManager.GetDevices().GetCount(); i++)
		{
			NDevice device = deviceManager.GetDevices().Get(i);
			NMicrophone microphone = NObjectDynamicCast<NMicrophone>(device);
			cout << "Found microphone " << microphone.GetDisplayName() << endl;
			microphone.StartCapturing();
			cout << "Capturing" << endl;
			for (int j = 0; j < bufferCount; j++)
			{
				NSoundBuffer soundSample = microphone.GetSoundSample();
				cout << "Sample buffer received. sample rate: " << soundSample.GetSampleRate() << ", sample lenght: " << soundSample.GetLength() << endl;
				cout << " ... ";
			}
			microphone.StopCapturing();
			cout << "Done";
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
