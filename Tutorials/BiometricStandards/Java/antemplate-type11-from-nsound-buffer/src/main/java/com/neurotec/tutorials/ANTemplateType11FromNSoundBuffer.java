package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.ANAcquisitionSource;
import com.neurotec.biometrics.standards.ANAcquisitionSourceType;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType11Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.sound.NSoundBuffer;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateType11FromNSoundBuffer 
{
	private static final String DESCRIPTION = "Demonstrates creation of ANTemplate with type 11 record in it.";
	private static final String NAME = "antemplate-type11-from-nsound-buffer";
	private static final String VERSION = "13.1.0.0";

	private static void usage() 
	{
		System.out.println("usage:");
		System.out.format("\t%s [NSoundBuffer] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Src] [Encoding]%n", NAME);
		System.out.println("");
		System.out.println("\t[NSoundBuffer] - filename with sound buffer file.");
		System.out.println("\t[ANTemplate] - filename for ANTemplate.");
		System.out.println("\t[Tot] - specifies type of transaction.");
		System.out.println("\t[Dai] - specifies destination agency identifier.");
		System.out.println("\t[Ori] - specifies originating agency identifier.");
		System.out.println("\t[Tcn] - specifies transaction control number.");
		System.out.println("\t[Src] - specifies source agency number.");
		System.out.println("\t[Encoding] - specifies ANTemplate encoding type.");
		System.out.println("\t\t0 - Traditional binary encoding.");
		System.out.println("\t\t1 - NIEM-conformant XML encoding.");
		System.out.println("");
	}

	public static void main(String[] args)
	{
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 8)
		{
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "VoiceClient";

		//=========================================================================

		//=========================================================================
		// TRIAL MODE
		//=========================================================================
		// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
		// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
		// Also you can just set TRUE to "TrialMode" property in code.
		//=========================================================================

		try
		{
			boolean trialMode = Utils.getTrialModeFlag();
			NLicenseManager.setTrialMode(trialMode);
			System.out.println("\tTrial mode: " + trialMode);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

		try
		{
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license))
			{
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String tot = args[2]; 	// type of transaction
			String dai = args[3]; 	// destination agency identifier
			String ori = args[4]; 	// originating agency identifier
			String tcn = args[5]; 	// transaction control number
			String src = args[6]; 	// source agency number
			String enc = args[7];	// encoding type

			if ((tot.length() < 3) || (tot.length() > 4))
			{
				System.out.println("Tot parameter should be 3 or 4 characters length.");
				System.exit(-1);
			}

			BDIFEncodingType encoding = enc.equals("1") ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;

			// Create empty ANTemplate object with current version and only type 1 record in it.
			// Creates Type 11 record and adds record to ANTemplate object.
			try (ANTemplate template = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, 0))
			{
				try (NSoundBuffer soundBuffer = NSoundBuffer.fromFile(args[0]))
				{
					// Sample acquisition source (11.008), which is mandatory when record has associated voice data. Must be updated with actual data.
					ANAcquisitionSource acqSource = new ANAcquisitionSource(ANAcquisitionSourceType.DIGITAL_AUDIO_RECORDING_DEVICE, null, null, null);

					// Create Type 11 record and add record to ANTemplate
					ANType11Record record = template.getRecords().addType11(src, acqSource, soundBuffer);

					// XML encoding is not supported currently
					if (encoding != BDIFEncodingType.TRADITIONAL) {
						throw new IllegalStateException("Currently only traditional encoding is supported for voice record");
					}

					// Storing ANTemplate object in file
					template.save(args[1], encoding);
				}
				catch (Throwable th)
				{
					Utils.handleError(th);
				}
			}
			catch (Throwable th)
			{
				Utils.handleError(th);
			}
		}
		catch (Throwable th)
		{
			Utils.handleError(th);
		}
	}
}
