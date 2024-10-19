package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NFace;
import com.neurotec.biometrics.NMatchingResult;
import com.neurotec.biometrics.NMatchingSpeed;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class IdentifyFace {
	private static final String DESCRIPTION = "Demonstrates face identification";
	private static final String NAME = "identify-face";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [probe image] [one or more gallery images]%n", NAME);
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
		// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String licenses = "FaceMatcher,FaceExtractor";
		//final String licenses = "FaceMatcher,FaceClient";
		//final String licenses = "FaceFastMatcher,FaceFastExtractor";
		//final String licenses = "SentiVeillance";

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
		NSubject probeSubject = null;
		NBiometricTask enrollTask = null;

		try {
			// Obtain licenses
			if (!NLicense.obtain("/local", 5000, licenses)) {
				System.err.format("Could not obtain licenses: %s%n", licenses);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			probeSubject = createSubject(args[0], "ProbeSubject");

			NBiometricStatus status = biometricClient.createTemplate(probeSubject);

			if (status != NBiometricStatus.OK) {
				System.out.format("Failed to create probe template. Status: %s.\n", status);
				System.exit(-1);
			}

			enrollTask = biometricClient.createTask(EnumSet.of(NBiometricOperation.ENROLL), null);
			for (int i = 1; i < args.length; i++) {
				enrollTask.getSubjects().add(createSubject(args[i], String.format("GallerySubject_%d", i)));
			}
			biometricClient.performTask(enrollTask);
			if (enrollTask.getStatus() != NBiometricStatus.OK) {
				System.out.format("Enrollment was unsuccessful. Status: %s.\n", enrollTask.getStatus());
				if (enrollTask.getError() != null) throw enrollTask.getError();
				System.exit(-1);
			}

			biometricClient.setMatchingThreshold(48);

			biometricClient.setFacesMatchingSpeed(NMatchingSpeed.LOW);

			status = biometricClient.identify(probeSubject);

			if (status == NBiometricStatus.OK) {
				for (NMatchingResult result : probeSubject.getMatchingResults()) {
					System.out.format("Matched with ID: '%s' with score %d\n", result.getId(), result.getScore());
				}
			} else if (status == NBiometricStatus.MATCH_NOT_FOUND) {
				System.out.format("Match not found");
			} else {
				System.out.format("Identification failed. Status: %s\n", status);
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (enrollTask != null) enrollTask.dispose();
			if (probeSubject != null) probeSubject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}

	private static NSubject createSubject(String fileName, String subjectId) {
		NSubject subject = new NSubject();
		NFace face = new NFace();
		face.setFileName(fileName);
		subject.getFaces().add(face);
		subject.setId(subjectId);
		return subject;
	}

}
