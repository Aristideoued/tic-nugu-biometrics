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

#include <vector>

using namespace std;
using namespace Neurotec;
using namespace Neurotec::IO;
using namespace Neurotec::Images;
using namespace Neurotec::Licensing;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Biometrics::Client;
using namespace Neurotec::Biometrics::Standards;

const NChar title[] = N_T("CbeffRecordToNTemplate");
const NChar description[] = N_T("Converting CbeffRecord to NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

#define MAX_LICENSES 4

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [CbeffRecord] [PatronFormat] [NTemplate]" << endl << endl;
	cout << "\t[NTemplate] - filename of NTemplate" << endl;
	cout << "\t[CbeffRecord] - filename for CbeffRecord" << endl;
	cout << "\t[PatronFormat] - hex number identifying patron format (all supported values can be found in CbeffRecord class documentation)" << endl;
	return 1;
}

int main(int argc, NChar ** argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if(argc != 4)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	static const NChar * licenses[MAX_LICENSES] = { N_T("FingerClient"),N_T("PalmClient"),N_T("FaceClient"),N_T("IrisClient") };
	//static const NChar * licenses[MAX_LICENSES] = { N_T("FingerFastExtrctor"),N_T("PalmClient"),N_T("FaceFastExtractor"),N_T("IrisFastExtractor") };

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

		NBuffer packedCbeffRecord = NFile::ReadAllBytes(argv[1]);
		NUInt patronFormat = NTypes::UInt32Parse(argv[2], N_T("X"));
		CbeffRecord cbeffRecord(packedCbeffRecord, patronFormat);
		NSubject subject;
		NBiometricClient client;
		subject.SetTemplate(cbeffRecord);
		NBiometricStatus status = client.CreateTemplate(subject);
		if (status == nbsOk)
		{
			NFile::WriteAllBytes(argv[3], subject.GetTemplate().Save());
			cout << "Template successfully saved";
		}
		else
			cout << "Template creation failed! Satus: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status);

	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
