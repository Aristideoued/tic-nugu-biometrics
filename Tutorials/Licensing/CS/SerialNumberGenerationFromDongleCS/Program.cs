using System;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	internal class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [sequence number] [product id]", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			Console.WriteLine("product name : id:");
			uint[] ids = NLicenseManager.GetProductIds();
			foreach (uint id in ids)
			{
				Console.WriteLine("{0} : {1}", NLicenseManager.GetShortProductName(id, NLicenseType.SingleComputer), id);
			}
			Console.WriteLine();

			return 1;
		}

		private static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 2)
			{
				return Usage();
			}

			try
			{
				int sequenceNumber = int.Parse(args[0]);
				uint productId = uint.Parse(args[1]);
				int distributorId;
				string serialNumber = NLicenseManager.GenerateSerial(productId, sequenceNumber, out distributorId);

				Console.WriteLine("serial number: {0}", serialNumber);
				Console.WriteLine("distributor id: {0}", distributorId);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
