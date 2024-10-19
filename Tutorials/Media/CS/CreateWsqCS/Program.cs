using System;
using Neurotec.Images;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [srcImage] [dstImage] <optional: bitRate>", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			Console.WriteLine("\tsrcImage - filename of source finger image.");
			Console.WriteLine("\tdstImage - name of a file to save the created WSQ image to.");
			Console.WriteLine("\tbitRate  - specifies WSQ image compression level. Typical bit rates: 0.75, 2.25.");
			Console.WriteLine();
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

				// Create an NImage from file
				using (NImage image = NImage.FromFile(args[0]))
				{
					// Create WSQInfo to store bit rate
					using (var info = (WsqInfo) NImageFormat.Wsq.CreateInfo(image))
					{
						// Set specified bit rate (or default if bit rate was not specified).
						var bitrate = args.Length > 2 ? float.Parse(args[2]) : WsqInfo.DefaultBitRate;
						info.BitRate = bitrate;

						// Save image in WSQ format and bitrate to file.
						image.Save(args[1], info);
						Console.WriteLine("WSQ image with bit rate {0} was saved to {1}", bitrate, args[1]);
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
