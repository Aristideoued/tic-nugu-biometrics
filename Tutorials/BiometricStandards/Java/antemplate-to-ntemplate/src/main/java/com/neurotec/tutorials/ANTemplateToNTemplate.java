package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.NTemplate;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateToNTemplate {

	private static final String DESCRIPTION = "ANTemplate to NTemplate conversion tutorial";
	private static final String NAME = "antemplate-to-ntemplate";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [ANTemplate] [NTemplate]%n", NAME);
		System.out.println("");
		System.out.println("\t[ATemplate] - filename of ANTemplate.");
		System.out.println("\t[NTemplate] - filename of NTemplate.");
		System.out.println("");
		System.out.println("examples:");
		System.out.format("\t%s antemplate.data nTemplate.data%n", NAME);
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 2) {
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

		ANTemplate anTemplate = null;
		NTemplate nTemplate = null;
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String aNTemplateFileName = args[0];

			// Creating ANTemplate object from file
			anTemplate = new ANTemplate(aNTemplateFileName);
			if (!anTemplate.isValidated()) {
				throw new Exception("ANSI/NIST template is not valid");
			}

			// Converting ANTemplate object to NTemplate object
			nTemplate = anTemplate.toNTemplate();

			// Packing NTemplate object
			NBuffer packedNTemplate = nTemplate.save();

			// Storing NTemplate object in file
			NFile.writeAllBytes(args[1], packedNTemplate);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (anTemplate != null)
				anTemplate.dispose();
			if (nTemplate != null)
				nTemplate.dispose();
		}
	}
}
