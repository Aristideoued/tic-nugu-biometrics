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

const NChar title[] = N_T("ANTemplateType2Record");
const NChar description[] = N_T("Demonstrates creation of ANTemplate with user-defined type 2 record in it");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]" << endl << endl;
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
	const NChar * components = N_T("Biometrics.Standards.Base");
		OnStart(title, description, version, copyright, argc, argv);

	if(argc < 7)
	{
		OnExit();
		return usage();
	}

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
		if (!NLicense::ObtainComponents(N_T("/local"), N_T("5000"), components))
		{
			NThrowException(NString::Format(N_T("Could not obtain licenses for components: {S}"), components));
		}

		NString tot = argv[2];
		NString dai = argv[3];
		NString ori = argv[4];
		NString tcn = argv[5];
		NString enc = argv[6];

		if (tot.GetLength() < 3 || tot.GetLength() > 4)
		{
			cout << "Tot parameter should be 3 or 4 characters length.";
			return -1;
		}
		BdifEncodingType encoding = (enc == "1") ? betXml : betTraditional;
		ANTemplate antemplate(AN_TEMPLATE_VERSION_CURRENT, tot, dai, ori, tcn);

		NInt nameFieldNumber = 18;// exemplary field number for subject's name and surname
		const NChar * nameFieldValue = N_T("name, surname"); // exemplary subject's name and surname
		NInt placeOfBirthFieldNumber = 20;// exemplary field number for subject's place of birth
		const NChar * placeOfBirthFieldValue = N_T("UK"); // exemplary subject's place of birth
		NInt dateOfBirthFieldNumber = 22;// exemplary field number for subject's date of birth
		const NChar * dateOfBirthFieldValue = N_T("19700131"); // exemplary subject's date of birth
		NInt genderFieldNumber = 24;// exemplary field number for subject's gender
		const NChar * genderFieldValue = N_T("M");// exemplary subject's gender

		ANType2Record record = antemplate.GetRecords().AddType2();

		// Add fields for "traditional" binary encoding
		if (encoding == betTraditional)
		{
			record.GetFields().Add(nameFieldNumber, nameFieldValue);
			record.GetFields().Add(placeOfBirthFieldNumber, placeOfBirthFieldValue);
			record.GetFields().Add(dateOfBirthFieldNumber, dateOfBirthFieldValue);
			record.GetFields().Add(genderFieldNumber, genderFieldValue);
		}
		else // Add fields for NIEM-conformant XML encoding
		{
			record.GetFields().Add(nameFieldNumber, N_T("PersonName"), nameFieldValue);
			record.GetFields().Add(placeOfBirthFieldNumber, N_T("PersonBirthPlaceCode"), placeOfBirthFieldValue);
			record.GetFields().Add(dateOfBirthFieldNumber, N_T("PersonBirthDate"), dateOfBirthFieldValue);
			record.GetFields().Add(genderFieldNumber, N_T("PersonSexCode"), genderFieldValue);
		}

		antemplate.Save(argv[1], encoding);
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
