using System;
using Neurotec.Images;
using Neurotec.Licensing;
using Neurotec.Media;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [source] [frameCount] <optional: is url>", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			Console.WriteLine("\tsource - filename or url frames should be captured from");
			Console.WriteLine("\tframeCount - number of sound buffers to capture from specified filename or url");
			Console.WriteLine("\tis url - specifies that passed source parameter is url (value: 1) or filename (value: 0)");
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

			const string license = "FaceExtractor";
			//const string license = "FaceClient";
			//const string license = "FaceFastExtractor";
			//const string license = "SentiVeillance";
			//const string license = "SentiMask";
			
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

				string uri = args[0];
				bool isUrl = false;
				int frameCount = int.Parse(args[1]);
				if (frameCount == 0)
				{
					Console.WriteLine("No frames will be captured as frame count is not specified");
				}

				if (args.Length > 2)
					isUrl = args[2] == "1";

				// Create media source
				using (NMediaSource mediaSource = (isUrl) ? NMediaSource.FromUrl(uri) : NMediaSource.FromFile(uri))
				{
					Console.WriteLine("Display name: {0}", mediaSource.DisplayName);

					using (var mediaReader = new NMediaReader(mediaSource, NMediaType.Video, true))
					{
						ReadFrames(mediaReader, frameCount);
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

		static void DumpMediaFormat(NMediaFormat mediaFormat)
		{
			if (mediaFormat == null) throw new ArgumentNullException("mediaFormat");

			switch (mediaFormat.MediaType)
			{
				case NMediaType.Video:
					var videoFormat = (NVideoFormat)mediaFormat;
					Console.WriteLine("Video format .. {0}x{1} @ {2}/{3} (interlace: {4}, aspect ratio: {5}/{6})", videoFormat.Width, videoFormat.Height,
						videoFormat.FrameRate.Numerator, videoFormat.FrameRate.Denominator, videoFormat.InterlaceMode, videoFormat.PixelAspectRatio.Numerator, videoFormat.PixelAspectRatio.Denominator);
					break;
				case NMediaType.Audio:
					var audioFormat = (NAudioFormat)mediaFormat;
					Console.WriteLine("Audio format .. channels: {0}, samples/second: {1}, bits/channel: {2}", audioFormat.ChannelCount,
										audioFormat.SampleRate, audioFormat.BitsPerChannel);
					break;
				default:
					throw new ArgumentException("Unknown media type specified in format!");
			}
		}

		static void ReadFrames(NMediaReader mediaReader, int frameCount)
		{
			NMediaSource mediaSource = mediaReader.Source;

			Console.WriteLine("Media length: {0}", mediaReader.Length);

			NMediaFormat[] mediaFormats = mediaSource.GetFormats(NMediaType.Video);
			if (mediaFormats == null)
			{
				Console.WriteLine("Formats are not yet available (should be available after media reader is started");
			}
			else
			{
				Console.WriteLine("Format count: {0}", mediaFormats.Length);
				for (int i = 0; i < mediaFormats.Length; i++)
				{
					Console.Write("[{0}] ", i);
					DumpMediaFormat(mediaFormats[i]);
				}
			}

			NMediaFormat currentMediaFormat = mediaSource.GetCurrentFormat(NMediaType.Video);
			if (currentMediaFormat != null)
			{
				Console.WriteLine("Current media format:");
				DumpMediaFormat(currentMediaFormat);

				if (mediaFormats != null)
				{
					Console.WriteLine("Set the last supported format (optional) ... ");
					mediaSource.SetCurrentFormat(NMediaType.Video, mediaFormats[mediaFormats.Length - 1]);
				}
			}
			else Console.WriteLine("Current media format is not yet available (will be available after media reader start)");

			Console.Write("Starting capture ... ");
			mediaReader.Start();
			Console.WriteLine("Capture started");

			try
			{
				currentMediaFormat = mediaSource.GetCurrentFormat(NMediaType.Video);
				if (currentMediaFormat == null)
					throw new Exception("Current media format is not set even after media reader start!");
				Console.WriteLine("Capturing with format: ");
				DumpMediaFormat(currentMediaFormat);

				for (int i = 0; i < frameCount; i++)
				{
					TimeSpan timeSpan, duration;

					using (NImage image = mediaReader.ReadVideoSample(out timeSpan, out duration))
					{
						if (image == null) return; // end of stream

						string filename = String.Format("{0:d4}.jpg", i);
						image.Save(filename);

						Console.WriteLine("[{0} {1}] {2}", timeSpan, duration, filename);
					}
				}
			}
			finally
			{
				mediaReader.Stop();
			}
		}
	}
}
