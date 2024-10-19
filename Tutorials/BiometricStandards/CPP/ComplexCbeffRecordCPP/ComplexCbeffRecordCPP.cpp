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

#include <vector>

using namespace std;
using namespace Neurotec;
using namespace Neurotec::IO;
using namespace Neurotec::Images;
using namespace Neurotec::Licensing;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Biometrics::Standards;

enum RecordType {
	rtANTemplate,
	rtFCRecord,
	rtFIRecord,
	rtFMRecord,
	rtIIRecord
};

struct RecordInfo {
	NChar * recordFile;
	RecordType recordType;
	BdifStandard standard;
	NUInt patronFormat;
};

const NChar title[] = N_T("ComplexCbeffRecord");
const NChar description[] = N_T("Creating a complex CbeffRecord");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

#define MAX_LICENSES 4

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [ComplexCbeffRecord] [PatronFormat] [[Record] [RecordType] [RecordStandard] [PatronFormat]] ..." << endl << endl;
	cout << "\t[ComplexCbeffRecord] - filename of CbeffRecord which will be created" << endl;
	cout << "\t[PatronFormat] - hex number identifying root record patron format (all supported values can be found in CbeffRecord class documentation)" << endl;
	cout << "\t[[Record] [RecordType] [RecordStandard] [PatronFormat]] - record information. Block can be specified more than once" << endl;
	cout << "\t\t[Record] - filename containing the record." << endl;
	cout << "\t\t[RecordType] - number indicating record type(0 - ANTemplate, 1 - FCRecord, 2 - FIRecord, 3 - FMRecord, 4 - IIRecord)" << endl;
	cout << "\t\t[RecordStandard] - number indicating record standard value(0 - Iso, 1 - Ansi or -1 - Unspecified if ANTemplate type is used)" << endl;
	cout << "\t\t[PatronFormat] - hex number identifying patron format" << endl;
	return 1;
}

static std::vector<RecordInfo> ParseArgs(NChar ** argv, int argc)
{
	std::vector<RecordInfo> infoList;
	for (int i = 3; i < argc; i += 4)
	{
		RecordInfo recInfo;
		recInfo.recordFile = argv[i];
		recInfo.recordType = (RecordType)atoi(argv[i + 1]);
		recInfo.standard = (BdifStandard)atoi(argv[i + 2]);
		recInfo.patronFormat = NTypes::UInt32Parse(argv[i + 3], N_T("X"));
		infoList.push_back(recInfo);
	}
	return infoList;
}

int main(int argc, NChar ** argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 6 || (argc - 3) % 4 != 0)
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

		std::vector<RecordInfo> recordInfo = ParseArgs(argv, argc);
		NUInt patronFormat = NTypes::UInt32Parse(argv[2], N_T("X"));
		CbeffRecord rootRecord(patronFormat);

		for (std::vector<RecordInfo>::iterator it = recordInfo.begin(); it != recordInfo.end(); it++)
		{
			CbeffRecord cbeffRecord = NULL;
			NBuffer buffer = NFile::ReadAllBytes(it->recordFile);

			switch (it->recordType)
			{
				case rtANTemplate:
					{
						ANTemplate anTemplate(buffer);
						if (!anTemplate.GetIsValidated())
						{
							NThrowException(N_T("ANSI/NIST template is not valid"));
						}
						cbeffRecord = CbeffRecord(anTemplate, it->patronFormat);
						break;
					}
				case rtFCRecord:
					{
						FCRecord fcRecord(buffer, it->standard);
						cbeffRecord = CbeffRecord(fcRecord, it->patronFormat);
						break;
					}
				case rtFIRecord:
					{
						FIRecord fiRecord(buffer, it->standard);
						cbeffRecord = CbeffRecord(fiRecord, it->patronFormat);
						break;
					}
				case rtFMRecord:
					{
						FMRecord fmRecord(buffer, it->standard);
						cbeffRecord = CbeffRecord(fmRecord, it->patronFormat);
						break;
					}
				case rtIIRecord:
					{
						IIRecord iiRecord(buffer, it->standard);
						cbeffRecord = CbeffRecord(iiRecord, it->patronFormat);
					}
				break;
			}
			rootRecord.GetRecords().Add(cbeffRecord);
		}

		NFile::WriteAllBytes(argv[1], rootRecord.Save());
		cout << "Record sucssfully saved" << endl;
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
