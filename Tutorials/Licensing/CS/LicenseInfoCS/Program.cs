using System;
using System.IO;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
    class Program
    {
        static int Usage()
        {
            Console.WriteLine("usage:");
            Console.WriteLine("\t{0} [license file name]", TutorialUtils.GetAssemblyName());
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
                NLicenseInfo licenseInfo = NLicense.GetLicenseInfoOnline(File.ReadAllText(args[0]));
                Console.WriteLine("Specified license information:");
                Console.WriteLine("\tType: {0}", licenseInfo.Type);
                Console.WriteLine("\tSource type: {0}", licenseInfo.SourceType);
                Console.WriteLine("\tDistributor id: {0}", licenseInfo.DistributorId);
                Console.WriteLine("\tSequence number: {0}", licenseInfo.SequenceNumber);
                Console.WriteLine("\tLicense id: {0}", licenseInfo.LicenseId);
                Console.WriteLine("\tProducts:");
                NLicenseProductInfo[] licenses = licenseInfo.GetLicenses();
                var parameters = licenses[0].Parameters;
                foreach (NLicenseProductInfo license in licenses)
                {
                    Console.WriteLine("\t\t{0} OS: {1}, Count: {2}", NLicenseManager.GetShortProductName(license.Id, license.LicenseType), license.OSFamily, license.LicenseCount);
                    Console.WriteLine("{0}", license.Parameters);
                }

                Console.ReadLine();
                return 0;
            }
            catch (Exception ex)
            {
                return TutorialUtils.PrintException(ex);
            }
        }
    }
}
