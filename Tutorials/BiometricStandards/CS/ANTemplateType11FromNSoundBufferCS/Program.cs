using System;
using Neurotec.Biometrics.Standards;
using Neurotec.Licensing;
using Neurotec.IO;
using Neurotec.Sound;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [NSoundBuffer] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Src] [Encoding]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[NSoundBuffer] - filename with sound buffer file.");
			Console.WriteLine("\t[ANTemplate] - filename for ANTemplate.");
			Console.WriteLine("\t[Tot] - specifies type of transaction.");
			Console.WriteLine("\t[Dai] - specifies destination agency identifier.");
			Console.WriteLine("\t[Ori] - specifies originating agency identifier.");
			Console.WriteLine("\t[Tcn] - specifies transaction control number.");
			Console.WriteLine("\t[Src] - specifies source agency number.");
            Console.WriteLine("\t[Encoding] - specifies ANTemplate encoding type.");
            Console.WriteLine("\t\t0 - Traditional binary encoding.");
            Console.WriteLine("\t\t1 - NIEM-conformant XML encoding.");
            Console.WriteLine("");

			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length != 8)
			{
				return Usage();
			}

			//=========================================================================
			// CHOOSE LICENCES !!!
			//=========================================================================
			// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
			// If you are using a TRIAL version - choose any of them.

			const string license = "VoiceClient";

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

				string tot = args[2]; // type of transaction
				string dai = args[3]; // destination agency identifier
				string ori = args[4]; // originating agency identifier
				string tcn = args[5]; // transaction control number
				string src = args[6]; // source agency number
				string enc = args[7]; // encoding type

				if ((tot.Length < 3) || (tot.Length > 4))
				{
					Console.WriteLine("Tot parameter should be 3 or 4 characters length.");
					return -1;
				}

				BdifEncodingType encoding = (enc == "1") ? BdifEncodingType.Xml : BdifEncodingType.Traditional;

				/**
				 * Create empty ANTemplate object with current version and only type 1 record in it.
				 * Creates Type 11 record and adds record to ANTemplate object.
				*/
				using (var template = new ANTemplate(ANTemplate.VersionCurrent, tot, dai, ori, tcn, 0))
				using (var soundBuffer = NSoundBuffer.FromFile(args[0]))
				{
					// Sample acquisition source (11.008), which is mandatory when record has associated voice data. Must be updated with actual data.
					ANAcquisitionSource acqSource = new ANAcquisitionSource(ANAcquisitionSourceType.DigitalAudioRecordingDevice, null, null, null);

					// Create Type 11 record and add record to ANTemplate
					ANType11Record record = template.Records.AddType11(src, acqSource, soundBuffer);

					// XML encoding is not supported currently
					if (encoding != BdifEncodingType.Traditional)
					{
						throw new InvalidOperationException("Currently only traditional encoding is supported for voice record");
					}

					// Storing ANTemplate object in file
					template.Save(args[1], encoding);
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
