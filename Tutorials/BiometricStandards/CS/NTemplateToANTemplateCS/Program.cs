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
			Console.WriteLine("\t{0} [NTemplate] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[NTemplate]     - filename of NTemplate.");
			Console.WriteLine("\t[ANTemplate]    - filename of ANTemplate.");
			Console.WriteLine("\t[Tot] - specifies type of transaction.");
			Console.WriteLine("\t[Dai] - specifies destination agency identifier.");
			Console.WriteLine("\t[Ori] - specifies originating agency identifier.");
			Console.WriteLine("\t[Tcn] - specifies transaction control number.");
            Console.WriteLine("\t[Encoding] - specifies ANTemplate encoding type.");
            Console.WriteLine("\t\t0 - Traditional binary encoding.");
            Console.WriteLine("\t\t1 - NIEM-conformant XML encoding.");
            Console.WriteLine("");

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 7)
			{
				return Usage();
			}

			if (args[0] == "/?" || args[0] == "help")
			{
				return Usage();
			}

			//=========================================================================
			// CHOOSE LICENCES !!!
			//=========================================================================
			// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
			// If you are using a TRIAL version - choose any of them.

			const string licenses = "FingerClient,PalmClient";
			//const string licenses = "FingerFastExtractor,PalmClient";

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

			var anyMatchingComponent = false;
			try
			{
				// Obtain licenses
				foreach (string license in licenses.Split(','))
				{
					if (NLicense.Obtain("/local", 5000, license))
					{
						Console.WriteLine("Obtained license: {0}", license);
						anyMatchingComponent = true;
					}
				}
				if (!anyMatchingComponent)
				{
					throw new NotActivatedException("Could not obtain any matching license");
				}

				string nTemplateFileName = args[0];

				string tot = args[2]; // type of transaction
				string dai = args[3]; // destination agency identifier
				string ori = args[4]; // originating agency identifier
				string tcn = args[5]; // transaction control number
				string enc = args[6]; // encoding type

				if ((tot.Length < 3) || (tot.Length > 4))
				{
					Console.WriteLine("Tot parameter should be 3 or 4 characters length.");
					return -1;
				}

				BdifEncodingType encoding = (enc == "1") ? BdifEncodingType.Xml : BdifEncodingType.Traditional;

				byte[] packedNTemplate = File.ReadAllBytes(nTemplateFileName);

				// Creating NTemplate object from packed NTemplate
				using (var nTemplate = new NTemplate(packedNTemplate))
				{
					//sets minutia format: true - if standard, false - otherwise. For palms only standard minutia format is supported
					bool type9RecordFmtStd = nTemplate.Palms != null && nTemplate.Palms.Records.Count > 0 ? true : false;
					// Creating ANTemplate object from NTemplate object
					using (var anTemplate = new ANTemplate(ANTemplate.VersionCurrent, tot, dai, ori, tcn, type9RecordFmtStd, nTemplate))
					{
						// Storing ANTemplate object in file
						anTemplate.Save(args[1], encoding);
						Console.WriteLine("Program produced file: " + args[1]);
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
