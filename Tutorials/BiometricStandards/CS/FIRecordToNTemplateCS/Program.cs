using System;
using System.IO;

using Neurotec.Biometrics;
using Neurotec.Biometrics.Client;
using Neurotec.Biometrics.Standards;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage: {0} [FIRecord] [NTemplate]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\t[FIRecord]  - input FIRecord");
			Console.WriteLine("\t[NTemplate] - output NTemplate");

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 2)
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

				using (var biometricClient = new NBiometricClient())
				using (var subject = new NSubject())
				{
					// Read FIRecord from file
					byte[] fiRecordData = File.ReadAllBytes(args[0]);

					// Create FIRecord
					var fiRec = new FIRecord(fiRecordData, BdifStandard.Iso);

					// Read all images from FIRecord
					foreach (FirFingerView fv in fiRec.FingerViews)
					{
						var finger = new NFinger { Image = fv.ToNImage() };
						subject.Fingers.Add(finger);
					}

					// Set finger template size (large is recommended for enrolment to database) (optional)
					biometricClient.FingersTemplateSize = NTemplateSize.Large;

					// Create template from added finger image(s)
					var status = biometricClient.CreateTemplate(subject);
					Console.WriteLine(status == NBiometricStatus.Ok
						? "Template extracted"
						: String.Format("Extraction failed: {0}", status));

					// Save template to file
					if (status == NBiometricStatus.Ok)
					{
						File.WriteAllBytes(args[1], subject.GetTemplateBuffer().ToArray());
						Console.WriteLine("Template saved successfully");
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
