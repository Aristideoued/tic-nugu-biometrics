package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FIRFingerView;
import com.neurotec.biometrics.standards.FIRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class FIRecordToNTemplate {
	private static final String DESCRIPTION = "Convert FIRecord to NTemplate tutorial";
	private static final String NAME = "firecord-to-ntemplate";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.format("usage: %s [FIRecord] [standard] [Encoding] [NTemplate]%n", NAME);
		System.out.println("\t[FIRecord]  - input FIRecord");
		System.out.println("\t[Standard] - FIRecord standard (ISO or ANSI)");
		System.out.println("\t[NTemplate] - output NTemplate");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 3) {
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "FingerClient";
		//final String license = "FingerFastExtractor";

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

		FIRecord fiRec = null;
		NBiometricClient biometricClient = null;
		NSubject subject = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();

			// Read FIRecord from file
			NBuffer fiRecordData = NFile.readAllBytes(args[0]);
			BDIFStandard standard = BDIFStandard.valueOf(args[1]);
			
			// Create FIRecord
			fiRec = new FIRecord(fiRecordData, standard);

			// Read all images from FIRecord
			for (FIRFingerView fv : fiRec.getFingerViews()) {
				NFinger finger = new NFinger();
				finger.setImage(fv.toNImage());
				subject.getFingers().add(finger);
			}

			// Set finger template size (large is recommended for enrolment to database) (optional)
			biometricClient.setFingersTemplateSize(NTemplateSize.LARGE);

			// Create template from added finger image(s)
			NBiometricStatus status = biometricClient.createTemplate(subject);

			System.out.println(status == NBiometricStatus.OK
					? "Template extracted"
					: String.format("Extraction failed: %s", status));

			if (status == NBiometricStatus.OK) {
				NFile.writeAllBytes(args[2], subject.getTemplateBuffer());
				System.out.println("NTemplate saved to file " + args[2]);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (fiRec != null) fiRec.dispose();
			if (biometricClient != null) biometricClient.dispose();
			if (subject != null) subject.dispose();
		}
	}
}
