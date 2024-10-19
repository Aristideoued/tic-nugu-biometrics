using System;
using Neurotec.Devices;
using Neurotec.Licensing;
using Neurotec.Sound;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [bufferCount]", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			Console.WriteLine("\tbufferCount - number of sound buffers to capture from each microphone to current directory");
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

			const string license = "VoiceExtractor";
			//const string license = "VoiceClient";
			//const string license = "VoiceFastExtractor";

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

				int bufferCount = int.Parse(args[0]);
				if (bufferCount == 0)
				{
					Console.WriteLine("No sound buffers will be captured as sound buffer count is not specified");
				}

				using (var deviceManager = new NDeviceManager { DeviceTypes = NDeviceType.Microphone, AutoPlug = true })
				{
					deviceManager.Initialize();
					Console.WriteLine("Device manager created. Found microphones: {0}", deviceManager.Devices.Count);

					foreach (NMicrophone microphone in deviceManager.Devices)
					{
						Console.Write("Found microphone {0}", microphone.DisplayName);

						microphone.StartCapturing();

						if (bufferCount > 0)
						{
							Console.WriteLine(", capturing");
							for (int i = 0; i < bufferCount; ++i)
							{
								using (NSoundBuffer soundSample = microphone.GetSoundSample())
								{
									Console.WriteLine("Sample buffer received. sample rate: {0}, sample length: {1}", soundSample.SampleRate, soundSample.Length);
								}
								Console.Write(" ... ");
							}
							Console.Write(" Done");
							Console.WriteLine();
						}
						microphone.StopCapturing();
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
