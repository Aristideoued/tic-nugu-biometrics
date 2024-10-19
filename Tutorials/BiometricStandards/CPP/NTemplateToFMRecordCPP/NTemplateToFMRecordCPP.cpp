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

const NChar title[] = N_T("NTemplateToFMRecord");
const NChar description[] = N_T("Demonstrates creation of FMRecord from NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [NTemplate] [FMRecord] [Standard&Version] [FlagUseNeurotecFields] [Encoding]" << endl << endl;
	cout << "\tNTemplate - filename with NTemplate" << endl;
	cout << "\tFMRecord  - filename with FMRecord" << endl;
	cout << "\tStandard & Version - FMRecord standard & version" << endl;
	cout << "\t\t2 - ANSI/INCITS 378-2004" << endl;
	cout << "\t\t3.5 - ANSI/INCITS 378-2009" << endl;
	cout << "\t\t2 - ISO/IEC 19794-2:2005" << endl;
	cout << "\t\t3 - ISO/IEC 19794-2:2011" << endl;
	cout << "\t\tMINEX - Minex compliant record (ANSI/INCITS 378-2004 without extended data)" << endl;
	cout << "\tFlagUseNeurotecFields - 1 if FMRFV_USE_NEUROTEC_FIELDS flag is used; otherwise, 0 flag was not used. For Minex compliant record must be 0." << endl;
	cout << "example:" << endl;
	cout << "\t" << title << " template.NTemplate fmrecord.FMRecord ISO3 1" << endl;
	cout << "\t" << title << " template.NTemplate fmrecord.FMRecord MINEX 0" << endl;
	cout << "\tEncoding - specifies FMRecord encoding type\n" << endl;
	cout << "\t\t0 - Traditional binary encoding \n" << endl;
	cout << "\t\t1 - XML encoding (supported only for ISO3)\n" << endl;
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

		BdifStandard standard;
		NVersion recordVersion;
		int flags = 0;
		if (!strcmp(argv[3], N_T("ANSI2")))
		{
			standard = bsAnsi;
			recordVersion = FMR_VERSION_ANSI_2_0;
		}
		else if (!strcmp(argv[3], N_T("ISO2")))
		{
			standard = bsIso;
			recordVersion = FMR_VERSION_ISO_2_0;
		}
		else if (!strcmp(argv[3], N_T("ISO3")))
		{
			standard = bsIso;
			recordVersion = FMR_VERSION_ISO_3_0;
		}
		else if (!strcmp(argv[3], N_T("ANSI3.5")))
		{
			standard = bsAnsi;
			recordVersion = FMR_VERSION_ANSI_3_5;
		}
		else if (!strcmp(argv[3], N_T("MINEX")))
		{
			if (!strcmp(argv[4], N_T("1"))) // check if Neurotec flags are used
				NThrowException("MINEX and FlagUseNeurotecFields is incompatible");

			standard = bsAnsi;
			recordVersion = FMR_VERSION_ANSI_3_5;
			flags = FMRFV_SKIP_RIDGE_COUNTS | FMRFV_SKIP_SINGULAR_POINTS | FMRFV_SKIP_NEUROTEC_FIELDS;
		}
		else
			NThrowException("Wrong version");

		flags |= !strcmp(argv[4], N_T("1")) ? FMRFV_USE_NEUROTEC_FIELDS : 0;

		BdifEncodingType encoding = strcmp(argv[5], N_T("1")) == 0 ? betXml : betTraditional;
		NBuffer packedNTemplate = NFile::ReadAllBytes(argv[1]);
		NTemplate nTemplate(packedNTemplate);
		NFTemplate nfTemplate = nTemplate.GetFingers();
		FMRecord fmRecord = NULL;
		if (!nfTemplate.IsNull())
		{
			fmRecord = FMRecord(nfTemplate, standard, recordVersion);
			NBuffer storedFmRecord = NULL;
			storedFmRecord = fmRecord.Save(encoding, flags);
			NFile::WriteAllBytes(argv[2], storedFmRecord);
		}
		else
			cout << "There are no NFRecords in NTemplate" << endl;
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
