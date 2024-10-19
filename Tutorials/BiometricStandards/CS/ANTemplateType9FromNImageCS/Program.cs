using System;
using Neurotec.Biometrics;
using Neurotec.Biometrics.Client;
using Neurotec.Biometrics.Standards;
using Neurotec.Licensing;
using System.Linq;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [NImage] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [FmtFlag] [Encoding]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[NImage]     - filename with image file.");
			Console.WriteLine("\t[ANTemplate] - filename for ANTemplate.");
			Console.WriteLine("\t[Tot] - specifies type of transaction.");
			Console.WriteLine("\t[Dai] - specifies destination agency identifier.");
			Console.WriteLine("\t[Ori] - specifies originating agency identifier.");
			Console.WriteLine("\t[Tcn] - specifies transaction control number.");
			Console.WriteLine("\t[FmtFlag] - specifies finger minutiae format. 1 if minutiae are saved in standard way (used until version 4.0), 0 - if in vendor specific 'INCITS 378' block (recomended from version 5.0).");
			Console.WriteLine("\t[Encoding] - specifies ANTemplate encoding type.");
			Console.WriteLine("\t\t0 - Traditional binary encoding.");
			Console.WriteLine("\t\t1 - NIEM-conformant XML encoding.");
			Console.WriteLine("");

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 8)
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
				string fmt = args[6]; // pointer to string that specifies minutiae format
				string enc = args[7]; // encoding type

				bool fmtBool = fmt.Equals("1") ? true : false;
				if ((tot.Length < 3) || (tot.Length > 4))
				{
					Console.WriteLine("Tot parameter should be 3 or 4 characters length.");
					return -1;
				}

				BdifEncodingType encoding = (enc == "1") ? BdifEncodingType.Xml : BdifEncodingType.Traditional;
				NFPosition position = NFPosition.RightThumb;

				//NTemplate from which ANTemplate should be initialised
				using (var biometricClient = new NBiometricClient())
				using (var subject = new NSubject())
				using (var finger = new NFinger())
				{
					// Read finger image from file and add it to NFinger object
					finger.FileName = args[0];

					// Set finger position
					finger.Position = position;

					// Read finger image from file and add it to NSubject
					subject.Fingers.Add(finger);

					// Create template from added finger image
					var status = biometricClient.CreateTemplate(subject);
					if (status == NBiometricStatus.Ok)
					{
						Console.WriteLine("Template extracted");

						// Create empty ANTemplate object with only type 1 record in it
						var template = new ANTemplate(ANTemplate.VersionCurrent, tot, dai, ori, tcn);

						// Create Type 9 record
						var record = template.Records.AddType9(fmtBool, subject.GetTemplate().Fingers.Records.First());

						// Store ANTemplate object with type 9 record in file
						template.Save(args[1], encoding);
					}
					else
					{
						Console.WriteLine("Extraction failed: {0}", status);
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
