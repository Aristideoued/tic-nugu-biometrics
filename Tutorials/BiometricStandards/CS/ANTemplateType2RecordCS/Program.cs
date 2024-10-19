using System;
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
			Console.WriteLine("\t{0} [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[ANTemplate] - filename for ANTemplate.");
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

			if (args.Length != 6)
			{
				return Usage();
			}
			//=========================================================================
			// CHOOSE LICENCES !!!
			//=========================================================================
			// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
			// If you are using a TRIAL version - choose any of them.

			const string licenses = "FingerClient,PalmClient,FaceClient,IrisClient";
			//const string licenses = "FingerFastExtractor,FaceFastExtractor,IrisFastExtractor";

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

				string tot = args[1]; // type of transaction
				string dai = args[2]; // destination agency identifier
				string ori = args[3]; // originating agency identifier
				string tcn = args[4]; // transaction control number
				string enc = args[5]; // encoding type

				if ((tot.Length < 3) || (tot.Length > 4))
				{
					Console.WriteLine("Tot parameter should be 3 or 4 characters length.");
					return -1;
				}

				BdifEncodingType encoding = (enc == "1") ? BdifEncodingType.Xml : BdifEncodingType.Traditional;

				int nameFieldNumber = 18;// exemplary field number for subject's name and surname
				string nameFieldValue = "name, surname"; // exemplary subject's name and surname
				int placeOfBirthFieldNumber = 20;// exemplary field number for subject's place of birth
				string placeOfBirthFieldValue = "UK"; // exemplary subject's place of birth
				int dateOfBirthFieldNumber = 22;// exemplary field number for subject's date of birth
				string dateOfBirthFieldValue = "19700131"; // exemplary subject's date of birth
				int genderFieldNumber = 24;// exemplary field number for subject's gender
				string genderFieldValue = "M"; // exemplary subject's gender

				using (var template = new ANTemplate(ANTemplate.VersionCurrent, tot, dai, ori, tcn, 0))
				{
					ANType2Record record = template.Records.AddType2();

					// Adds fields for "traditional" binary encoding
					if (encoding == BdifEncodingType.Traditional)
					{
						record.Fields.Add(nameFieldNumber, nameFieldValue);
						record.Fields.Add(placeOfBirthFieldNumber, placeOfBirthFieldValue);
						record.Fields.Add(dateOfBirthFieldNumber, dateOfBirthFieldValue);
						record.Fields.Add(genderFieldNumber, genderFieldValue);
					}
					else // Adds fields for NIEM-conformant XML encoding
					{
						record.Fields.Add(nameFieldNumber, "PersonName", nameFieldValue);
						record.Fields.Add(placeOfBirthFieldNumber, "PersonBirthPlaceCode", placeOfBirthFieldValue);
						record.Fields.Add(dateOfBirthFieldNumber, "PersonBirthDate", dateOfBirthFieldValue);
						record.Fields.Add(genderFieldNumber, "PersonSexCode", genderFieldValue);
					}
					template.Save(args[0], encoding);
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
