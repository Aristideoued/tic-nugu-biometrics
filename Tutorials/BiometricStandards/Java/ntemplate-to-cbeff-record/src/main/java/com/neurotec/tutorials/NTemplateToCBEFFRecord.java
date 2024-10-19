package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.BDIFTypes;
import com.neurotec.biometrics.standards.CBEFFBDBFormatIdentifiers;
import com.neurotec.biometrics.standards.CBEFFBiometricOrganizations;
import com.neurotec.biometrics.standards.CBEFFRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public class NTemplateToCBEFFRecord {

	private static final String DESCRIPTION = "Converting CbeffRecord to NTemplate";
	private static final String NAME = "ntemplate-to-cbeff-record";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [NTemplate] [CbeffRecord] [PatronFormat]", NAME);
		System.out.println();
		System.out.println("\t[NTemplate] - filename of NTemplate.");
		System.out.println("\t[CbeffRecord] - filename of CbeffRecord.");
		System.out.println("\t[PatronFormat] - number identifying patron format (all supported values can be found in CbeffRecord class documentation).");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 3) {
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

		CBEFFRecord cbeffRecord = null;
		NBuffer packedNTemplate = null;
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

			// Read NTemplate buffer
			packedNTemplate = NFile.readAllBytes(args[0]);

			// Combine NTemplate BDB format
			int bdbFormat = BDIFTypes.makeFormat(CBEFFBiometricOrganizations.NEUROTECHNOLOGIJA, CBEFFBDBFormatIdentifiers.NEUROTECHNOLOGIJA_NTEMPLATE);

			// Get CbeffRecord patron format
			// all supported patron formats can be found in CbeffRecord class documentation
			int patronFormat = Integer.parseInt(args[2], 16);

			// Create CbeffRecord from NTemplate buffer
			cbeffRecord = new CBEFFRecord(bdbFormat, packedNTemplate, patronFormat);

			NFile.writeAllBytes(args[1], cbeffRecord.save());
			System.out.println("Template successfully saved");
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (packedNTemplate != null) packedNTemplate.dispose();
			if (cbeffRecord != null) cbeffRecord.dispose();
		}
	}
}
