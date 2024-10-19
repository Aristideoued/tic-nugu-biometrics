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
using namespace Neurotec::Images;
using namespace Neurotec::Licensing;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Biometrics::Standards;

const NChar title[] = N_T("ANTemplateToNImage");
const NChar description[] = N_T("Demonstrates how to save images stored in ANTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [ANTemplate]" << endl << endl;
	cout << "\tANTemplate - filename of ANTemplate" << endl;
	return 1;
}

int main(int argc, NChar ** argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 2)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * licenses = { N_T("FingerClient,PalmClient,FaceClient,IrisClient") };
	//const NChar * licenses = { N_T("FingerFastExtractor,PalmClient,FaceFastExtractor,IrisFastExtractor") };

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
		// Obtain licenses
		if (!NLicense::Obtain(N_T("/local"), N_T("5000"), licenses))
		{
			NThrowException(NString::Format(N_T("Could not obtain licenses: {S}"), licenses)); 
		}

		ANTemplate anTemplate(argv[1]);
		if (!anTemplate.GetIsValidated())
		{
			NThrowException(N_T("ANSI/NIST template is not valid"));
		}
		for (int i = 0; i < anTemplate.GetRecords().GetCount(); i++)
		{
			ANRecord record = anTemplate.GetRecords().Get(i);
			NImage image = NULL;
			int number = record.GetRecordType().GetNumber();
			if (number >= 3 && number <=8 && number !=7)
				image = NObjectDynamicCast<ANImageBinaryRecord>(record).ToNImage();
			else if (number >= 10 && number <= 17)
				image = NObjectDynamicCast<ANImageAsciiBinaryRecord>(record).ToNImage();
			if (!image.IsNull())
			{
				NString fileName = NString::Format("record{I}_type{I}.jpg", i + 1, number);
				image.Save(fileName);
				cout << "Image saved to " << fileName << endl;
			}
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
