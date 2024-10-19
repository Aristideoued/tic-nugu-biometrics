package com.neurotec.tutorials.biometrics;

import java.io.IOException;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFace;
import com.neurotec.biometrics.NLAttributes;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class EnrollFaceFromImage {
	private static final String DESCRIPTION = "Demonstrates enrollment from one image";
	private static final String NAME = "enroll-face-from-image";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("%s [input image] [output template]%n", NAME);
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
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

		final String license = "FaceExtractor";
		//final String license = "FaceClient";
		//final String license = "FaceFastExtractor";
		//final String license = "SentiVeillance";

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
		NFace face = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			face = new NFace();

			// Set file name with face image
			face.setFileName(args[0]);

			subject.getFaces().add(face);

			// Detect all faces features
			boolean isAdditionalFunctionalityEnabled = license.equals("FaceClient") || license.equals("FaceFastExtractor") || license.equals("SentiVeillance");
			biometricClient.setFacesDetectAllFeaturePoints(isAdditionalFunctionalityEnabled);

			NBiometricStatus status = biometricClient.createTemplate(subject);

			if (subject.getFaces().size() > 1)
				System.out.format("Found %d faces\n", subject.getFaces().size() - 1);

			// List attributes for all located faces
			for (NFace nface : subject.getFaces()) {
				for (NLAttributes attribute : nface.getObjects()) {
					System.out.println("Face:");
					System.out.format("\tLocation = (%d, %d), width = %d, height = %d\n", attribute.getBoundingRect().getBounds().x, attribute.getBoundingRect().getBounds().y,
							attribute.getBoundingRect().width, attribute.getBoundingRect().height);

					if ((attribute.getRightEyeCenter().confidence > 0) || (attribute.getLeftEyeCenter().confidence > 0)) {
						System.out.println("\tFound eyes:");
						if (attribute.getRightEyeCenter().confidence > 0) {
							System.out.format("\t\tRight: location = (%d, %d), confidence = %d%n", attribute.getRightEyeCenter().x, attribute.getRightEyeCenter().y,
									attribute.getRightEyeCenter().confidence);
						}
						if (attribute.getLeftEyeCenter().confidence > 0) {
							System.out.format("\t\tLeft: location = (%d, %d), confidence = %d%n", attribute.getLeftEyeCenter().x, attribute.getLeftEyeCenter().y,
									attribute.getLeftEyeCenter().confidence);
						}
					}
					if (isAdditionalFunctionalityEnabled) {
						if (attribute.getNoseTip().confidence > 0) {
							System.out.println("\tFound nose:");
							System.out.format("\t\tLocation = (%d, %d), confidence = %d%n", attribute.getNoseTip().x, attribute.getNoseTip().y, attribute.getNoseTip().confidence);
						}
						if (attribute.getMouthCenter().confidence > 0) {
							System.out.println("\tFound mouth:");
							System.out.printf("\t\tLocation = (%d, %d), confidence = %d%n", attribute.getMouthCenter().x, attribute.getMouthCenter().y, attribute.getMouthCenter().confidence);
						}
					}
				}
			}

			if (status == NBiometricStatus.OK) {
				System.out.println("Template extracted");
				// Save compressed template to file
				NFile.writeAllBytes(args[1], subject.getTemplate().save());
				System.out.println("Template saved successfully");
			} else {
				System.out.format("Extraction failed: %s%n", status.toString());
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (face != null) face.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}
}
