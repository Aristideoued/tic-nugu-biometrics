using System;
using Neurotec.Biometrics.Standards;
using Neurotec.Images;
using Neurotec.Licensing;
using Neurotec.IO;

namespace Neurotec.Tutorials
{
	class Program
	{
		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [ANTemplate] [Encoding] [Finger NImage] [Face NImage] [Iris NImage]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("");
			Console.WriteLine("\t[ANTemplate] - filename for ANTemplate.");
			Console.WriteLine("\t[Encoding] - specifies ANTemplate encoding type.");
			Console.WriteLine("\t\t0 - Traditional binary encoding.");
			Console.WriteLine("\t\t1 - NIEM-conformant XML encoding.");
			Console.WriteLine("\t[Finger NImage]  - filename with finger image file.");
			Console.WriteLine("\t[Face NImage]    - filename with face image file (optional).");
			Console.WriteLine("\t[Iris NImage]    - filename with finger image file (optional).");
			Console.WriteLine("");

			return 1;
		}

		private static void ANTemplateGetRecordType2(ANTemplate antemplate, BdifEncodingType encoding)
		{
			int nameFieldNumber = 18;
			int placeOfBirthFieldNumber = 20;
			int dateOfBirthFieldNumber = 22;
			int genderFieldNumber = 24;

			try
			{
				ANType2Record record = antemplate.Records.AddType2();

				// Adds fields for "traditional" binary encoding
				if (encoding == BdifEncodingType.Traditional)
				{
					record.Fields.Add(nameFieldNumber, "name, surname");
					record.Fields.Add(placeOfBirthFieldNumber, "UK");
					record.Fields.Add(dateOfBirthFieldNumber, "19700131");
					record.Fields.Add(genderFieldNumber, "M");
				}
				else // Adds fields for NIEM-conformant XML encoding
				{
					record.Fields.Add(nameFieldNumber, "PersonName", "name, surname");
					record.Fields.Add(placeOfBirthFieldNumber, "PersonBirthPlaceCode", "UK");
					record.Fields.Add(dateOfBirthFieldNumber, "PersonBirthDate", "19700131");
					record.Fields.Add(genderFieldNumber, "PersonSexCode", "M");
				}
			}
			catch(Exception)
			{
				throw;
			}
		}

		private static void ANTemplateGetRecordType10(ANTemplate antemplate, string fileNameIn, string src)
		{
			try
			{
				/**
				 * Image must be compressed using valid compression algorithm for Type-10 record.
				 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
				*/
				using (var imageBuffer = NFile.ReadAllBytes(fileNameIn))
				{
					ANImageType imt = ANImageType.Face;
					ANType10Record record = antemplate.Records.AddType10(imt, src, imageBuffer);
				}
			}
			catch(Exception)
			{
				throw;
			}
		}

		private static void ANTemplateGetRecordType14(ANTemplate antemplate, string fileNameIn, string src)
		{
			try
			{
				/**
				 * Finger image must be compressed using valid compression algorithm for Type-14 record.
				 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
				*/
				using (var imageBuffer = NFile.ReadAllBytes(fileNameIn))
				{
					ANType14Record record = antemplate.Records.AddType14(src, imageBuffer);
				}
			}
			catch(Exception)
			{
				throw;
			}
		}

		private static void ANTemplateGetRecordType17(ANTemplate antemplate, string fileNameIn, string src)
		{
			try
			{
				/**
				 * Image must be compressed using valid compression algorithm for Type-17 record.
				 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
				*/
				using (var imageBuffer = NFile.ReadAllBytes(fileNameIn))
				{
					ANType17Record record = antemplate.Records.AddType17(src, imageBuffer);
				}
			}
			catch(Exception)
			{
				throw;
			}
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 3)
			{
				return Usage();
			}

			//=========================================================================
			// CHOOSE LICENCES !!!
			//=========================================================================
			// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
			// If you are using a TRIAL version - choose any of them.

			const string licenses = "FingerClient,FaceClient,IrisClient";
			//const string licenses = "FingerFastExtractor,FaceFastExtractor,IrisFastExtractor";

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

            string fileNameOut = args[0];
			BdifEncodingType encoding = (args[1] == "1") ? BdifEncodingType.Xml : BdifEncodingType.Traditional;
			string fingerFileNameIn = args[2];
			string faceFileNameIn = args.Length > 3 ? args[3] : "";
			string irisFileNameIn = args.Length > 4 ? args[4] : "";

			try
			{
				// Obtain license
				if (!NLicense.Obtain("/local", 5000, licenses))
				{
					throw new NotActivatedException(string.Format("Could not obtain licenses: {0}", licenses));
				}

				string tot = "TransactionType";
				string dai = "DestinationAgencyId";
				string ori = "OriginatingAgencyId";
				string tcn = "Transaction1";
				string src = "SourceAgencyName";
				NVersion version = ANTemplate.VersionCurrent;

				using (ANTemplate antemplate = new ANTemplate(version, tot, dai, ori, tcn, 0))
				{
					ANTemplateGetRecordType2(antemplate, encoding);

					ANTemplateGetRecordType14(antemplate, fingerFileNameIn, src);
					if (faceFileNameIn.Length > 0) ANTemplateGetRecordType10(antemplate, faceFileNameIn, src);
					if (irisFileNameIn.Length > 0) ANTemplateGetRecordType17(antemplate, irisFileNameIn, src);

					antemplate.Save(fileNameOut, encoding);
					Console.WriteLine("Template saved to {0}", fileNameOut);
					return 0;
				}
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
