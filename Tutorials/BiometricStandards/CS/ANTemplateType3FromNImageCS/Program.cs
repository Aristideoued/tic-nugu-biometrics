using System;
using Neurotec.Biometrics.Standards;
using Neurotec.Images;
using Neurotec.Licensing;
using Neurotec.IO;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [NImage] [ANTemplate] [Tot] [Dai] [Ori] [Tcn]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[NImage]     - filename with image file.");
			Console.WriteLine("\t[ANTemplate] - filename for ANTemplate.");
			Console.WriteLine("\t[Tot] - specifies type of transaction.");
			Console.WriteLine("\t[Dai] - specifies destination agency identifier.");
			Console.WriteLine("\t[Ori] - specifies originating agency identifier.");
			Console.WriteLine("\t[Tcn] - specifies transaction control number.");
			Console.WriteLine("");

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 6)
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

				string tot = args[2]; // type of transaction
				string dai = args[3]; // destination agency identifier
				string ori = args[4]; // originating agency identifier
				string tcn = args[5]; // transaction control number

				if ((tot.Length < 3) || (tot.Length > 4))
				{
					Console.WriteLine("Tot parameter should be 3 or 4 characters length.");
					return -1;
				}

				var version = ANTemplate.Version40;
				float resolution = 250;

				// Create empty ANTemplate object with only type 1 record in it
				using (var template = new ANTemplate(version, tot, dai, ori, tcn, 0))
				using (var imageBuffer = NFile.ReadAllBytes(args[0]))
				{
					// Create Type 3 record and add to ANTemplate object
					var record = template.Records.AddType3(true, imageBuffer);

					ANType1Record type1 = (ANType1Record)template.Records[0];
					type1.NativeScanningResolution = ANType1Record.MinScanningResolution;
					type1.NominalTransmittingResolutionPpi = resolution;

					// Store ANTemplate object with type 3 record in file
					template.Save(args[1]);
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
