using System;
using System.IO;

using Neurotec.IO;
using Neurotec.Biometrics.Standards;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage: {0} [FIRecord] [Standard] [Version] [Encoding] {{[image]}}", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\t[FIRecord] - output FIRecord");
			Console.WriteLine("\t[Standard] - standard for the record (ANSI or ISO)");
			Console.WriteLine("\t[Version] - version for the record");
			Console.WriteLine("\t\t 1 - ANSI/INCITS 381-2004");
			Console.WriteLine("\t\t 2.5 - ANSI/INCITS 381-2009");
			Console.WriteLine("\t\t 1 - ISO/IEC 19794-4:2005");
			Console.WriteLine("\t\t 2 - ISO/IEC 19794-4:2011");
			Console.WriteLine("\t[Encoding] - encoding format\n");
			Console.WriteLine("\t\t bin - Traditional binary encoding \n");
			Console.WriteLine("\t\t xml - XML encoding (supported only for ISO v2)\n");
			Console.WriteLine("\t[image] - one or more images");

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

			FIRecord fi = null;
			try
			{
				// Obtain license
				if (!NLicense.Obtain("/local", 5000, license))
				{
					throw new NotActivatedException(string.Format("Could not obtain license: {0}", license));
				}

				var standard = (BdifStandard)Enum.Parse(typeof(BdifStandard), args[1], true);
				NVersion version;
				switch (args[2])
				{
					case "1":
						version = standard == BdifStandard.Ansi ? FIRecord.VersionAnsi10 : FIRecord.VersionIso10;
						break;
					case "2":
						if (standard != BdifStandard.Iso) throw new ArgumentException("Standard and version is incompatible");
						version = FIRecord.VersionIso20;
						break;
					case "2.5":
						if (standard != BdifStandard.Ansi) throw new ArgumentException("Standard and version is incompatible");
						version = FIRecord.VersionAnsi25;
						break;
					default:
						throw new ArgumentException("Version was not recognised");
				}
				BdifEncodingType encoding;
				switch (args[3])
				{
					case "bin":
						encoding = BdifEncodingType.Traditional;
						break;
					case "xml":
						if (standard != BdifStandard.Iso || version != FIRecord.VersionIso20) throw new ArgumentException("Xml encoding only available in ISO 2.0");
						encoding = BdifEncodingType.Xml;
						break;
					default:
						throw new ArgumentException("Encoding unrecognised");
				}

				ushort vertScanResolution = 500;//ppi
				ushort horzScanResolution = 500;//ppi
				BdifFPPosition fPosition = BdifFPPosition.RightThumb;
				for (int i = 4; i < args.Length; i++)
				{
					/**
					 * Image must be compressed using valid compression algorithm for FIRecord.
					 *	How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
					*/
					using (NBuffer imageBuffer = NFile.ReadAllBytes(args[i]))
					{
						if (fi == null)
						{
							fi = new FIRecord(standard, version, 10, fPosition, horzScanResolution, vertScanResolution, imageBuffer);
						}
						else
							fi.FingerViews.Add(fPosition, horzScanResolution, vertScanResolution, imageBuffer);
					}
				}

				if (fi != null)
				{
					File.WriteAllBytes(args[0], fi.Save(encoding).ToArray());
					Console.WriteLine("FIRecord saved to {0}", args[0]);
				}
				else
				{
					Console.WriteLine("No images were added to FIRecord");
				}

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
			finally
			{
				if (fi != null)
				{
					fi.Dispose();
				}
			}
		}
	}
}
