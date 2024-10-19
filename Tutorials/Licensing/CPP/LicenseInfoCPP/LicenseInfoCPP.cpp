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

const NChar title[] = N_T("LicenseInfo");
const NChar description[] = N_T("Demonstrates how to get information about specified license/hardware id/serial number");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

static int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [license file name]" << endl;
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
		NLicenseInfo licenseInfo = NLicense::GetLicenseInfoOnline(NFile::ReadAllText(argv[1]));
		cout << "Specified license information:" << endl;
		cout << "\tType: " << licenseInfo.GetType() << endl;
		cout << "\tSource type: " << licenseInfo.GetSourceType() << endl;
		cout << "\tDistributor id: " << licenseInfo.GetDistributorId() << endl;
		cout << "\tSequence number: " << licenseInfo.GetSequenceNumber() << endl;
		cout << "\tLicense id: " << licenseInfo.GetLicenseId() << endl;
		cout << "\tProducts: " << endl;
		for (int i = 0; i < licenseInfo.GetLicenses().GetCount(); i++)
		{
			NLicenseProductInfo license = licenseInfo.GetLicenses().Get(i);
			cout << "\t\t" << NLicenseManager::GetShortProductName(license.GetId(), license.GetLicenseType()) << " OS: " << license.GetOSFamily() << ", Count: " << license.GetLicenseCount() << endl;
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
