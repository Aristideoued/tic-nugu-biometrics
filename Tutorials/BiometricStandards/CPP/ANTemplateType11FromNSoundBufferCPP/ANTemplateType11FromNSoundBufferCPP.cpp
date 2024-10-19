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
using namespace Neurotec::Sound;

const NChar title[] = N_T("ANTemplateType10FromNImage");
const NChar description[] = N_T("Demonstrates creation of ANTemplate with current version and type 10 record in it");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [NSoundBuffer] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Src] [Encoding]" << endl << endl;
	cout << "\tNSoundBuffer - filename with sound buffer file" << endl;
	cout << "\tANTemplate - filename for ANTemplate" << endl;
	cout << "\tTot - specifies type of transaction" << endl;
	cout << "\tDai - specifies destination agency identifier" << endl;
	cout << "\tOri - specifies originating agency identifier" << endl;
	cout << "\tTcn - specifies transaction control number" << endl;
	cout << "\tSrc - specifies source agency name" << endl;
	cout << "\tEncoding - specifies ANTemplate encoding type" << endl;
	cout << "\t\t0 - Traditional binary encoding" << endl;
	cout << "\t\t1 - NIEM-conformant XML encoding" << endl;
	return 1;
}

int main(int argc, NChar ** argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 9)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NString license = N_T("VoiceClient");

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
		NString src = argv[7];
		NString enc = argv[8];
		// Sample acquisition source (11.008), which is mandatory when record has associated voice data. Must be updated with actual data.
		ANAcquisitionSource acqSource = { anastDigitalAudioRecordingDevice, "", "", "" };

		if ((tot.GetLength() < 3) || (tot.GetLength() > 4))
		{
			cout << "Tot parameter should be 3 or 4 characters length." << endl;
			return -1;
		}
		BdifEncodingType encoding = (enc == "1") ? betXml : betTraditional;

		ANTemplate antemplate(AN_TEMPLATE_VERSION_CURRENT, tot, dai, ori, tcn, 0);

		//Reads sound buffer data from file
		NSoundBuffer soundBuffer = NSoundBuffer::FromFile(argv[1], 0);

		// XML encoding is not supported currently
		if (encoding != betTraditional)
		{
			NThrowException(NString::Format(N_T("Currently only traditional encoding is supported for voice record")));
		}

		// Creates Type 11 record and adds record to ANTemplate object
		ANType11Record record = antemplate.GetRecords().AddType11(src, &acqSource, soundBuffer);

		antemplate.Save(argv[2], encoding);
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
