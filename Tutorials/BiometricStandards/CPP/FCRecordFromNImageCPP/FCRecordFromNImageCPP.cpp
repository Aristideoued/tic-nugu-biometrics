#include <TutorialUtils.hpp>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NBiometrics/NBiometrics.hpp>
	#include <NMedia/NMedia.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NBiometrics.hpp>
	#include <NMedia.hpp>
	#include <NLicensing.hpp>
#endif

using namespace std;
using namespace Neurotec;
using namespace Neurotec::IO;
using namespace Neurotec::Images;
using namespace Neurotec::Licensing;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Biometrics::Standards;

const NChar title[] = N_T("FCRecordFromNImage");
const NChar description[] = N_T("Demonstrates creation of FCRecord from image");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [FCRecord] {[image]}" << endl << endl;
	cout << "\tFCRecord - output FCRecord" << endl;
	cout << "\t[Standard] - standard for the record (ISO or ANSI)" << endl;
	cout << "\t[Version] - version for the record" << endl;
	cout << "\t\t 1 - ANSI/INCITS 375-2004" << endl;
	cout << "\t\t 1 - ISO/IEC 19794-5:2005" << endl;
	cout << "\t\t 3 - ISO/IEC 19794-5:2011" << endl;
	cout << "\timage    - one or more images" << endl;
	return 1;
}

int main(int argc, NChar *argv[])
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 5)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NString license = N_T("FaceClient");
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

		BdifStandard standard;
		if (!strcmp(argv[2], N_T("ANSI")))
			standard = bsAnsi;
		else if (!strcmp(argv[2], N_T("ISO")))
			standard = bsIso;
		else
			NThrowException("Wrong standard");

		NVersion recordVersion;
		if (!strcmp(argv[3], N_T("1")))
		{
			recordVersion = standard == bsAnsi ? FCR_VERSION_ANSI_1_0 : FCR_VERSION_ISO_1_0;
		}
		else if (!strcmp(argv[3], N_T("3")))
		{
			if (standard != bsIso)
				NThrowException("Standard and version is incompatible!");
			recordVersion = FCR_VERSION_ISO_3_0;
		}
		else
			NThrowException("Wrong version!");

		if (argc > 4)
		{
			FCRecord fcRecord = NULL;
			for (int i = 4; i < argc; i++)
			{
				/*	
				Reads image data from file.
				Image must be compressed using valid compression algorithm for IIRecord.
				How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
				*/
				NBuffer imageBuffer = NFile::ReadAllBytes(argv[i]);

				if (fcRecord.IsNull())
				{
					fcRecord = FCRecord(standard, recordVersion, fcrfitBasic, imageBuffer);
				}
				else
					fcRecord.GetFaceImages().Add(fcrfitBasic, imageBuffer);
			}

			NFile::WriteAllBytes(argv[1], fcRecord.Save());
			cout << "FCRecord saved to " << argv[1];
		}
		else
			cout << "No images were added to FCRecord";
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
