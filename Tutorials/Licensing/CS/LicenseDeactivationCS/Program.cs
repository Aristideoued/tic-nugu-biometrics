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
			Console.WriteLine("\t{0} [lic file name] (optional: [deactivation id file name])", TutorialUtils.GetAssemblyName());
			Console.WriteLine("NOTE: Please always deactivate license on the same computer it was activated on!");
			Console.WriteLine();

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 1)
			{
				return Usage();
			}

			try
			{
				/* Load license file */
				string license = File.ReadAllText(args[0]);

				/* First check our intentions */
				Console.WriteLine("WARNING: deactivating a license will make\nit and product(for which it was generated) disabled on current pc. Continue? (y/n)");
				if (Console.Read() != 'y')
				{
					Console.WriteLine("not generating");
					return 0;
				}

				try
				{
					/* Either point to correct place for id_gen.exe, or pass NULL or use method without idGenPath parameter in order to search id_gen.exe in current folder */
					/* Do the deactivation */
					NLicense.DeactivateOnline(license);

					Console.WriteLine("online deactivation succeeded. you can now use serial number again");
				}
				catch (Exception ex)
				{
					Console.WriteLine("online deactivation failed. reason: {0}", ex.Message);
					Console.WriteLine("generating deactivation id, which you can send to support@neurotechnology.com for manual deactivation");

					if (args.Length != 2)
					{
						Console.WriteLine("missing deactivation id argument, please specify it");
						return Usage();
					}

					string id = NLicense.GenerateDeactivationIdForLicense(license);
					/* Write generated deactivation id to file */
					File.WriteAllText(args[1], id);

					Console.WriteLine("deactivation id saved to file {0}. please send it to support@neurotechnology.com to complete deactivation process", args[1]);
				}

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
