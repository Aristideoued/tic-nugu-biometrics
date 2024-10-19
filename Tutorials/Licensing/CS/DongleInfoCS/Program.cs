using System;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			try
			{
				
				NLicManDongle[] dongles = NLicenseManager.GetDongles();

				if (dongles.Length == 0)
				{
					Console.WriteLine("no dongles found");
					return -1;
				}

				foreach (NLicManDongle dongle in dongles)
				{
					Console.WriteLine("=== Dongle Id: {0} ===\n", dongle.DistributorId);
					NLicenseProductInfo[] licenses = dongle.GetLicenses();
					foreach (NLicenseProductInfo license in licenses)
					{
						Console.WriteLine("{0} OS: {1}, Count: {2}", NLicenseManager.GetShortProductName(license.Id, license.LicenseType), license.OSFamily, license.LicenseCount);
					}
				}

				Console.WriteLine("no more dongles found");

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
