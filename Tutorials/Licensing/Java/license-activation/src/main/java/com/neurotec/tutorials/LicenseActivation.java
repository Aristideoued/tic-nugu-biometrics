package com.neurotec.tutorials;

import com.neurotec.licensing.NLicense;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class LicenseActivation {

	private static final String DESCRIPTION = "Demonstrates license activation online using generated diagnostics Id";
	private static final String NAME = "license-activation";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [id file name] [lic file name]", NAME);
		System.out.println();

	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 2) {
			usage();
			System.exit(-1);
		}

		try {
			// Load id file (it can be generated using IdGeneration tutorial or ActivationWizardDotNet)
			String id = Utils.readText(args[0]);

			// Generate license for specified id.
			String license = NLicense.activateOnline(id);

			// Write license to file.
			Utils.writeText(args[1], license);

			System.out.format("License saved to file %s.%n", args[1]);
		} catch (Throwable th) {
			Utils.handleError(th);
		}
	}

}
