package com.neurotec.tutorials.biometrics;

import com.neurotec.biometrics.NFRecord;
import com.neurotec.biometrics.NFTemplate;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

import java.io.IOException;

public final class CreateMultiFingerTemplate {

	private static final String DESCRIPTION = "Demonstrates creation of NTemplate containing multiple fingerprint templates.";
	private static final String NAME = "create-multifinger-template";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [templates ...] [NTemplate]%n", NAME);
		System.out.println();
		System.out.println("\t[templates] - one or more files containing fingerprint templates.");
		System.out.println("\t[NTemplate] - filename of output file where NTemplate is saved.");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if ((args.length < 2) || ("/?".equals(args[0])) || ("--help".equals(args[0]))) {
			usage();
			System.exit(1);
		}

		NFTemplate nfTemplate = null;
		
		try {
			nfTemplate = new NFTemplate();

			// Read all input NTemplates and fill output fingers template
			for (int i = 0; i < args.length - 1; i++) {
				NTemplate template = new NTemplate(NFile.readAllBytes(args[i]));
				if (template.getFingers() != null) {
					for (NFRecord record : template.getFingers().getRecords()) {
						nfTemplate.getRecords().add(record);
					}
				}
				template.dispose();
			}

			if (nfTemplate.getRecords().size() == 0) {
				System.err.println("Not writing template file because no records found");
				System.exit(-1);
			}

			System.out.println(nfTemplate.getRecords().size() + " records found");

			// Write output file
			NFile.writeAllBytes(args[args.length - 1], nfTemplate.save());
			System.out.format("Template successfully written to %s%n", args[args.length - 1]);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (nfTemplate != null) nfTemplate.dispose();
		}
	}
}
