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
			Console.WriteLine("usage: {0} [IIRecord] [Standard] [Version] [image]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\t[IIRecord] - output IIRecord");
			Console.WriteLine("\t[Standard] - standard for the record (ANSI or ISO)");
			Console.WriteLine("\t[Version] - version for the record");
			Console.WriteLine("\t\t 1 - ANSI/INCITS 379-2004");
			Console.WriteLine("\t\t 1 - ISO/IEC 19794-6:2005");
			Console.WriteLine("\t\t 2 - ISO/IEC 19794-6:2011");
			Console.WriteLine("\t[image]    - one or more images");

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

			const string license = "IrisClient";
			//const string license = "IrisFastExtractor";

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

			IIRecord iiRec = null;
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
						version = standard == BdifStandard.Ansi ? IIRecord.VersionAnsi10 : IIRecord.VersionIso10;
						break;
					case "2":
						if (standard != BdifStandard.Iso) throw new ArgumentException("Standard and version is incompatible");
						version = IIRecord.VersionIso20;
						break;
					default:
						throw new ArgumentException("Version was not recognised");
				}

				BdifEyePosition irisPosition = BdifEyePosition.Left;
				for (int i = 3; i < args.Length; i++)
				{
					using (NBuffer imageBuffer = NFile.ReadAllBytes(args[i]))
					{
						if (iiRec == null)
						{
							iiRec = new IIRecord(standard, version, irisPosition, imageBuffer);
						}
						else
							iiRec.IrisImages.Add(irisPosition, imageBuffer);
					}
				}

				if (iiRec != null)
				{
					File.WriteAllBytes(args[0], iiRec.Save().ToArray());

					Console.WriteLine("IIRecord saved to {0}", args[0]);
				}
				else
				{
					Console.WriteLine("No images were added to IIRecord");
				}

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
			finally
			{
				if (iiRec != null)
				{
					iiRec.Dispose();
				}
			}
		}
	}
}
