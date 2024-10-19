package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType2Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateType2Record {

	private static final String DESCRIPTION = "Demonstrates creation of ANTemplate with user-defined type 2 record in it.";
	private static final String NAME = "antemplate-type2-record";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]%n", NAME);
		System.out.println("");
		System.out.println("\t[ANTemplate] - filename for ANTemplate.");
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

		if (args.length != 6) {
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String[] licenses = { "FingerMatcher", "FaceMatcher", "IrisMatcher", "PalmMatcher", "VoiceMatcher" };
		//final String[] licenses = { "FingerFastMatcher", "FaceFastMatcher", "IrisFastMatcher", "PalmFastMatcher", "VoiceFastMatcher" };

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
		ANType2Record record = null;

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

			String tot = args[1]; // type of transaction
			String dai = args[2]; // destination agency identifier
			String ori = args[3]; // originating agency identifier
			String tcn = args[4]; // transaction control number
			String enc = args[5]; // encoding type

			if ((tot.length() < 3) || (tot.length() > 4)) {
				System.out.println("Tot parameter should be 3 or 4 characters length.");
				System.exit(-1);
			}

			BDIFEncodingType encoding = enc.equals("1") ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;

			int nameFieldNumber = 18;// exemplary field number for subject's name and surname
			String nameFieldValue = "name, surname"; // exemplary subject's name and surname
			int placeOfBirthFieldNumber = 20;// exemplary field number for subject's place of birth
			String placeOfBirthFieldValue = "UK"; // exemplary subject's place of birth
			int dateOfBirthFieldNumber = 22;// exemplary field number for subject's date of birth
			String dateOfBirthFieldValue = "19700131"; // exemplary subject's date of birth
			int genderFieldNumber = 24;// exemplary field number for subject's gender
			String genderFieldValue = "M";// exemplary subject's gender

			// Create empty ANTemplate object with current version and only type 1 record in it.
			template = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, 0);

			// Create Type 2 record and add record to ANTemplate
			record = template.getRecords().addType2();
			
			// Adds fields for "traditional" binary encoding
			if (encoding == BDIFEncodingType.TRADITIONAL) {
				record.getFields().add(nameFieldNumber, nameFieldValue);
				record.getFields().add(placeOfBirthFieldNumber, placeOfBirthFieldValue);
				record.getFields().add(dateOfBirthFieldNumber, dateOfBirthFieldValue);
				record.getFields().add(genderFieldNumber, genderFieldValue);
			} else { // Adds fields for NIEM-conformant XML encoding
				record.getFields().add(nameFieldNumber, "PersonName", nameFieldValue);
				record.getFields().add(placeOfBirthFieldNumber, "PersonBirthPlaceCode", placeOfBirthFieldValue);
				record.getFields().add(dateOfBirthFieldNumber, "PersonBirthDate", dateOfBirthFieldValue);
				record.getFields().add(genderFieldNumber, "PersonSexCode", genderFieldValue);
			}
			// Store ANTemplate object with type 2 record in file
			template.save(args[0], encoding);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (record != null) record.dispose();
			if (template != null) template.dispose();
		}
	}

}
