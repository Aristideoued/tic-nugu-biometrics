using System;
using System.IO;

using Neurotec.Biometrics;
using Neurotec.Biometrics.Standards;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		const byte minutiaTruncationQualityThreshold = 0;
		/* NOTE: ISO/IEC 19794-2 (informative) minutiae count range recommendations for card formats:
		 - FMCRecord.DefaultMinEnrollMC to FMCRecord.DefaultMaxEnrollMC for enroll, 
		 - FMCRecord.DefaultMinVerifyMC to FMCRecord.DefaultMaxVerifyMC for verify.
		*/
		const int minutiaTruncationMaximalCount = 48;
		const NFMinutiaTruncationAlgorithm minutiaTruncationAlgorithm = NFMinutiaTruncationAlgorithm.QualityAndCenterOfMass; 

		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [NTemplate] [FMCRecord] [Version] [MinutiaeFormat] [SaveBiometricDataTemplate]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[NTemplate] - filename of NFCRecord.");
			Console.WriteLine("\t[FMCRecord] - filename of FMCRecord to be created.");
			Console.WriteLine("\t[Version] - FMCRecord version");
			Console.WriteLine("\t\tISO2 - ISO/IEC 19794-2:2005");
			Console.WriteLine("\t\tISO3 - ISO/IEC 19794-2:2011");
			Console.WriteLine("\t[tMinutiaeFormat] - card format of minutiae data.");
			Console.WriteLine("\t\tC - compact size");
			Console.WriteLine("\t\tN - normal size (ISO2 only)");
			Console.WriteLine("\tSaveBiometricDataTemplate - FMCRecord save to buffer option");
			Console.WriteLine("\t\t1 - full Biometric Data Template (BDT) BER-TLV DO (Data Object)");
			Console.WriteLine("\t\t0 - minutiae data only");
			Console.WriteLine("");
			Console.WriteLine("examples:");
			Console.WriteLine("\t{0}  template.NTemplate fmcrecord.FMCRecord ISO3 C 1", TutorialUtils.GetAssemblyName());

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

				BdifStandard standard = BdifStandard.Iso;
				NVersion standardVersion;
				FmcrMinutiaOrder minutiaOrder = FmcrMinutiaOrder.None;
				uint flags = FMCRecord.FlagSkipAllExtendedData | FMCRecord.FlagUseBiometricDataTemplate; // the most common use case of minutiae data only within on-card records

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

				// Check if full FMCRecord Biometric Data Template (BDT) BER-TLV Data Object (DO) or minutiae buffer only to be saved
				bool isBdtBerTlv = args[4].Equals("1");

				byte[] packedNTemplate = File.ReadAllBytes(args[0]);
				NTemplate nTemplate = new NTemplate(packedNTemplate);
				NFTemplate nfTemplate = nTemplate.Fingers;
				if (nfTemplate != null && nfTemplate.Records.Count > 0)
				{
					// Retrieve NFRecord object from NFTemplate object
					NFRecord nfRecord = nfTemplate.Records[0];

					// Truncate minutiae by quality
					nfRecord.TruncateMinutiaeByQuality(minutiaTruncationQualityThreshold, minutiaTruncationMaximalCount);

					// Truncate minutiae using specified truncation algorithm (if more than desired minutiae with quality above minutiaTruncationQualityThreshold remain)
					nfRecord.TruncateMinutiae(minutiaTruncationAlgorithm, minutiaTruncationMaximalCount);

					// Create FMCRecord object from NFRecord object
					FMCRecord fmcRecord = new FMCRecord(nfRecord, standard, standardVersion, minutiaFormat, minutiaOrder, 0);

					// Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
					if (fmcRecord.Version == FMCRecord.VersionIso20 && !fmcRecord.ValidateMinutiaeUniqueness())
					{
						Console.WriteLine("!!!WARNING!!!:");
						Console.WriteLine("Not all minutiae in FMCRecord are unique!");
						Console.WriteLine("Please, try using ISO3 version to remove non-unique minutiae while conversion.");
					}

					if (isBdtBerTlv)
					{
						// Store FMCRecord object in memory as ISO/IEC 19794-2 and ISO/IEC 7816-11 compliant Biometric Data Template (BDT) BER-TLV Data Object (DO)
						byte[] storedFmcRecord = fmcRecord.Save(flags).ToArray();
						File.WriteAllBytes(args[1], storedFmcRecord);
					}
					else
					{
						// Get minutiae data as buffer
						byte[] minutiaeBuffer = fmcRecord.GetMinutiaeBuffer().ToArray();
						File.WriteAllBytes(args[1], minutiaeBuffer);
					}
				}
				else 
				{
					Console.WriteLine("There are no NFRecords in NTemplate");
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
