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

const NChar title[] = N_T("ANTemplateType6FromNImage");
const NChar description[] = N_T("Demonstrates creation of ANTemplate with type 6 record in it");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [NImage] [ANTemplate] [Tot] [Dai] [Ori] [Tcn]" << endl << endl;
	cout << "\tNImage     - filename with image file" << endl;
	cout << "\tANTemplate - filename for ANTemplate" << endl;
	cout << "\tTot - specifies type of transaction" << endl;
	cout << "\tDai - specifies destination agency identifier" << endl;
	cout << "\tOri - specifies originating agency identifier" << endl;
	cout << "\tTcn - specifies transaction control number" << endl;
	return 1;
}

int main(int argc, NChar **argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 7)
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

		NString tot = argv[3];
		NString dai = argv[4];
		NString ori = argv[5];
		NString tcn = argv[6];

		if (tot.GetLength() < 3 || tot.GetLength() > 4)
		{
			cout << "Tot parameter should be 3 or 4 characters length.";
			return -1;
		}

		NVersion templateVersion = AN_TEMPLATE_VERSION_4_0;
		ANTemplate antemplate(templateVersion, tot, dai, ori, tcn, 0);
		NImage image = NImage::FromFile(argv[1]);
		image.SetHorzResolution(500);
		image.SetVertResolution(500);
		image.SetResolutionIsAspectRatio(false);
		ANType6Record record = antemplate.GetRecords().AddType6(true, anbicaNone, image);

		ANType1Record type1 = NObjectDynamicCast<ANType1Record>(antemplate.GetRecords().Get(0));
		type1.SetNativeScanningResolution(AN_TYPE_1_RECORD_MIN_SCANNING_RESOLUTION);
		type1.SetNominalTransmittingResolutionPpi(image.GetHorzResolution());

		antemplate.Save(argv[2]);
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
