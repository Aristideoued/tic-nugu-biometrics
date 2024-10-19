using System;
using System.IO;
using Neurotec.Biometrics.Standards;
using Neurotec.IO;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		private enum BdbFormat
		{
			ANTemplate = 0x001B8019,
			FCRecordAnsi = 0x001B0501,
			FCRecordIso = 0x01010008,
			FIRecordAnsi = 0x001B0401,
			FIRecordIso = 0x01010007,
			FMRecordAnsi = 0x001B0202,
			FMRecordIso = 0x01010002,
			IIRecordAnsiPolar = 0x001B0602,
			IIRecordIsoPolar = 0x0101000B,
			IIRecordAnsiRectilinear = 0x001B0601,
			IIRecordIsoRectilinear = 0x01010009
		}

		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [ComplexCbeffRecord] [PatronFormat]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[ComplexCbeffRecord] - filename of CbeffRecord which will be created.");
			Console.WriteLine("\t[PatronFormat] - hex number identifying patron format (all supported values can be found in CbeffRecord class documentation).");
			Console.WriteLine("");

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 2)
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

				// Create CbeffRecord object
				var cbeffRecord = new CbeffRecord(packedCbeffRecord, patronFormat);

				// Start unpacking the record
				UnpackRecords(cbeffRecord);

				Console.WriteLine("Records sucessfully saved");
				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}

		private static void UnpackRecords(CbeffRecord cbeffRecord)
		{
			int recordNumber = 0;
			UnpackRecords(cbeffRecord, ref recordNumber);
		}

		private static void UnpackRecords(CbeffRecord cbeffRecord, ref int recordNumber)
		{
			if (cbeffRecord.Records.Count == 0)
			{
				// Write root record to file
				RecordToFile(cbeffRecord, recordNumber++);
			}
			else
			{
				// Go through all record in this CbeffRecord
				foreach (var record in cbeffRecord.Records)
				{
					// Start unpacking complex record
					UnpackRecords(record, ref recordNumber);
				}
			}
		}

		private static void RecordToFile(CbeffRecord record, int recordNumber)
		{
			string fileName;
			try
			{
				// Find Record format
				fileName = string.Format("Record{0}_{1}.dat", recordNumber, Enum.GetName(typeof(BdbFormat), record.BdbFormat));
			}
			catch
			{
				fileName = string.Format("Record{0}_UnknownFormat.dat", recordNumber);
			}

			// Save specified record
			File.WriteAllBytes(fileName, record.BdbBuffer.ToArray());
		}
	}
}
