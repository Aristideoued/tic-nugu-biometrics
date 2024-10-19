using System;
using System.IO;

using Neurotec.Biometrics.Client;
using Neurotec.Biometrics.Standards;
using Neurotec.Licensing;
using Neurotec.Biometrics;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage: {0} [IIRecord] [NTemplate]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\t[IIRecord]  - input IIRecord");
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

			const string license = "IrisClient";
			//const string license = "IrisFastExtractor";

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
					// Read IIRecord from file
					byte[] iiRecordData = File.ReadAllBytes(args[0]);

					// Create IIRecord
					var iiRec = new IIRecord(iiRecordData, BdifStandard.Iso);

					// Read all images from IIRecord
					foreach (IirIrisImage irisImage in iiRec.IrisImages)
					{
						var iris = new NIris { Image = irisImage.ToNImage() };
						subject.Irises.Add(iris);
					}

					// Set iris template size (large is recommended for enrolment to database) (optional)
					biometricClient.IrisesTemplateSize = NTemplateSize.Large;

					// Create template from added iris image(s)
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
