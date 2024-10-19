package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType1Record;
import com.neurotec.biometrics.standards.ANType4Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateType4FromNImage {

	private static final String DESCRIPTION = "Demonstrates creation of ANTemplate with type 4 record in it.";
	private static final String NAME = "antemplate-type4-from-nimage";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [Image] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]%n", NAME);
		System.out.println("");
		System.out.println("\t[Image]     - filename with image file.");
		System.out.println("\t[ANTemplate] - filename for ANTemplate.");
		System.out.println("\t[Tot] - specifies type of transaction.");
		System.out.println("\t[Dai] - specifies destination agency identifier.");
		System.out.println("\t[Ori] - specifies originating agency identifier.");
		System.out.println("\t[Tcn] - specifies transaction control number.");
		System.out.println("\t[Encoding] - specifies ANTemplate encoding type.");
		System.out.println("\t\t0 - Traditional binary encoding.");
		System.out.println("\t\t1 - NIEM-conformant XML encoding.");
		System.out.println("");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 7) {
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "FingerClient";
		//final String license = "FingerFastExtractor";

		//=========================================================================

		//=========================================================================
		// TRIAL MODE
		//=========================================================================
		// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
		// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
		// Also you can just set TRUE to "TrialMode" property in code.
		//=========================================================================

		try {
			boolean trialMode = Utils.getTrialModeFlag();
			NLicenseManager.setTrialMode(trialMode);
			System.out.println("\tTrial mode: " + trialMode);
		} catch (IOException e) {
			e.printStackTrace();
		}

		ANTemplate template = null;
		ANType4Record record = null;
		NBuffer imgBuffer = null;
		int imageScanningResolution = ANType1Record.MIN_SCANNING_RESOLUTION; // image scanning resolution
		int imageResolutionPpi = 500; // image current resolution

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String tot = args[2]; // type of transaction
			String dai = args[3]; // destination agency identifier
			String ori = args[4]; // originating agency identifier
			String tcn = args[5]; // transaction control number
			String enc = args[6]; // encoding type

			if ((tot.length() < 3) || (tot.length() > 4)) {
				System.out.println("Tot parameter should be 3 or 4 characters length.");
				System.exit(-1);
			}

			BDIFEncodingType encoding = enc.equals("1") ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;
			imgBuffer = NFile.readAllBytes(args[0]);

			/* 
			 * Create empty ANTemplate object with current version and only type 1 record in it.
			 * Finger image must be compressed using valid compression algorithm for Type-4 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			*/
			template = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, 0);

			// Create Type 4 record and add record to ANTemplate
			record = template.getRecords().addType4(true, imgBuffer);

			ANType1Record type1 = (ANType1Record)template.getRecords().get(0);
			type1.setNativeScanningResolution(imageScanningResolution);
			type1.setNominalTransmittingResolutionPpi(imageResolutionPpi);

			// Store ANTemplate object with type 4 record in file
			template.save(args[1], encoding);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (record != null) record.dispose();
			if (template != null) template.dispose();
			if (imgBuffer != null) imgBuffer.dispose();
		}
	}
}
