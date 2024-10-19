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

const NChar title[] = N_T("DongleUpdate");
const NChar description[] = N_T("Demonstrates dongle online update using ticket");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

static int usage()
{
	cout <<"usage:" << endl;
	cout << "\t" << title << " [serial file name] [id file name]" << endl;
	return 1;
}

int main(int argc, NChar *argv[])
{
	OnStart(title, description, version, copyright, 0, NULL);

	if (argc != 2)
	{
		return usage();
	}

	try
	{
		NLicManDongleUpdateTicketInfo ticket = NLicenseManager::GetUpdateTicketInfo(argv[1]);
		cout << "Ticket: " << ticket.GetNumber() << ", status: " << ticket.GetStatus() << ", issue date: " << ticket.GetIssueDate().ToString() << endl;
		if (ticket.GetDongleDistributorId() != 0 && ticket.GetDongleHardwareId() != 0)
		{
			cout << "Ticket assigned to dongle: " << ticket.GetDongleDistributorId() << " hardware id: " << ticket.GetDongleHardwareId() << endl;
		}
		for (int i = 0; i < ticket.GetLicenses().GetCount(); i++)
		{
			NLicenseProductInfo license = ticket.GetLicenses().Get(i);
			cout << NLicenseManager::GetShortProductName(license.GetId(), license.GetLicenseType()) << " OS: " << license.GetOSFamily()
				 << ", Count: " << license.GetLicenseCount() << endl;
		}
		if (ticket.GetStatus() != nlmdutsEnabled)
		{
			cout << "Specified ticket can not be used as ticket status is: " << ticket.GetStatus() << endl;
			return -1;
		}

		NLicManDongle foundDongle = NULL;

		NArrayWrapper <NLicManDongle> dongles = NLicenseManager::GetDongles();

		for (NLicManDongle dongle : dongles)
		{
			if (ticket.GetDongleDistributorId() != 0 && ticket.GetDongleHardwareId() != 0)
			{
				if (dongle.GetDistributorId() == ticket.GetDongleDistributorId() && dongle.GetHardwareId() == ticket.GetDongleHardwareId())
				{
					foundDongle = dongle;
					break;
				}
				else
					foundDongle = dongle;
			}
		}

		if (foundDongle.IsNull())
		{
			cout << "No dongles found (that could be used)";
			return -1;
		}
		

		foundDongle.UpdateOnline(ticket);
		cout << "Dongle updated successfully";
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
