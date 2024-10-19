package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.NTemplate;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class NTemplateToANTemplate {

	private static final String DESCRIPTION = "Converting NTemplate to ANTemplate";
	private static final String NAME = "ntemplate-to-antemplate";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [NTemplate] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]%n", NAME);
		System.out.println("");
		System.out.println("\t[NTemplate]     - filename of NTemplate.");
		System.out.println("\t[ANTemplate]    - filename of ANTemplate.");
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

		if (args.length < 7) {
			usage();
			System.exit(1);
		}

		if (args[0] == "/?" || args[0] == "help") {
			usage();
			System.exit(-1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String[] licenses = { "FingerClient", "PalmClient" };
		//final String[] licenses = { "FingerFastExtractor", "PalmClient" };

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

		NTemplate nTemplate = null;
		ANTemplate anTemplate = null;

		boolean anyMatchingComponent = false;
		try {
			// Obtain licenses
			for (String license : licenses) {
				if (NLicense.obtain("/local", 5000, license)) {
					System.out.format("Obtained license: %s%n", license);
					anyMatchingComponent = true;
				}
			}
			if (!anyMatchingComponent) {
				System.err.println("Could not obtain any matching license");
				System.exit(-1);
			}

			String nTemplateFileName = args[0];

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

			NBuffer packedNTemplate = NFile.readAllBytes(nTemplateFileName);

			// Creating NTemplate object from packed NTemplate
			nTemplate = new NTemplate(packedNTemplate);

			//sets minutia format: true - if standard, false - otherwise. For palms only standard minutia format is supported
			boolean type9RecordFmtStd = nTemplate.getPalms() != null && !nTemplate.getPalms().getRecords().isEmpty() ? true : false;

			// Creating ANTemplate object from NTemplate object
			anTemplate = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, type9RecordFmtStd, nTemplate);

			// Storing ANTemplate object in file
			anTemplate.save(args[1], encoding);
			System.out.println("Program produced file: " + args[1]);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (nTemplate != null) nTemplate.dispose();
			if (anTemplate != null) anTemplate.dispose();
		}
	}
}
