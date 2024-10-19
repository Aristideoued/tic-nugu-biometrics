package com.neurotec.tutorials.biometrics;

import java.io.IOException;

import com.neurotec.biometrics.NETemplate;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public class CreateTwoIrisTemplate {

	private static final String DESCRIPTION = "Demonstrates how to create two eye NTemplate";
	private static final String NAME = "create-two-iris-template";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [left eye record] [right eye record] [template]%n", NAME);
		System.out.println();
		System.out.println("\t[left eye record]  - filename of left eye record.");
		System.out.println("\t[right eye record] - filename of right eye record.");
		System.out.println("\t[template]        - filename for template.");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 3) {
			usage();
			System.exit(1);
		}

		NTemplate nTemplate = new NTemplate();
		// Create NTemplate
		NTemplate outputTemplate = new NTemplate();
		// Create NETemplate
		NETemplate outputIrisesTemplate = new NETemplate();
		// Set NETemplate to NTemplate
		outputTemplate.setIrises(outputIrisesTemplate);

		NETemplate irisesTemplate = new NETemplate();
		nTemplate.setIrises(irisesTemplate);

		try {
			for (int i = 0; i < (args.length - 1); i++)
			{
				// Read NTemplate/NETemplate/NERecord from input file
				NTemplate newTemplate = new NTemplate(NFile.readAllBytes(args[i]));
				NETemplate irisTemplate = newTemplate.getIrises();

				// Retrieve NETemplate from NTemplate
				NETemplate inputIrisesTemplate = nTemplate.getIrises();

				// Add NERecord to output NETemplate
				try {
					outputIrisesTemplate.getRecords().addAll(irisTemplate.getRecords());
				} finally {
					if (newTemplate != null) newTemplate.dispose();
					if (irisTemplate != null) irisTemplate.dispose();
					if (inputIrisesTemplate != null) inputIrisesTemplate.dispose();
				}
			}

			// Save compressed template to file
			NFile.writeAllBytes(args[2], outputIrisesTemplate.save());
			System.out.format("Template successfully saved to file: %s%n", args[2]);

		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (nTemplate != null) nTemplate.dispose();
			if (outputTemplate != null) outputTemplate.dispose();
			if (outputIrisesTemplate != null) outputIrisesTemplate.dispose();
			if (irisesTemplate != null) irisesTemplate.dispose();
		}
	}
}
