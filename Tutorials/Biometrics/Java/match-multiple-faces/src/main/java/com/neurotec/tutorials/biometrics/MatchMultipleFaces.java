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

public final class MatchMultipleFaces {
	private static final String DESCRIPTION = "Demonstrates matching a face from reference image to multiple faces from other image.";
	private static final String NAME = "match-multiple-faces";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [reference face image] [multiple faces image]%n", NAME);
		System.out.println();
		System.out.println("\t[reference face image]  - filename of image with a single (reference) face.");
		System.out.println("\t[multiple faces image]  - filename of image with multiple faces.\n");
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
		NSubject referenceSubject = null;
		NSubject candidateSubject = null;
		NBiometricTask enrollTask = null;
		
		try {
			// Obtain licenses
			if (!NLicense.obtain("/local", 5000, licenses)) {
				System.err.format("Could not obtain licenses: %s%n", licenses);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();

			referenceSubject = createSubject(args[0], args[0], false);
			candidateSubject = createSubject(args[1], args[1], true);

			NBiometricStatus status = biometricClient.createTemplate(referenceSubject);
			if (status != NBiometricStatus.OK) {
				System.out.format("Template creation was unsuccessful. Status: %s\n.", status);
				return;
			}

			status = biometricClient.createTemplate(candidateSubject);
			if (status != NBiometricStatus.OK) {
				System.out.format("Template creation was unsuccessful. Status: %s\n.", status);
				return;
			}

			enrollTask = biometricClient.createTask(EnumSet.of(NBiometricOperation.ENROLL), null);

			int i = 0;
			candidateSubject.setId(new Integer(i++).toString());
			enrollTask.getSubjects().add(candidateSubject);
			for (NSubject relatedSubject : candidateSubject.getRelatedSubjects()) {
				relatedSubject.setId(new Integer(i++).toString());
				enrollTask.getSubjects().add(relatedSubject);
			}

			biometricClient.performTask(enrollTask);
			if (enrollTask.getStatus() != NBiometricStatus.OK) {
				System.out.format("Enrollment was unsuccessful. Status: %s.\n", status);
				return;
			}

			biometricClient.setMatchingThreshold(48);

			biometricClient.setFacesMatchingSpeed(NMatchingSpeed.LOW);

			status = biometricClient.identify(referenceSubject);

			if (status == NBiometricStatus.OK) {
				for (NMatchingResult result : referenceSubject.getMatchingResults()) {
					System.out.format("Matched with ID: '%s' with score %d\n", result.getId(), result.getScore());
				}
			} else if (status == NBiometricStatus.MATCH_NOT_FOUND) {
				System.out.format("Match not found");
			} else {
				System.out.format("Identification failed. Status: %s.\n", status);
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (enrollTask != null) enrollTask.dispose();
			if (referenceSubject != null) referenceSubject.dispose();
			if (candidateSubject != null) candidateSubject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}

	private static NSubject createSubject(String fileName, String subjectId, boolean isMultipleSubjects) {
		NSubject subject = new NSubject();
		subject.setId(subjectId);
		subject.setMultipleSubjects(isMultipleSubjects);
		NFace face = new NFace();
		face.setFileName(fileName);
		subject.getFaces().add(face);
		return subject;
	}
}
