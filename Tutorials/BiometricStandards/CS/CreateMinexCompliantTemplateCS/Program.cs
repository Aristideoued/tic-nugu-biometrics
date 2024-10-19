using System;
using System.IO;
using System.Collections.Generic;
using Neurotec.Biometrics;
using Neurotec.Biometrics.Standards;
using Neurotec.Licensing;
using Neurotec.IO;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [image] [template]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[image] - image filename to extract.");
			Console.WriteLine("\t[template] - FMRecord to store extracted features.");
			Console.WriteLine();
			Console.WriteLine("example:");
			Console.WriteLine("\t{0} image.jpg fmrecord.FMRecord", TutorialUtils.GetAssemblyName());

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

				using (var biometricEngine = new NBiometricEngine())
				using (var subject = new NSubject())
				using (var finger = new NFinger())
				{
					string outputFileName = args[1];

					finger.FileName = args[0];
					subject.Fingers.Add(finger);
					biometricEngine.FingersExtractionScenario = NExtractionScenario.Minex;

					NBiometricTask task = biometricEngine.CreateTask(NBiometricOperations.CreateTemplate | NBiometricOperations.AssessQuality, subject);
					biometricEngine.PerformTask(task);
					NBiometricStatus biometricStatus = task.Status;

					if (biometricStatus == NBiometricStatus.Ok)
					{
						Console.WriteLine("ANSI template extracted.");

						// Save FMRecord
						byte[] storedFmRecord = subject.GetTemplateBuffer(CbeffBiometricOrganizations.IncitsTCM1Biometrics,
							CbeffBdbFormatIdentifiers.IncitsTCM1BiometricsFingerMinutiaeU,
							FMRecord.VersionAnsi20).ToArray();
						File.WriteAllBytes(outputFileName, storedFmRecord);
					}
					else
					{
						Console.WriteLine("Template extraction failed!");
						Console.WriteLine("Biometric status = {0}", biometricStatus);
						if (task.Error != null)
						{
							return TutorialUtils.PrintException(task.Error);
						}
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
