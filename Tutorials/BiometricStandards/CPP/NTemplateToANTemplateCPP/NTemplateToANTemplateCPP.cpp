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

const NChar title[] = N_T("NTemplateToANTemplate");
const NChar description[] = N_T("Demonstrates creation of ANTemplate from NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

#define MAX_LICENSES 2

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [NTemplate] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]" << endl << endl;
	cout << "\tNTemplate     - filename with tNTemplate" << endl;
	cout << "\tANTemplate - filename for ANTemplate" << endl;
	cout << "\tTot - specifies type of transaction" << endl;
	cout << "\tDai - specifies destination agency identifier" << endl;
	cout << "\tOri - specifies originating agency identifier" << endl;
	cout << "\tTcn - specifies transaction control number" << endl;
	cout << "\tEncoding - specifies ANTemplate encoding type" << endl;
	cout << "\t\t0 - Traditional binary encoding" << endl;
	cout << "\t\t1 - NIEM-conformant XML encoding" << endl;
	return 1;
}

int main(int argc, NChar ** argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 8)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	static const NChar * licenses[MAX_LICENSES] = { N_T("FingerClient"),N_T("PalmClient") };
	//static const NChar * licenses[MAX_LICENSES] = { N_T("FingerFastExtrctor"),N_T("PalmClient") };

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

	bool anyMatchingComponent = false;
	try
	{
		// Obtain licenses
		for (int i = 0; i < MAX_LICENSES; i++) 
		{
			if (NLicense::Obtain(N_T("/local"), N_T("5000"), licenses[i]))
			{
				cout << "Obtained license: " << licenses[i] << endl;
				anyMatchingComponent = true;
			}
		}
		if (!anyMatchingComponent)
		{
			NThrowNotActivatedException("Could not obtain any matching license");
		}

		NString tot = argv[3];
		NString dai = argv[4];
		NString ori = argv[5];
		NString tcn = argv[6];
		NString enc = argv[7];

		if (tot.GetLength() < 3 || tot.GetLength() > 4)
		{
			cout << "Tot parameter should be 3 or 4 characters length.";
			return -1;
		}

		BdifEncodingType encoding = (enc == "1") ? betXml : betTraditional;

		NBuffer buffer = NFile::ReadAllBytes(argv[1]);
		NTemplate nTemplate(buffer);

		//sets minutia format: true - if standard, false - otherwise. For palms only standard minutia format is supported
		NBool type9RecordFmtStd = nTemplate.GetPalms() != NULL && nTemplate.GetPalms().GetRecords().GetCount() > 0 ? true : false;
		// Create ANTemplate object from NTemplate object
		ANTemplate anTemplate(AN_TEMPLATE_VERSION_CURRENT, tot, dai, ori, tcn, type9RecordFmtStd, nTemplate);
		anTemplate.Save(argv[2], encoding);
		cout << "Program produced file: " << argv[2];
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
