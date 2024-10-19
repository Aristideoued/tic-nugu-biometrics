package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFImpressionType;
import com.neurotec.biometrics.NFPosition;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType9Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateType9FromNImage {

	private static final String DESCRIPTION = "Demonstrates creation of ANTemplate with type 9 record in it.";
	private static final String NAME = "antemplate-type9-from-nimage";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [NImage] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [FmtFlag] [Encoding]%n", NAME);
		System.out.println("");
		System.out.println("\t[NImage]     - filename with image file.");
		System.out.println("\t[ANTemplate] - filename for ANTemplate.");
		System.out.println("\t[Tot] - specifies type of transaction.");
		System.out.println("\t[Dai] - specifies destination agency identifier.");
		System.out.println("\t[Ori] - specifies originating agency identifier.");
		System.out.println("\t[Tcn] - specifies transaction control number.");
		System.out.println("\t[FmtFlag] - specifies finger minutiae format. 1 if minutiae are saved in standard way (used until version 4.0), 0 - if in vendor specific 'INCITS 378' block (recomended from version 5.0).");
		System.out.println("\t[Encoding] - specifies ANTemplate encoding type.");
		System.out.println("\t\t0 - Traditional binary encoding.");
		System.out.println("\t\t1 - NIEM-conformant XML encoding.");
		System.out.println("");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 8) {
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

		ANTemplate template = null;
		ANType9Record record = null;
		NBiometricClient biometricClient = null;
		NSubject subject = null;
		NFinger finger = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String tot = args[2]; // type of transaction
			String dai = args[3]; // destination agency identifier
			String ori = args[4]; // originating agency identifier
			String tcn = args[5]; // transaction control number
			String fmt = args[6]; // minutiae format
			String enc = args[7]; // encoding type
			Boolean fmtBool = fmt.equals("1") ? true : false;
			NFPosition position = NFPosition.RIGHT_THUMB;

			if ((tot.length() < 3) || (tot.length() > 4)) {
				System.out.println("Tot parameter should be 3 or 4 characters length.");
				System.exit(-1);
			}

			BDIFEncodingType encoding = enc.equals("1") ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			finger = new NFinger();

			finger.setFileName(args[0]);
			finger.setPosition(position);
			finger.setImpressionType(NFImpressionType.LIVE_SCAN_PLAIN);
			subject.getFingers().add(finger);

			biometricClient.createTemplate(subject);

			if (subject.getStatus() == NBiometricStatus.OK) {
							/* 
							* Create empty ANTemplate object with current version and only type 1 record in it.
							* Finger image must be compressed using valid compression algorithm for Type-9 record.
							* How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
							*/
				template = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn);

				// Add Type 9 record to ANTemplate object
				record = template.getRecords().addType9(fmtBool, subject.getTemplate().getFingers().getRecords().get(0));

				// Store ANTemplate object with type 9 record in file
				template.save(args[1], encoding);
			} else {
				System.out.println("Fingerprint extraction failed");
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (record != null) record.dispose();
			if (template != null) template.dispose();
			if (biometricClient != null) biometricClient.dispose();
			if (subject != null) subject.dispose();
			if (finger != null) finger.dispose();
		}
	}

}
