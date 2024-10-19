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

const NChar title[] = N_T("LicenseDeactivation");
const NChar description[] = N_T("Demonstrates license deactivation");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

static int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [lic file name] (optional: [deactivation id file name])" << endl;
	cout << "NOTE: Please always deactivate license on the same computer it was activated on!" << endl;
	return 1;
}

int main(int argc, NChar *argv[])
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc != 2)
	{
		return usage();
	}

	try
	{
		NString license = NFile::ReadAllText(argv[1]);
		cout << "WARNING: deactivating a license will make\nit and product(for which it was generated) disabled on current pc. Continue? (y/n)";
		string answer;
		cin >> answer;
		if (answer != "y")
		{
			cout << "not deactivating";
			return 0;
		}

		try
		{
			NLicense::DeactivateOnline(license);
			cout << "online deactivation succeeded. you can now use serial number again";
		}
		catch (NError& e)
		{
			cout << "Online deactivation failed. Reason: " << e << endl;
			cout << "Generating deactivation id, which can be sent to support@neurotechnology.com for manual deactivation." << endl;
			
			if (argc != 3)
			{
				cout << "Missing deactivation id argument, please specifi it.";
				return usage();
			}
			NString id = NLicense::GenerateDeactivationIdForLicense(license);
			NFile::WriteAllText(argv[2], id);
			cout << "Deactivation id saved to file " << argv[2] << " Please send it to support@neurotechnology.com to complete deactivation process.";
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
