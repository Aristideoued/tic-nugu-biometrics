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
using namespace Neurotec::IO;

const NChar title[] = N_T("ANTemplateMultiModal");
const NChar description[] = N_T("Demonstrates creation of multi modal ANTemplate with type 2 / 10 / 14/ 17 records in it");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [ANTemplate] [Encoding] [Finger NImage] [Face NImage] [Iris NImage]" << endl << endl;
	cout << "\tANTemplate - filename for ANTemplate" << endl;
	cout << "\tEncoding - specifies ANTemplate encoding type" << endl;
	cout << "\t\t0 - Traditional binary encoding" << endl;
	cout << "\t\t1 - NIEM-conformant XML encoding" << endl;
	cout << "\tFinger NImage	- filename with finger image file" << endl;
	cout << "\tFace NImage		- filename with face image file (optional)" << endl;
	cout << "\tIris NImage		- filename with iris image file (optional)" << endl;
	return 1;
}

void ANTemplateGetRecordType2(ANTemplate antemplate, BdifEncodingType encoding)
{
	NInt nameFieldNumber = 18;
	NInt placeOfBirthFieldNumber = 20;
	NInt dateOfBirthFieldNumber = 22;
	NInt genderFieldNumber = 24;

	try
	{
		ANType2Record record = antemplate.GetRecords().AddType2();

		// Adds fields for "traditional" binary encoding
		if (encoding == betTraditional)
		{
			record.GetFields().Add(nameFieldNumber, N_T("name, surname"));
			record.GetFields().Add(placeOfBirthFieldNumber, N_T("UK"));
			record.GetFields().Add(dateOfBirthFieldNumber, N_T("19700131"));
			record.GetFields().Add(genderFieldNumber, N_T("M"));
		}
		else // Adds fields for NIEM-conformant XML encoding
		{
			record.GetFields().Add(nameFieldNumber, N_T("PersonName"), N_T("name, surname"));
			record.GetFields().Add(placeOfBirthFieldNumber, N_T("PersonBirthPlaceCode"), N_T("UK"));
			record.GetFields().Add(dateOfBirthFieldNumber, N_T("PersonBirthDate"), N_T("19700131"));
			record.GetFields().Add(genderFieldNumber, N_T("PersonSexCode"), N_T("M"));
		}
	}
	catch (const NError &)
	{
		throw;
	}
}

void ANTemplateGetRecordType10(ANTemplate antemplate, NString fileNameIn, NString src)
{
	ANImageType imt = anitFace;
	try
	{
		/*
		Reads image data from file.
		Image must be compressed using valid compression algorithm for Type-10 record.
		How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
		*/
		NBuffer imageData = NFile::ReadAllBytes(fileNameIn);
		ANType10Record record = antemplate.GetRecords().AddType10(imt, src, imageData);
	}
	catch (const NError &)
	{
		throw;
	}
}

void ANTemplateGetRecordType14(ANTemplate antemplate, NString fileNameIn, NString src)
{
	try
	{
		/*
		Reads image data from file.
		Image must be compressed using valid compression algorithm for Type-14 record.
		How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
		*/
		NBuffer imageData = NFile::ReadAllBytes(fileNameIn);
		ANType14Record record = antemplate.GetRecords().AddType14(src, imageData);
	}
	catch (const NError &)
	{
		throw;
	}
}

void ANTemplateGetRecordType17(ANTemplate antemplate, NString fileNameIn, NString src)
{
	try
	{
		/*
		Reads image data from file.
		Image must be compressed using valid compression algorithm for Type-17 record.
		How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
		*/
		NBuffer imageData = NFile::ReadAllBytes(fileNameIn);
		ANType17Record record = antemplate.GetRecords().AddType17(src, imageData);
	}
	catch (const NError &)
	{
		throw;
	}
}

int main(int argc, NChar ** argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 4)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * licenses = { N_T("FingerClient,FaceClient,IrisClient") };
	//const NChar * licenses = { N_T("FingerFastExtractor,FaceFastExtractor,IrisFastExtractor") };

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

		NString fileNameOut = argv[1];
		BdifEncodingType encoding = ((NString)argv[2] == "1") ? betXml : betTraditional;
		NString fingerFileNameIn = argv[3];
		NString faceFileNameIn = argc > 4 ? argv[4] : N_T("");
		NString irisFileNameIn = argc > 5 ? argv[5] : N_T("");

		NString tot = "TransactionType";
		NString dai = "DestinationAgencyId";
		NString ori = "OriginatingAgencyId";
		NString tcn = "Transaction1";
		NString src = "SourceAgencyName";

		ANTemplate antemplate(AN_TEMPLATE_VERSION_CURRENT, tot, dai, ori, tcn, 0);

		ANTemplateGetRecordType2(antemplate, encoding);
		ANTemplateGetRecordType14(antemplate, fingerFileNameIn, src);
		if(!faceFileNameIn.IsEmpty()) ANTemplateGetRecordType10(antemplate, faceFileNameIn, src);
		if(!irisFileNameIn.IsEmpty()) ANTemplateGetRecordType17(antemplate, irisFileNameIn, src);

		antemplate.Save(fileNameOut, encoding);
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
