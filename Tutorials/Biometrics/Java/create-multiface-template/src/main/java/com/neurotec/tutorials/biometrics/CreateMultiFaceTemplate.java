package com.neurotec.tutorials.biometrics;

import com.neurotec.biometrics.NLRecord;
import com.neurotec.biometrics.NLTemplate;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

import java.io.IOException;

public final class CreateMultiFaceTemplate {

	private static final String DESCRIPTION = "Demonstrates creation of NTemplate containing multiple face templates";
	private static final String NAME = "create-multiface-template";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("%s [one or more templates] [output NTemplate]%n", NAME);
		System.out.println();
		System.out.println("\tone or more NLTemplates  - one or more files containing face templates.");
		System.out.println("\toutput NTemplate         - output NTemplate file.");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 2) {
			usage();
			System.exit(1);
		}

		NLTemplate nlTemplate = null;
		
		try {
			nlTemplate = new NLTemplate();

			// Read all input NTemplates and fill output faces template
			for (int i = 0; i < args.length - 1; i++) {
				System.out.println("reading " + args[i]);
				NTemplate template = new NTemplate(NFile.readAllBytes(args[i]));
				if (template.getFaces() != null) {
					for (NLRecord record : template.getFaces().getRecords()) {
						nlTemplate.getRecords().add(record);
					}
				}
				template.dispose();
			}

			if (nlTemplate.getRecords().size() == 0) {
				System.err.println("Not writing template file because no records found");
				System.exit(-1);
			}

			System.out.println(nlTemplate.getRecords().size() + " records found");

			// Write output file
			NFile.writeAllBytes(args[args.length - 1], nlTemplate.save());
			System.out.format("Template successfully written to %s%n", args[args.length - 1]);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (nlTemplate != null) nlTemplate.dispose();
		}
	}
}
