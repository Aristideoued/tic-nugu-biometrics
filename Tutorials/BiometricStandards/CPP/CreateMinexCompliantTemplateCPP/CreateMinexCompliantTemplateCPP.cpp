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
using namespace Neurotec::Biometrics::Client;
using namespace Neurotec::Biometrics::Standards;

const NChar title[] = N_T("CreateMinexCompliantTemplate");
const NChar description[] = N_T("Demonstrates creation of Minex compliant fingerprint record (FMRecord) from image.");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2017-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [image] [template]" << endl << endl;
	cout << "\t[image]    - image filename to extract." << endl;
	cout << "\t[template] - FMRecord to store extracted features." << endl;
	cout << "\n\nexamples:" << endl;
	cout << "\t" << title << " image.jpg fmrecord.FMRecord" << endl;
	return 1;
}

int main(int argc, NChar *argv[])
{
	NBiometricStatus biometricStatus = nbsNone;

	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 3)
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

		NSubject subject;
		NFinger finger;

		finger.SetSampleBuffer(NFile::ReadAllBytes(argv[1]));
		subject.GetFingers().Add(finger);
		NBiometricClient biometricClient;
		biometricClient.SetFingersExtractionScenario(nesMinex);

		NBiometricTask task = biometricClient.CreateTask((NBiometricOperations)(nboCreateTemplate | nboAssessQuality), subject);
		biometricClient.PerformTask(task);
		biometricStatus = task.GetStatus();

		if (biometricStatus == nbsOk)
		{
			cout << "ANSI template extracted" << endl;

			// save FMRecord
			NBuffer storedFmRecord = subject.GetTemplateBuffer(CBEFF_BO_INCITS_TC_M1_BIOMETRICS, CBEFF_BDBFI_INCITS_TC_M1_BIOMETRICS_FINGER_MINUTIAE_U, FMR_VERSION_ANSI_2_0);
			NFile::WriteAllBytes(argv[2], storedFmRecord);
			printf(N_T("Template saved successfully\n"));
		}
		else
		{
			cout << "Extraction failed!" << endl;
			cout << "Biometric status = " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), biometricStatus) << endl;
			if (!task.GetError().IsNull())
				return LastError(task.GetError());
			return -1;
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
