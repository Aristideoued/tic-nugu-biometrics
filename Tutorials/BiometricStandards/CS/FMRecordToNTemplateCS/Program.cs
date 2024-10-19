using System;
using System.IO;
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
			Console.WriteLine("\t{0} [FMRecord] [NTemplate] [Standard] [FlagUseNeurotecFields]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[FMRecord] - filename of FMRecord.");
			Console.WriteLine("\t[NTemplate] - filename of NTemplate to be created.");
			Console.WriteLine("\t[Standard] - FMRecord standard (ISO or ANSI)");
			Console.WriteLine("\t[FlagUseNeurotecFields] - 1 if FmrFingerView.FlagUseNeurotecFields flag is used; otherwise, 0 flag was not used.");
			Console.WriteLine();
			Console.WriteLine("example:");
			Console.WriteLine("\t{0} fmrecord.dat ntemplate.dat ISO 1", TutorialUtils.GetAssemblyName());

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 4)
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

				string fmRecordFileName = args[0];
				string outputFileName = args[1];
				BdifStandard standard = (BdifStandard)Enum.Parse(typeof(BdifStandard), args[2], true);
				int flagUseNeurotecFields = int.Parse(args[3]);

				if (fmRecordFileName == "/?" || fmRecordFileName == "help")
				{
					return Usage();
				}

				byte[] storedFmRecord = File.ReadAllBytes(fmRecordFileName);

				// Creating FMRecord object from FMRecord stored in memory
				FMRecord fmRecord = flagUseNeurotecFields == 1 ? new FMRecord(new NBuffer(storedFmRecord), FmrFingerView.FlagUseNeurotecFields, standard) : new FMRecord(new NBuffer(storedFmRecord), standard);

				// Converting FMRecord object to NTemplate object
				NTemplate nTemplate = fmRecord.ToNTemplate();
				// Packing NTemplate object
				byte[] packedNTemplate = nTemplate.Save().ToArray();

				File.WriteAllBytes(outputFileName, packedNTemplate);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
