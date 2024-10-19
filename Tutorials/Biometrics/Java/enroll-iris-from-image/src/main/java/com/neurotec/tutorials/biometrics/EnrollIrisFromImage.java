package com.neurotec.tutorials.biometrics;

import java.io.IOException;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NIris;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;
import com.sun.jna.Platform;

public final class EnrollIrisFromImage {
	private static final String DESCRIPTION = "Demonstrates enrollment from one image";
	private static final String NAME = "enroll-iris-from-image";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("%s [input image] [output template]%n", NAME);
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Platform.isAndroid();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 2) {
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "IrisExtractor";
		//final String license = "IrisClient";
		//final String license = "IrisFastExtractor";

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

		NBiometricClient biometricClient = null;
		NSubject subject = null;
		NIris iris = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			iris = new NIris();
			
			// Set file name with face image
			iris.setFileName(args[0]);

			subject.getIrises().add(iris);

			// Set iris template size (large is recommended for enrolment to database) (optional)
			biometricClient.setIrisesTemplateSize(NTemplateSize.LARGE);

			NBiometricStatus status = biometricClient.createTemplate(subject);

			if (subject.getIrises().size() > 1)
				System.out.format("Found %d iris(es)\n", subject.getIrises().size() - 1);

			if (status == NBiometricStatus.OK) {
				System.out.println("Template extracted");
				NFile.writeAllBytes(args[1], subject.getTemplate().save());
				System.out.println("Template saved successfully");
			} else {
				System.out.format("Extraction failed: %s%n", status.toString());
				System.exit(-1);
			}

		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (iris != null) iris.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}
}
