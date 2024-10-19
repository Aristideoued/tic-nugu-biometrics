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
			Console.WriteLine("\t{0} [FMCRecord] [NTemplate] [Version] [MinutiaeFormat] [ReadBerTlv]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[FMCRecord] - filename of FMCRecord.");
			Console.WriteLine("\t[NTemplate] - filename of NTemplate to be created.");
			Console.WriteLine("\t[Version] - FMCRecord version.");
			Console.WriteLine("\t\tISO2 - ISO/IEC 19794-2:2005.");
			Console.WriteLine("\t\tISO3 - ISO/IEC 19794-2:2011.");
			Console.WriteLine("\t[MinutiaeFormat] - card format of minutiae data.");
			Console.WriteLine("\t\tC - compact size.");
			Console.WriteLine("\t\tN - normal size (ISO2 only).");
			Console.WriteLine("\tReadBerTlvDo - FMCRecord read from buffer option");
			Console.WriteLine("\t\t1 - Biometric Data Template (BDT) or Cardholder");
			Console.WriteLine("\t\t    Biometric Data (CBD) BER-TLV DO (Data Object)");
			Console.WriteLine("\t\t0 - minutiae data buffer only.\n");
			Console.WriteLine();
			Console.WriteLine("example:");
			Console.WriteLine("\t{0}  fmcRecord.FMCRecord template.NTemplate ISO3 C 1", TutorialUtils.GetAssemblyName());

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 5)
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

				string fmcRecordFileName = args[0];
				string outputFileName = args[1];

				BdifStandard standard = BdifStandard.Iso;
				uint flags = 0; // BdifTypes.FlagNonStrictRead - removes non-unique minutiae for FMCRecord.VersionIso30 only
				
				NVersion standardVersion;
				if (args[2].Equals("ISO2"))
				{
					standardVersion = FMCRecord.VersionIso20;
				}
				else if (args[2].Equals("ISO3"))
				{
					standardVersion = FMCRecord.VersionIso30;
				}
				else
				{
					throw new ArgumentException("Wrong standard");
				}

				FmcrMinutiaFormat minutiaFormat;
				if (args[3].Equals("C"))
				{
					minutiaFormat = FmcrMinutiaFormat.CompactSize;
				}
				else if (args[3].Equals("N"))
				{
					minutiaFormat = FmcrMinutiaFormat.NormalSize;
				}
				else
				{
					throw new ArgumentException("Wrong minutia format");
				}

				// Check if full FMCRecord BER-TLV Data Object (DO) (e.g., Biometric Data Template (BDT) or Cardholder Biometric Data (CBD)) or minutiae buffer only is available
				bool isBerTlv = args[4].Equals("1");

				byte[] storedFmcRecord = File.ReadAllBytes(fmcRecordFileName);
				FMCRecord fmcRecord = null;
				if (isBerTlv)
				{
					// Create FMCRecord object from FMCRecord BER-TLV Data Object (DO) stored in memory (e.g., BDT or CBD BER-TLV DO)
					fmcRecord = new FMCRecord(storedFmcRecord, standard, standardVersion, minutiaFormat, flags);
				}
				else //if (!isBerTlv)
				{
					// Create FMCrecord and read minutiae data from buffer to FMCRecord
					fmcRecord = new FMCRecord(standard, standardVersion, minutiaFormat);
					fmcRecord.SetMinutiaeBuffer(new NBuffer(storedFmcRecord));
				}

				// Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
				if (fmcRecord.Version == FMCRecord.VersionIso20 && !fmcRecord.ValidateMinutiaeUniqueness())
				{
					Console.WriteLine("!!!WARNING!!!:");
					Console.WriteLine("Not all minutiae in FMCRecord are unique!");
					Console.WriteLine("Please, try using ISO3 version with BdifTypes.FlagNonStrictRead flag to remove non-unique minutiae while reading.");
				}

				// Convert FMCRecord to NFRecord
				NFRecord nfRecord = fmcRecord.ToNFRecord();

				// Add NFRecord to NFTemplate
				NFTemplate nfTemplate = new NFTemplate();
				nfTemplate.Records.Add(nfRecord);
				// Set NFTemplate to NTemplate
				NTemplate nTemplate = new NTemplate();
				nTemplate.Fingers = nfTemplate;

				// Pack NTemplate object
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
