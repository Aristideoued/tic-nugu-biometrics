using System;
using Neurotec.Licensing;
using Neurotec.Media;
using Neurotec.Sound;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [source] [bufferCount] <optional: is url>", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			Console.WriteLine("\tsource - filename or url sound buffers should be captured from");
			Console.WriteLine("\tbufferCount - number of sound buffers to capture from specified filename or url");
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
			// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
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

				string uri = args[0];
				bool isUrl = false;
				int frameCount = int.Parse(args[1]);
				if (frameCount == 0)
				{
					Console.WriteLine("No frames will be captured as frame count is not specified");
				}

				if (args.Length > 2)
					isUrl = args[2] == "1";

				// create media source
				using (NMediaSource mediaSource = (isUrl) ? NMediaSource.FromUrl(uri) : NMediaSource.FromFile(uri))
				{
					Console.WriteLine("Display name: {0}", mediaSource.DisplayName);

					using (var mediaReader = new NMediaReader(mediaSource, NMediaType.Audio, true))
					{
						ReadSoundBuffers(mediaReader, frameCount);
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

		static void ReadSoundBuffers(NMediaReader mediaReader, int bufferCount)
		{
			NMediaSource mediaSource = mediaReader.Source;

			Console.WriteLine("Media length: {0}", mediaReader.Length);

			NMediaFormat[] mediaFormats = mediaSource.GetFormats(NMediaType.Audio);
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

			NMediaFormat currentMediaFormat = mediaSource.GetCurrentFormat(NMediaType.Audio);
			if (currentMediaFormat != null)
			{
				Console.WriteLine("Current media format:");
				DumpMediaFormat(currentMediaFormat);

				if (mediaFormats != null)
				{
					Console.WriteLine("Set the last supported format (optional) ... ");
					mediaSource.SetCurrentFormat(NMediaType.Audio, mediaFormats[mediaFormats.Length - 1]);
				}
			}
			else Console.WriteLine("Current media format is not yet available (will be available after media reader start)");

			Console.Write("Starting capture ... ");
			mediaReader.Start();
			Console.WriteLine("Capture started");

			try
			{
				currentMediaFormat = mediaSource.GetCurrentFormat(NMediaType.Audio);
				if (currentMediaFormat == null)
					throw new Exception("Current media format is not set even after media reader start!");
				Console.WriteLine("Capturing with format: ");
				DumpMediaFormat(currentMediaFormat);

				for (int i = 0; i < bufferCount; i++)
				{
					TimeSpan timeSpan, duration;

					using (NSoundBuffer buffer = mediaReader.ReadAudioSample(out timeSpan, out duration))
					{
						if (buffer == null) return; // end of stream

						Console.WriteLine("[{0} {1}] sample rate: {2}, sample length: {3}", timeSpan, duration, buffer.SampleRate, buffer.Length);
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
