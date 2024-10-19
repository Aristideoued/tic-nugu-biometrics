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
using namespace Neurotec::Licensing;

const NChar title[] = N_T("DongleInfo");
const NChar description[] = N_T("Demonstrates dongle information retrieval");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int main()
{
	OnStart(title, description, version, copyright, 0, NULL);

	try
	{
		NArrayWrapper <NLicManDongle> dongles = NLicenseManager::GetDongles();
		
		if (dongles.GetCount() == 0)
		{
			cout << "no dongles found";
			return -1;
		}

		for (NLicManDongle dongle : dongles)
		{
			cout << "=== Dongle Id: " << dongle.GetDistributorId() << " ===" << endl;
			for (int i = 0; i < dongle.GetLicenses().GetCount(); i++)
			{
				NLicenseProductInfo licenseInfo = dongle.GetLicenses().Get(i);
				cout << NLicenseManager::GetShortProductName(licenseInfo.GetId(), licenseInfo.GetLicenseType()) << " OS: " << licenseInfo.GetOSFamily()
					<< ", Count: " << licenseInfo.GetLicenseCount() << endl;
			}
		}
		cout << "No more dongles found";
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
