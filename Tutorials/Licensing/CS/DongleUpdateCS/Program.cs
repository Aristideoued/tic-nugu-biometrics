using System;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [ticket number]", TutorialUtils.GetAssemblyName());
			Console.WriteLine();

			return 1;
		}

		private static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 1)
			{
				return Usage();
			}

			try
			{
				NLicManDongleUpdateTicketInfo ticket = NLicenseManager.GetUpdateTicketInfo(args[0]);
				Console.WriteLine("ticket: {0}, status: {1}, issue date: {2:yyyy-MM-dd HH:mm:ss}", ticket.Number, ticket.Status, ticket.IssueDate);
				if (ticket.DongleDistributorId != 0 && ticket.DongleHardwareId != 0)
					Console.WriteLine("ticket assigned to dongle: {0} (hardware id: {1:X})", ticket.DongleDistributorId,
						ticket.DongleHardwareId);

				foreach (NLicenseProductInfo license in ticket.GetLicenses())
				{
					Console.WriteLine("{0} OS: {1}, Count: {2}", NLicenseManager.GetShortProductName(license.Id, license.LicenseType), license.OSFamily, license.LicenseCount);
				}
				if (ticket.Status != NLicManDongleUpdateTicketStatus.Enabled)
				{
					Console.WriteLine("Specified ticket can not be used as ticket status is: {0}", ticket.Status);
					return -1;
				}

				NLicManDongle foundDongle = null;

				NLicManDongle[] dongles = NLicenseManager.GetDongles();

				foreach (NLicManDongle dongle in dongles)
				{
					if (ticket.DongleDistributorId != 0 && ticket.DongleHardwareId != 0)
					{
						if (dongle.DistributorId == ticket.DongleDistributorId && dongle.HardwareId == ticket.DongleHardwareId)
						{
							foundDongle = dongle;
							break;
						}
					}
					else
						foundDongle = dongle;
				}

				if (foundDongle == null)
				{
					Console.WriteLine("No dongles found (that could be used)");
					return -1;
				}

				// Apply the dongle update
				foundDongle.UpdateOnline(ticket);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
