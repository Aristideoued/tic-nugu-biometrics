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

const NChar title[] = N_T("ShowImageInfo");
const NChar description[] = N_T("Displays information about an image");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [filename]" << endl << endl;
	cout << "\tfilename - image filename." << endl;
	return 1;
}

#define VALUE_LENGTH 128

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
		// Obtain license (optional)
		if (!NLicense::Obtain(N_T("/local"), N_T("5000"), license))
		{
			cout << "Could not obtain license: " << license << endl;
		}

		NImage image = NImage::FromFile(argv[1]);
		NImageFormat format = image.GetInfo().GetFormat();
		cout << "Format: " << format.GetName() << endl;
		if (NImageFormat::GetJpeg2K() == format)
		{
			Jpeg2KInfo info = NObjectDynamicCast<Jpeg2KInfo>(image.GetInfo());
			cout << "Profile: " << info.GetProfile() << endl;
			cout << "Compression ratio: " << info.GetRatio();
		}
		else if (NImageFormat::GetJpeg() == format)
		{
			JpegInfo info = NObjectDynamicCast<JpegInfo>(image.GetInfo());
			cout << "Lossless " << info.IsLossless() << endl;
			cout << "Quality: " << info.GetQuality() << endl;
		}
		else if (NImageFormat::GetPng() == format)
		{
			PngInfo info = NObjectDynamicCast<PngInfo>(image.GetInfo());
			cout << "Compression level " << info.GetCompressionLevel() << endl;
		}
		else if (NImageFormat::GetWsq() == format)
		{
			WsqInfo info = NObjectDynamicCast<WsqInfo>(image.GetInfo());
			cout << "Bit rate: " << info.GetBitRate() << endl;
			cout << "Implementation number: " << info.GetImplementationNumber() << endl;
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
