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

const NChar title[] = N_T("FMCRecordToNTemplate");
const NChar description[] = N_T("Demonstrates creation of NTemplate from FMCRecord");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2017-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [FMCRecord] [NTemplate] [Version] [MinutiaeFormat] [ReadBerTlv] " << endl << endl;
	cout << "\tFMCRecord - filename with FMCRecord" << endl;
	cout << "\tNTemplate - filename for NTemplate" << endl;
	cout << "\tVersion - FMCRecord version" << endl;
	cout << "\t\tISO2 - ISO/IEC 19794-2:2005" << endl;
	cout << "\t\tISO3 - ISO/IEC 19794-2:2011" << endl;
	cout << "\tMinutiaeFormat - card format of minutiae data" << endl;
	cout << "\t\tC - compact size" << endl;
	cout << "\t\tN - normal size (ISO2 only)" << endl;
	cout << "\tReadBerTlvDo - FMCRecord read from buffer option" << endl;
	cout << "\t\t1 - Biometric Data Template (BDT) or Cardholder" << endl;
	cout << "\t\t    Biometric Data (CBD) BER-TLV DO (Data Object)" << endl;
	cout << "\t\t0 - minutiae data buffer only.\n" << endl;
	cout << "example:" << endl;
	cout << "\t" << title << " fmcRecord.FMCRecord template.NTemplate ISO3 C 1" << endl;
	return 1;
}

int main(int argc, NChar **argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 6)
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

		NVersion standardVersion;
		if (!strcmp(argv[3], N_T("ISO2")))
			standardVersion = FMCR_VERSION_ISO_2_0 ;
		else if (!strcmp(argv[3], N_T("ISO3")))
			standardVersion = FMCR_VERSION_ISO_3_0;
		else
			NThrowException("Wrong standard");

		FmcrMinutiaFormat minutiaFormat;
		if (!strcmp(argv[4], N_T("C")))
			minutiaFormat = fmcrmfCompactSize;
		else if (!strcmp(argv[4], N_T("N")))
			minutiaFormat = fmcrmfNormalSize;
		else
			NThrowException("Wrong minutia format");

		// Check if full FMCRecord BER-TLV Data Object (DO) (e.g., Biometric Data Template (BDT) or Cardholder Biometric Data (CBD)) or minutiae buffer only is available
		NBool isBerTlv = !strcmp(argv[5], N_T("1")) ? NTrue : NFalse;

		NBuffer storedFmcRecord = NFile::ReadAllBytes(argv[1]);

		BdifStandard standard = bsIso;
		NUInt flags = 0; // BDIF_NON_STRICT_READ - removes non-unique minutiae for FMCR_VERSION_ISO_3_0 only
		FMCRecord fmcRecord = NULL;
		if (isBerTlv)
		{
			// Create FMCRecord object from FMCRecord BER-TLV Data Object (DO) stored in memory (e.g., BDT or CBD BER-TLV DO)
			fmcRecord = FMCRecord(storedFmcRecord, standard, standardVersion, minutiaFormat, flags);
		}
		else
		{
			// Create FMCrecord and read minutiae data from buffer to FMCRecord
			fmcRecord = FMCRecord(standard, standardVersion, minutiaFormat, 0);
			fmcRecord.SetMinutiaeBuffer(storedFmcRecord);
		}

		// Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
		if (fmcRecord.GetVersion() == FMCR_VERSION_ISO_2_0 && !fmcRecord.ValidateMinutiaeUniqueness())
		{
			cout << "!!!WARNING!!!:" << endl;
			cout << "Not all minutiae in FMCRecord are unique!" << endl;
			cout << "Please, try using ISO3 version with BDIF_NON_STRICT_READ flag to remove non-unique minutiae while reading." << endl;
		}

		// Convert FMCRecord to NFRecord
		NFRecord nfRecord = fmcRecord.ToNFRecord();

		// Add NFRecord to NFTemplate
		NFTemplate nfTemplate;
		nfTemplate.GetRecords().Add(nfRecord);
		// Set NFTemplate to NTemplate
		NTemplate nTemplate;
		nTemplate.SetFingers(nfTemplate);

		// Pack NTemplate object
		NBuffer packedNTemplate = nTemplate.Save();
		NFile::WriteAllBytes(argv[2], packedNTemplate);
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
