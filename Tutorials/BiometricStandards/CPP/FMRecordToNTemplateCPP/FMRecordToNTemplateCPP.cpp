#include <TutorialUtils.hpp>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NBiometricClient/NBiometricClient.hpp>
	#include <NBiometrics/NBiometrics.hpp>
	#include <NMedia/NMedia.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NBiometricClient.hpp>
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

const NChar title[] = N_T("FMRecordToNTemplate");
const NChar description[] = N_T("Demonstrates creation of NTemplate from FMRecord");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [FMRecord] [NTemplate] [Standard] [FlagUseNeurotecFields]" << endl << endl;
	cout << "\tFMRecord - filename with FMRecord" << endl;
	cout << "\tNTemplate - filename for NTemplate" << endl;
	cout << "\tStandard - standard for FMRecord" << endl;
	cout << "\t\tANSI for ANSI/INCITS 378-2004" << endl;
	cout << "\tFlagUseNeurotecFields - 1 if FMRFV_USE_NEUROTEC_FIELDS flag is used; otherwise, 0 flag was not used." << endl;
	cout << "example:" << endl;
	cout << "\t" << title << " fmrecord.FMRecord template.NTemplate ANSI 1" << endl;
	return 1;
}

int main(int argc, NChar **argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 5)
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
		if (!strcmp(argv[3], N_T("ANSI")))
			standard = bsAnsi;
		else if (!strcmp(argv[3], N_T("ISO")))
			standard = bsIso;
		else
			NThrowException("Wrong standard");

		int flagUseNeurotecFields = !strcmp(argv[4], N_T("1")) ? 1 : 0;
		NBuffer storedFmRecord = NFile::ReadAllBytes(argv[1]);
		FMRecord fmRecord = NULL;
		if (flagUseNeurotecFields == 1)
			fmRecord = FMRecord(storedFmRecord, standard, FMRFV_USE_NEUROTEC_FIELDS);
		else
			fmRecord = FMRecord(storedFmRecord, standard);
		NTemplate nTemplate = fmRecord.ToNTemplate();
		NBuffer packedNTemplate = nTemplate.Save();
		cout << "Template extracted" << endl;
		NFile::WriteAllBytes(argv[2], packedNTemplate);
		cout << "NTemplate saved to file " << argv[2];
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
