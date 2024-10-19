package com.neurotec.tutorials;

import com.neurotec.licensing.NLicense;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class IDGeneration {

	private static final String DESCRIPTION = "Demonstrates how to generate Id from serial number (either generated using LicenseManager API or given by Neurotechnology or distributor)";
	private static final String NAME = "id-generation";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [serial file name] [id file name]", NAME);
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
			// Load serial file (generated using LicenseManager API or provided
			// either by Neurotechnology or its distributor)
			String serial = Utils.readText(args[0]);

			// Either point to correct place for id_gen.exe, or pass NULL or use
			// method without idGenPath parameter in order to search id_gen.exe
			// in current folder.
			String id = NLicense.generateID(serial);

			// Write generated id to file.
			Utils.writeText(args[1], id);

			System.out.format("Id saved to file %s, it can now be activated using LicenseActivation tutorial, web page, etc.%n", args[1]);
		} catch (Throwable th) {
			Utils.handleError(th);
		}
	}

}
