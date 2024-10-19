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

const NChar title[] = N_T("FIRecordFromImage");
const NChar description[] = N_T("Demonstrates creation of FIRecord from image data");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << "[FIRecord] [Standard] [Version] [Encoding] {[image]}" << endl << endl;
	cout << "\tFIRecord - output FIRecord" << endl;
	cout << "\t[Standard] - standard for the record (ISO or ANSI)" << endl;
	cout << "\t[Version] - version for the record" << endl;
	cout << "\t\t 1 - ANSI/INCITS 381-2004" << endl;
	cout << "\t\t 1 - ISO/IEC 19794-4:2005" << endl;
	cout << "\t\t 2 - ISO/IEC 19794-4:2011" << endl;
	cout << "\t\t 2.5 - ANSI/INCITS 381-2009" << endl;
	cout << "\t[Encoding] - encoding format\n" << endl;
	cout << "\t\t bin - Traditional binary encoding \n" << endl;
	cout << "\t\t xml - XML encoding (supported only for ISO v2)\n" << endl;
	cout << "\timage    - one or more images" << endl;
	return 1;
}

int main(int argc, NChar *argv[])
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 6)
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

		BdifStandard standard = bsIso;
		BdifEncodingType encoding = betTraditional;
		NVersion recordVersion;
		if (!strcmp(argv[2], N_T("ANSI")))
			standard = bsAnsi;
		else if (!strcmp(argv[2], N_T("ISO")))
			standard = bsIso;
		else
			NThrowException("Wrong standard!");

		if (!strcmp(argv[3], N_T("1")))
		{
			if (standard == bsAnsi)
				recordVersion = FIR_VERSION_ANSI_1_0;
			else
				recordVersion = FIR_VERSION_ISO_1_0;
		}
		else if (!strcmp(argv[3], N_T("2")))
		{
			if (standard != bsIso)
				NThrowException("Standard and version is incompatible!");
			recordVersion = FIR_VERSION_ISO_2_0;
		}
		else if (!strcmp(argv[3], N_T("2.5")))
		{
			if (standard != bsAnsi)
				NThrowException("Standard and version is incompatible!");
			recordVersion = FIR_VERSION_ANSI_2_5;
		}
		else
			NThrowException("Wrong version!");

		if (!strcmp(argv[4], N_T("bin")))
			encoding = betTraditional;
		else if (!strcmp(argv[4], N_T("xml")))
		{
			if (standard != bsIso || recordVersion != FIR_VERSION_ISO_2_0)
				NThrowException("xml encoding is only availaable for ISO v2.0");
			encoding = betXml;
		}
		else
			NThrowException("Wrong encoding!");

		BdifFPPosition fPosition = bfppRightThumb;
		NUShort vertScanResolution = 500;//ppi
		NUShort horzScanResolution = 500;//ppi
		FIRecord fiRecord = NULL;
		for (int i = 5; i < argc; i++)
		{
			/*	
			Reads image data from file.
			Image must be compressed using valid compression algorithm for FIRecord.
			How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			*/
			NBuffer imageBuffer = NFile::ReadAllBytes(argv[i]);

			if (fiRecord.IsNull())
			{
				fiRecord = FIRecord(standard, recordVersion, (NUShort)10, fPosition, horzScanResolution, vertScanResolution, imageBuffer);
			}
			else
				FirFingerView fingerView = fiRecord.GetFingerViews().Add(fPosition, horzScanResolution, vertScanResolution, imageBuffer);
		}

		if (!fiRecord.IsNull())
		{
			NFile::WriteAllBytes(argv[1], fiRecord.Save(encoding));
			cout << "FIRecord saved to " << argv[1] << endl;
		}
		else
			cout << "No images were added to FIRecord" << endl;
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
