#include <TutorialUtils.hpp>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NLicensing.hpp>
#endif

using namespace std;
using namespace Neurotec;
using namespace Neurotec::IO;
using namespace Neurotec::Licensing;

const NChar title[] = N_T("LicenseActivationFromDongle");
const NChar description[] = N_T("Demonstrates license activation from dongle");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C)2016 Neurotechnology");

static int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [id file name] [lic file name]" << endl;
	return 1;
}

int main(int argc, NChar *argv[])
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc != 3)
	{
		return usage();
	}

	try
	{
		NString id = NFile::ReadAllText(argv[1]);
		cout << "WARNING: generating a license will decrease license count" << endl << "for a specific product in a dongle by 1. Continue? (y/n)" <<endl;
		string answer;
		cin >> answer;
		if (answer != "y")
		{
			cout << "not generating" << endl;
			return 0;
		}

		NInt sequenceNumber;
		NUInt productId;
		NString license = NLicenseManager::GenerateLicense(id, &sequenceNumber, &productId);
		NFile::WriteAllText(argv[2], license);
		cout << "License saved to file: " << argv[2];
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
