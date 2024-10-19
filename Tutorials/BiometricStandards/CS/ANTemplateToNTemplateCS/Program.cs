using System;
using System.IO;
using Neurotec.Biometrics;
using Neurotec.Biometrics.Standards;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [ANTemplate] [NTemplate]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[ATemplate] - filename of ANTemplate.");
			Console.WriteLine("\t[NTemplate] - filename of NTemplate.");
			Console.WriteLine("");
			Console.WriteLine("examples:");
			Console.WriteLine("\t{0} antemplate.data nTemplate.data", TutorialUtils.GetAssemblyName());

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 2)
			{
				return Usage();
			}

			//=========================================================================
			// CHOOSE LICENCES !!!
			//=========================================================================
			// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
			// If you are using a TRIAL version - choose any of them.

			const string license = "FingerClient";
			//const string license = "FingerFastExtractor";

			//=========================================================================

			//=========================================================================
			// TRIAL MODE
			//=========================================================================
			// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
			// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
			// Also you can just set TRUE to "TrialMode" property in code.

			NLicenseManager.TrialMode = TutorialUtils.GetTrialModeFlag();
			Console.WriteLine("Trial mode: " + NLicenseManager.TrialMode);

			//=========================================================================

			try
			{
				// Obtain license
				if (!NLicense.Obtain("/local", 5000, license))
				{
					throw new NotActivatedException(string.Format("Could not obtain license: {0}", license));
				}

				string aNTemplateFileName = args[0];

				// Creating ANTemplate object from file
				using (var anTemplate = new ANTemplate(aNTemplateFileName))
				{
					if (!anTemplate.IsValidated)
					{
						throw new Exception("ANSI/NIST template is not valid");
					}
					// Converting ANTemplate object to NTemplate object
					using (NTemplate nTemplate = anTemplate.ToNTemplate())
					{
						// Packing NTemplate object
						byte[] packedNTemplate = nTemplate.Save().ToArray();

						// Storing NTemplate object in file
						File.WriteAllBytes(args[1], packedNTemplate);
					}
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
