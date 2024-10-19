using System;

using Neurotec.Images;
using Neurotec.Devices;
using Neurotec.Licensing;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [frameCount]", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			Console.WriteLine("\tframeCount - number of frames to capture from each camera to current directory");
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

			const string license = "FaceExtractor";
			//const string license = "FaceClient";
			//const string license = "FaceFastExtractor";
			//const string license = "SentiVeillance";

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

				int frameCount = int.Parse(args[0]);
				if (frameCount == 0)
				{
					Console.WriteLine("No frames will be captured as frame count is not specified");
				}

				using (var deviceManager = new NDeviceManager { DeviceTypes = NDeviceType.Camera, AutoPlug = true })
				{
					deviceManager.Initialize();
					Console.WriteLine("Device manager created. Found cameras: {0}", deviceManager.Devices.Count);

					foreach (NCamera camera in deviceManager.Devices)
					{
						Console.Write("Found camera {0}", camera.DisplayName);

						camera.StartCapturing();

						if (frameCount > 0)
						{
							Console.Write(", capturing");
							for (int i = 0; i < frameCount; ++i)
							{
								string filename = String.Format("{0}_{1:d4}.jpg", camera.DisplayName, i);
								using (NImage image = camera.GetFrame())
								{
									image.Save(filename);
								}
								Console.Write(".");
							}
							Console.Write(" Done");
							Console.WriteLine();
						}
						camera.StopCapturing();
					}
				}
				Console.WriteLine("Done");

				return -1;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
