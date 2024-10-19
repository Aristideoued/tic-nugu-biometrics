package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricAttributeId;
import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NFace;
import com.neurotec.biometrics.NLAttributes;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class CreateTokenFaceImage {
	private static final String DESCRIPTION = "Demonstrates creation of token face image.";
	private static final String NAME = "create-token-face-image";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [FaceImage] [CreateTokenFaceImage]%n", NAME);
		System.out.println();
		System.out.println("\t[FaceImage] - an image containing frontal face.");
		System.out.println("\t[CreateTokenFaceImage] - filename of created token face image.");
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

		final String license = "FaceClient";
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
		NBiometricTask task = null;
		
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			face = new NFace();

			face.setFileName(args[0]);
			subject.getFaces().add(face);

			task = biometricClient.createTask(EnumSet.of(NBiometricOperation.SEGMENT, NBiometricOperation.ASSESS_QUALITY), subject);

			biometricClient.performTask(task);

			if (task.getStatus() == NBiometricStatus.OK) {
				NLAttributes originalAttributes = face.getObjects().get(0);
				NLAttributes attributes = ((NFace) originalAttributes.getChild()).getObjects().get(0);
				System.out.format("Global token face image quality score = %d Tested attributes details:\n", attributes.getQuality());
				System.out.format("\tsharpness score = %d\n", attributes.getAttributeValue(NBiometricAttributeId.SHARPNESS));
				System.out.format("\tbackground uniformity score = %d\n", attributes.getAttributeValue(NBiometricAttributeId.BACKGROUND_UNIFORMITY));
				System.out.format("\tgrayscale density score = %d\n", attributes.getAttributeValue(NBiometricAttributeId.GRAYSCALE_DENSITY));

				// Save token Image to file
				subject.getFaces().get(1).getImage().save(args[1]);
			} else {
				System.out.format("Token Face Image creation failed! Status = %s\n", task.getStatus());
				if (task.getError() != null) throw task.getError();
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (task != null) task.dispose();
			if (face != null) face.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}
}
