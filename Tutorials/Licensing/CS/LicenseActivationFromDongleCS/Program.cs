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
			Console.WriteLine("\t{0} [id file name] [lic file name]", TutorialUtils.GetAssemblyName());
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
				string id = File.ReadAllText(args[0]);
				Console.Write("WARNING: generating a license will decrease license count\nfor a specific product in a dongle by 1. Continue? (y/n)" );
				if ((char) Console.Read() != 'y')
				{
					Console.WriteLine("not generating");
					return 0;
				}

				int sequenceNumber;
				uint productId;
				string license = NLicenseManager.GenerateLicense(id, out sequenceNumber, out productId);
				File.WriteAllText(args[1], license);
				Console.WriteLine("license saved to file {0}", args[1]);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
