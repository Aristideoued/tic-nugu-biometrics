package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.ANImageASCIIBinaryRecord;
import com.neurotec.biometrics.standards.ANImageBinaryRecord;
import com.neurotec.biometrics.standards.ANRecord;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.images.NImage;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateToNImage {

	private static final String DESCRIPTION = "Demonstrates how to save images stored in ANTemplate";
	private static final String NAME = "antemplate-to-nimage";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [ANTemplate]%n", NAME);
		System.out.println("");
		System.out.println("\t[ATemplate] - filename of ANTemplate.");
		System.out.println("");
		System.out.println("examples:");
		System.out.format("\t%s antemplate.data%n", NAME);
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 1) {
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String[] licenses = { "FingerClient", "PalmClient", "FaceClient", "IrisClient" };
		//final String[] licenses = { "FingerFastExtractor", "PalmClient", "FaceFastExtractor", "IrisFastExtractor" };

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

			template = new ANTemplate(args[0]);
			if (!template.isValidated()) {
				throw new Exception("ANSI/NIST template is not valid");
			}
			for (int i = 0; i < template.getRecords().size(); i++) {
				ANRecord record = template.getRecords().get(i);
				NImage image = null;
				int number = record.getRecordType().getNumber();
				if (number >= 3 && number <= 8 && number != 7) {
					image = ((ANImageBinaryRecord)record).toNImage();
				} else if (number >= 10 && number <= 17) {
					image = ((ANImageASCIIBinaryRecord)record).toNImage();
				}

				if (image != null) {
					String fileName = String.format("record%d_type%d.jpg", i + 1, number);
					image.save(fileName);
					image.dispose();
					System.out.format("Image saved to %s%n", fileName);
				}
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (template != null) template.dispose();
				template.dispose();
		}
	}
}
