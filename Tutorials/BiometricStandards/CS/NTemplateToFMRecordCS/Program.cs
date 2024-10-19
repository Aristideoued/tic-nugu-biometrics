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
			Console.WriteLine("\t{0} [NTemplate] [FMRecord] [Standard&Version] [FlagUseNeurotecFields] [Encoding]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[NTemplate] - filename of NFRecord.");
			Console.WriteLine("\t[FMRecord] - filename of FMRecord to be created.");
			Console.WriteLine("\t[Standard & Version] - FMRecord standard & version");
			Console.WriteLine("\t\tANSI2 - ANSI/INCITS 378-2004");
			Console.WriteLine("\t\tANSI3.5 - ANSI/INCITS 378-2009");
			Console.WriteLine("\t\tISO2 - ISO/IEC 19794-2:2005");
			Console.WriteLine("\t\tISO3 - ISO/IEC 19794-2:2011");
			Console.WriteLine("\t\tMINEX - Minex compliant record (ANSI/INCITS 378-2004 without extended data)");
			Console.WriteLine("\t[FlagUseNeurotecFields] - 1 if FmrFingerView.FlagUseNeurotecFields flag is uses; otherwise, 0 flag was not used. For Minex compliant record must be 0.");
			Console.WriteLine("\tEncoding - specifies FMRecord encoding type\n");
			Console.WriteLine("\t\t0 - Traditional binary encoding \n");
			Console.WriteLine("\t\t1 - XML encoding (supported only for ISO3)\n");
			Console.WriteLine("");
			Console.WriteLine("examples:");
			Console.WriteLine("\t{0} ntemplate.dat fmrecord.dat ISO3 1", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\t{0} ntemplate.dat fmrecord.dat MINEX 0", TutorialUtils.GetAssemblyName());

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 5)
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

				string nTemplateFileName = args[0];
				string outputFileName = args[1];
				int flagUseNeurotecFields = int.Parse(args[3]);
				BdifStandard standard = 0;
				
				uint flags = 0;
				NVersion version;
				switch (args[2])
				{
					case "ANSI2":
						standard = BdifStandard.Ansi;
						version = FMRecord.VersionAnsi20;
						break;
					case "ISO2":
						standard = BdifStandard.Iso;
						version = FMRecord.VersionIso20;
						break;
					case "ISO3":
						standard = BdifStandard.Iso;
						version = FMRecord.VersionIso30;
						break;
					case "ANSI3.5":
						standard = BdifStandard.Ansi;
						version = FMRecord.VersionAnsi35;
						break;
					case "MINEX":
						if (flagUseNeurotecFields != 0) throw new ArgumentException("MINEX compliant record and FlagUseNeurotecFields is incompatible");
						standard = BdifStandard.Ansi;
						version = FMRecord.VersionAnsi20;
						flags = FmrFingerView.FlagSkipRidgeCounts | FmrFingerView.FlagSkipSingularPoints | FmrFingerView.FlagSkipNeurotecFields;
						break;
					default:
						throw new ArgumentException("Version was not recognised");
				}

				flags |= flagUseNeurotecFields == 1 ? FmrFingerView.FlagUseNeurotecFields : 0;
				
				byte[] packedNTemplate = File.ReadAllBytes(nTemplateFileName);

				// Creating NTemplate object from packed NTemplate
				var nTemplate = new NTemplate(packedNTemplate);

				// Retrieving NFTemplate object from NTemplate object
				NFTemplate nfTemplate = nTemplate.Fingers;

				if (nfTemplate != null)
				{
					// Creating FMRecord object from NFTemplate object
					var fmRecord = new FMRecord(nfTemplate, standard, version);
					// Storing FMRecord object in memory
					BdifEncodingType encoding = int.Parse(args[4]) == 1 ? BdifEncodingType.Xml : BdifEncodingType.Traditional;
					byte[] storedFmRecord = fmRecord.Save(encoding, flags).ToArray();
					File.WriteAllBytes(outputFileName, storedFmRecord);
				}
				else
				{
					Console.WriteLine("There are no NFRecord in NTemplate");
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
