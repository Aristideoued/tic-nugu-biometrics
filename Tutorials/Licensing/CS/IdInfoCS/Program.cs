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
			Console.WriteLine("\t{0} [id file name]", TutorialUtils.GetAssemblyName());
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
				string id = File.ReadAllText(args[0]);
				int sequenceNumber, distributorId;
				uint productId;
				NLicenseManager.GetLicenseData(id, out sequenceNumber, out productId, out distributorId);

				Console.WriteLine("sequence number: {0}", sequenceNumber);
				Console.WriteLine("distributor id: {0}", distributorId);
				Console.WriteLine("product: {0}", NLicenseManager.GetShortProductName(productId, NLicenseType.SingleComputer));

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
