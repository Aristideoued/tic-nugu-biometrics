package com.neurotec.tutorials;

import com.neurotec.licensing.NLicense;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

import java.util.Scanner;

public final class LicenseDeactivation {

	private static final String DESCRIPTION = "Demonstrates license deactivation";
	private static final String NAME = "license-deactivation";
	private static final String VERSION = "6.0.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [lic file name] (optional: [deactivation id file name])", NAME);
		System.out.println("NOTE: Please always deactivate license on the same computer it was activated on!");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 1) {
			usage();
			System.exit(-1);
		}

		try {
			// Load license file.
			String license = Utils.readText(args[0]);

			// First check our intentions.
			System.out.println("WARNING: deactivating a license will make it and product(for which it was generated) disabled on current pc. Continue? (y/n)");
			Scanner scanner = new Scanner(System.in);
			try {
				if (!"y".equals(scanner.nextLine())) {
					System.out.println("Not generating.");
					return;
				}
			} finally {
				scanner.close();
			}

			try {
				// Either point to correct place for id_gen.exe, or pass NULL or use
				// method without idGenPath parameter in order to search id_gen.exe
				// in current folder.

				// Do the deactivation.
				NLicense.deactivateOnline(license);

				System.out.println("Online deactivation succeeded. You can now use serial number again.");
			} catch (Exception e) {
				System.out.format("Online deactivation failed. Reason: %s%n", e.getMessage());
				System.out.println("Generating deactivation id, which you can send to support@neurotechnology.com for manual deactivation.");

				if (args.length != 2) {
					System.out.println("Missing deactivation id argument, please specify it.");
					usage();
					System.exit(-1);
				}

				String id = NLicense.generateDeactivationIDForLicense(license);

				// Write generated deactivation id to file.
				Utils.writeText(args[1], id);

				System.out.format("Deactivation id saved to file %s. Please send it to support@neurotechnology.com to complete deactivation process.", args[1]);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		}
	}

}
