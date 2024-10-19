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
			Console.WriteLine("\t{0} [serial file name] [id file name]", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 2)
			{
				return Usage();
			}

			try
			{
				/* Load serial file (generated using LicenseManager API or provided either by Neurotechnology or its distributor) */
				string serial = File.ReadAllText(args[0]);

				/* Either point to correct place for id_gen.exe, or pass NULL or use method without idGenPath parameter in order to search id_gen.exe in current folder */
				string id = NLicense.GenerateId(serial);

				/* Write generated id to file */
				File.WriteAllText(args[1], id);

				Console.WriteLine("id saved to file {0}, it can now be activated using LicenseActivation tutorial, web page, etc.", args[1]);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
