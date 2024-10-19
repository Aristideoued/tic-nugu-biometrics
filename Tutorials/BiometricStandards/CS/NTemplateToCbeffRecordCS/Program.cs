using System;
using System.IO;
using Neurotec.Biometrics.Standards;
using Neurotec.IO;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [NTemplate] [CbeffRecord] [PatronFormat]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[NTemplate] - filename of NTemplate.");
			Console.WriteLine("\t[CbeffRecord] - filename of CbeffRecord.");
			Console.WriteLine("\t[PatronFormat] - hex number identifying patron format (all supported values can be found in CbeffRecord class documentation).");
			Console.WriteLine("");

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 3)
			{
				return Usage();
			}

			//=========================================================================
			// CHOOSE LICENCES !!!
			//=========================================================================
			// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
			// If you are using a TRIAL version - choose any of them.

			const string licenses = "FingerClient,PalmClient,FaceClient,IrisClient";
			//const string licenses = "FingerFastExtractor,PalmClient,FaceFastExtractor,IrisFastExtractor";

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

				// Read NTemplate buffer
				var packedNTemplate = new NBuffer(File.ReadAllBytes(args[0]));

				// Combine NTemplate BDB format
				uint bdbFormat = BdifTypes.MakeFormat(CbeffBiometricOrganizations.Neurotechnologija, CbeffBdbFormatIdentifiers.NeurotechnologijaNTemplate);

				// Get CbeffRecord patron format
				// all supported patron formats can be found in CbeffRecord class documentation
				uint patronFormat = uint.Parse(args[2], System.Globalization.NumberStyles.HexNumber);

				// Create CbeffRecord from NTemplate buffer
				using (var cbeffRecord = new CbeffRecord(bdbFormat, packedNTemplate, patronFormat))
				{
					// Saving NTemplate
					File.WriteAllBytes(args[1], cbeffRecord.Save().ToArray());
					Console.WriteLine("Template successfully saved");
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
