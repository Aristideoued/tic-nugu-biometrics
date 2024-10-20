using System;
using System.Collections.Generic;
using System.IO;
using Neurotec.Biometrics;
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
			Console.WriteLine("\t{0} [CbeffRecord] [PatronFormat] [NTemplate]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[CbeffRecord] - filename of CbeffRecord.");
			Console.WriteLine("\t[PatronFormat] - hex number identifying patron format (all supported values can be found in CbeffRecord class documentation).");
			Console.WriteLine("\t[NTemplate] - filename of NTemplate.");
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

				// Read CbeffRecord buffer
				var packedCbeffRecord = new NBuffer(File.ReadAllBytes(args[0]));

				// Get CbeffRecord patron format
				// all supported patron formats can be found in CbeffRecord class documentation
				uint patronFormat = uint.Parse(args[1], System.Globalization.NumberStyles.HexNumber);

				// Creating CbeffRecord object from NBuffer object
				using (var cbeffRecord = new CbeffRecord(packedCbeffRecord, patronFormat))
				using (var subject = new NSubject())
				using (var engine = new NBiometricEngine())
				{
					// Setting CbeffRecord
					subject.SetTemplate(cbeffRecord);

					// Extracting template details from specified CbeffRecord data
					engine.CreateTemplate(subject);

					if (subject.Status == NBiometricStatus.Ok)
					{
						File.WriteAllBytes(args[2], subject.GetTemplateBuffer().ToArray());
						Console.WriteLine("Template successfully saved");
					}
					else
					{
						Console.WriteLine("Template creation failed! Status: {0}", subject.Status);
						return -1;
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