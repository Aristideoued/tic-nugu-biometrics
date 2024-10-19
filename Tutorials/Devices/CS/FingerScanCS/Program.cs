using System;
using Neurotec.Biometrics;
using Neurotec.Devices;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [imageCount]", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			Console.WriteLine("\timageCount - count of fingerprint images to be scanned");
			Console.WriteLine();

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 1)
			{
				return Usage();
			}

			//=========================================================================
			// CHOOSE LICENCES !!!
			//=========================================================================
			// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
			// If you are using a TRIAL version - choose any of them.

			const string license = "FingerExtractor";
			//const string license = "FingerClient";
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

				int imageCount = int.Parse(args[0]);
				if (imageCount == 0)
				{
					Console.WriteLine("No frames will be captured as frame count is not specified");
				}

				using (var deviceManager = new NDeviceManager { DeviceTypes = NDeviceType.FingerScanner, AutoPlug = true })
				{
					deviceManager.Initialize();
					Console.WriteLine("Device manager created. Found scanners: {0}", deviceManager.Devices.Count);

					foreach (NFScanner scanner in deviceManager.Devices)
					{
						Console.WriteLine("Found scanner {0}, capturing fingerprints", scanner.DisplayName);

						for (int i = 0; i < imageCount; i++)
						{
							Console.Write("\tImage {0} of {1}. Please put your fingerprint on scanner: ", i + 1, imageCount);
							string filename = String.Format("{0}_{1:d4}.jpg", scanner.DisplayName, i);
							using (var biometric = new NFinger())
							{
								biometric.Position = NFPosition.Unknown;
								var biometricStatus = scanner.Capture(biometric, -1);
								if (biometricStatus != NBiometricStatus.Ok)
								{
									Console.WriteLine("Failed to capture from scanner, status: {0}", biometricStatus);
									continue;
								}
								biometric.Image.Save(filename);
								Console.WriteLine("Image captured");
							}
						}
					}
				}
				Console.WriteLine("Done");

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
