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

const NChar title[] = N_T("ANTemplateToNTemplate");
const NChar description[] = N_T("Demonstrates ANTemplate conversion to NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << "[ANTemplate] [NTemplate]" << endl << endl;
	cout << "\tANTemplate - filename with ANTemplate" << endl;
	cout << "\tNTemplate  - filename for NTemplate" << endl;
	cout << "example:" << endl;
	cout << "\t" << title << "anTemplate.ANTemplate template.NTemplate" << endl;
	return 1;
}

int main(int argc, NChar **argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 3)
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
		
		ANTemplate anTemplate(argv[1]);
		if (!anTemplate.GetIsValidated())
		{
			NThrowException(N_T("ANSI/NIST template is not valid"));
		}
		NTemplate nTemplate(anTemplate.ToNTemplate());
		NFile::WriteAllBytes(argv[2], nTemplate.Save());
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
