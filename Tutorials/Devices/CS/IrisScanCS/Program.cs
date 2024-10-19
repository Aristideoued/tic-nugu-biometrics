using System;

using Neurotec.Biometrics;
using Neurotec.Devices;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			//=========================================================================
			// CHOOSE LICENCES !!!
			//=========================================================================
			// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
			// If you are using a TRIAL version - choose any of them.

			const string license = "IrisExtractor";
			//const string license = "IrisClient";
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

			try
			{
				// Obtain license
				if (!NLicense.Obtain("/local", 5000, license))
				{
					throw new NotActivatedException(string.Format("Could not obtain license: {0}", license));
				}

				using (var deviceManager = new NDeviceManager { DeviceTypes = NDeviceType.IrisScanner, AutoPlug = true })
				{
					deviceManager.Initialize();
					Console.WriteLine("Device manager created. Found scanners: {0}", deviceManager.Devices.Count);

					foreach (NIrisScanner scanner in deviceManager.Devices)
					{
						Console.Write("Found scanner {0}", scanner.DisplayName);

						Console.Write("\tCapturing right iris: ");
						using (var rightIrisBiometric = new NIris())
						{
							rightIrisBiometric.Position = NEPosition.Right;
							var biometricStatus = scanner.Capture(rightIrisBiometric, -1);
							if (biometricStatus != NBiometricStatus.Ok)
							{
								Console.WriteLine("Failed to capture from scanner, status: {0}", biometricStatus);
								continue;
							}
							string filename = string.Format("{0}_iris_right.jpg", scanner.DisplayName);
							rightIrisBiometric.Image.Save(filename);
							Console.WriteLine("Done");
						}

						Console.Write("\tCapturing left eye: ");
						using (var leftIrisBiometric = new NIris())
						{
							leftIrisBiometric.Position = NEPosition.Left;
							var biometricStatus = scanner.Capture(leftIrisBiometric, -1);
							if (biometricStatus != NBiometricStatus.Ok)
							{
								Console.WriteLine("Failed to capture from scanner, status: {0}", biometricStatus);
								continue;
							}
							string filename = string.Format("{0}_iris_left.jpg", scanner.DisplayName);
							leftIrisBiometric.Image.Save(filename);
							Console.WriteLine("Done");
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
