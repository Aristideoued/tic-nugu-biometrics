#include <TutorialUtils.hpp>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NMedia/NMedia.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NMedia.hpp>
	#include <NLicensing.hpp>
#endif

using namespace std;
using namespace Neurotec;
using namespace Neurotec::Licensing;
using namespace Neurotec::Images;
using namespace Neurotec::IO;

const NChar title[] = N_T("CreateWsq");
const NChar description[] = N_T("Demonstrates WSQ format image creation from another image");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [srcImage] [dstImage] <optional: bitRate>" << endl << endl;
	cout << "\tsrcImage- filename of source finger image." << endl;
	cout << "\tdstImage - name of a file to save the created WSQ image to." << endl;
	cout << "\ttbitRate  - specifies WSQ image compression level. Typical bit rates: 0.75, 2.25." << endl;
	return 1;
}

int main(int argc, NChar **argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 3)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NString license = N_T("FingerClient");
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

		NImage image = NImage::FromFile(argv[1]);
		WsqInfo info = NObjectDynamicCast<WsqInfo>(NImageFormat::GetWsq().CreateInfo(image));
		float bitrate;
		if (argc > 3)
			bitrate = (float)atof(argv[3]);
		else
			bitrate = WSQ_DEFAULT_BIT_RATE;
		info.SetBitRate(bitrate);
		image.Save(argv[2], info.GetFormat(), info);

		cout << "WSQ image with bit rate " << bitrate << " was saved to: " << argv[2];
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
