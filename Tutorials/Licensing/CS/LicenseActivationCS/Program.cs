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

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 2)
			{
				return Usage();
			}

			try
			{
				/* Load id file (it can be generated using IdGeneration tutorial or ActivationWizardDotNet */
				string id = File.ReadAllText(args[0]);

				/* Generate license for specified id */
				string license = NLicense.ActivateOnline(id);

				/* Write license to file */
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
