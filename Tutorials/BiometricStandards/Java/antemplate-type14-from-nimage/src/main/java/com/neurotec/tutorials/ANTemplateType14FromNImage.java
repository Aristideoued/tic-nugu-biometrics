package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType14Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateType14FromNImage {

	private static final String DESCRIPTION = "Demonstrates creation of ANTemplate with type 14 record in it";
	private static final String NAME = "antemplate-type14-from-nimage";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [Image] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Src] [Encoding]%n", NAME);
		System.out.println("");
		System.out.println("\t[Image]     - filename with Image file.");
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

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 8) {
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
		ANType14Record record = null;
		NBuffer imgBuffer = null;

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
			String src = args[6]; // source agency number
			String enc = args[7]; // encoding type

			if ((tot.length() < 3) || (tot.length() > 4)) {
				System.out.println("Tot parameter should be 3 or 4 characters length.");
				System.exit(-1);
			}
			
			BDIFEncodingType encoding = enc.equals("1") ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;
			imgBuffer = NFile.readAllBytes(args[0]);

			/* 
			 * Create empty ANTemplate object with current version and only type 1 record in it.
			 * Finger image must be compressed using valid compression algorithm for Type-14 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			*/
			template = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, 0);

			// Create Type 14 record and add record to ANTemplate
			record = template.getRecords().addType14(src, imgBuffer);

			// Store ANTemplate object with type 14 record in file
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
