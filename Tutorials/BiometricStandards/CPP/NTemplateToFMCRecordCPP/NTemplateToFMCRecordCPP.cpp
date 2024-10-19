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

const NChar title[] = N_T("NTemplateToFMCRecord");
const NChar description[] = N_T("Demonstrates creation of FMCRecord from NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2017-2024 Neurotechnology");

const NByte minutiaTruncationQualityThreshold = 0;
 /* NOTE: ISO/IEC 19794-2 (informative) minutiae count range recommendations for card formats:
  - FMCR_DEFAULT_MIN_ENROLL_MC to FMCR_DEFAULT_MAX_ENROLL_MC for enroll, 
  - FMCR_DEFAULT_MIN_VERIFY_MC to FMCR_DEFAULT_MAX_VERIFY_MC for verify.
  */
const NInt minutiaTruncationMaximalCount = 48;
const NFMinutiaTruncationAlgorithm minutiaTruncationAlgorithm = nfmtaQualityAndCenterOfMass; 

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [NTemplate] [FMCRecord] [Version] [MinutiaeFormat] [SaveBiometricDataTemplate]" << endl << endl;
	cout << "\tNTemplate - filename with NTemplate" << endl;
	cout << "\tFMCRecord - filename with FMCRecord" << endl;
	cout << "\tVersion - ISO standard version for FMCRecord" << endl;
	cout << "\t\tISO2 - ISO/IEC 19794-2:2005" << endl;
	cout << "\t\tISO3 - ISO/IEC 19794-2:2011" << endl;
	cout << "\tMinutiaeFormat - card format of minutiae data" << endl;
	cout << "\t\tC - compact size" << endl;
	cout << "\t\tN - normal size (ISO2 only)" << endl;
	cout << "\tSaveBiometricDataTemplate - FMCRecord save to buffer option" << endl;
	cout << "\t\t1 - full Biometric Data Template (BDT) BER-TLV DO (Data Object)" << endl;
	cout << "\t\t0 - minutiae data only" << endl;
	cout << "example:" << endl;
	cout << "\t" << title << " template.NTemplate fmcrecord.FMCRecord ISO3 C 1" << endl;
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

		BdifStandard standard = bsIso;
		NVersion standardVersion;
		FmcrMinutiaOrder minutiaOrder = fmcrmoNone;
		NUInt flags = FMCR_SKIP_ALL_EXTENDED_DATA | FMCR_USE_BIOMETRIC_DATA_TEMPLATE; // the most common use case of minutiae data only within on-card records
		if (!strcmp(argv[3], N_T("ISO2")))
		{
			standardVersion = FMCR_VERSION_ISO_2_0;
		}
		else if (!strcmp(argv[3], N_T("ISO3")))
		{
			standardVersion = FMCR_VERSION_ISO_3_0;
		}
		else
			NThrowException("Wrong standard version");

		FmcrMinutiaFormat minutiaFormat;
		if (!strcmp(argv[4], N_T("C")))
		{
			minutiaFormat = fmcrmfCompactSize;
		}
		else if (!strcmp(argv[4], N_T("N")))
		{
			minutiaFormat = fmcrmfNormalSize;
		}
		else
		{
			NThrowException("Wrong minutia format");
		}

		// Check if full FMCRecord Biometric Data Template (BDT) BER-TLV Data Object (DO) or minutiae buffer only to be saved
		NBool isBdtBerTlv = !strcmp(argv[5], N_T("1")) ? NTrue : NFalse;

		NBuffer packedNTemplate = NFile::ReadAllBytes(argv[1]);
		NTemplate nTemplate = NTemplate(packedNTemplate);
		NFTemplate nfTemplate = nTemplate.GetFingers();
		if (!nfTemplate.IsNull() && nfTemplate.GetRecords().GetCount() > 0) 
		{
			// Retrieve NFRecord object from NFTemplate object
			NFRecord nfRecord = nfTemplate.GetRecords().Get(0);

			// Truncate minutiae by quality
			nfRecord.TruncateMinutiaeByQuality(minutiaTruncationQualityThreshold, minutiaTruncationMaximalCount);

			// Truncate minutiae using specified truncation algorithm (if more than desired minutiae with quality above minutiaTruncationQualityThreshold remain)
			nfRecord.TruncateMinutiae(minutiaTruncationAlgorithm, minutiaTruncationMaximalCount);

			// Create FMCRecord object from NFRecord object
			FMCRecord fmcRecord = FMCRecord(nfRecord, standard, standardVersion, minutiaFormat, minutiaOrder, 0);

			// Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
			if (fmcRecord.GetVersion() == FMCR_VERSION_ISO_2_0 && !fmcRecord.ValidateMinutiaeUniqueness())
			{
				cout << "!!!WARNING!!!:" << endl;
				cout << "Not all minutiae in FMCRecord are unique!" << endl;
				cout << "Please, try using ISO3 version to remove non-unique minutiae while conversion." << endl;
			}

			if (isBdtBerTlv)
			{
				// Store FMCRecord object in memory as ISO/IEC 19794-2 and ISO/IEC 7816-11 compliant Biometric Data Template (BDT) BER-TLV Data Object (DO)
				NBuffer storedFmcRecord = fmcRecord.Save(flags);
				NFile::WriteAllBytes(argv[2], storedFmcRecord);
			}
			else
			{
				// Get minutiae data as buffer
				NBuffer minutiaeBuffer = fmcRecord.GetMinutiaeBuffer();
				NFile::WriteAllBytes(argv[2], minutiaeBuffer);
			}
		}
		else
		{
			cout << "There are no NFRecords in NTemplate" << endl;
		}

	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
