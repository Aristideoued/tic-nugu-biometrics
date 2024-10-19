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
			Console.WriteLine("\t{0} [srcImage] [dstImage]", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			Console.WriteLine("\tsrcImage - filename of source WSQ image.");
			Console.WriteLine("\tdstImage - name of a file to save converted image to.");
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

				// Get WSQ image format
				// Create an NImage from a WSQ image file
				using (NImage image = NImage.FromFile(args[0], NImageFormat.Wsq))
				{
					Console.WriteLine("Loaded wsq bitrate: {0}", ((WsqInfo)image.Info).BitRate);
					// Pick a format to save in, e.g. JPEG
					NImageFormat dstFormat = NImageFormat.Jpeg;
					// Save image to specified file
					image.Save(args[1], dstFormat);
					Console.WriteLine("{0} Image was saved to {1}", dstFormat.Name, args[1]);
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
