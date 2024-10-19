package com.neurotec.tutorials.biometrics;

import java.io.IOException;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NVoice;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public class VerifyVoice {
	
	private static final String DESCRIPTION = "Demonstrates verification of two voice files";
	private static final String NAME = "verify-voice";
	private static final String VERSION = "13.1.0.0";
	
	public static void usage(){
		System.out.println("usage:");
		System.out.format("\t%s [reference] [candidate]", NAME);
		System.out.println();
		System.out.println("\t[reference] - reference to voice file");
		System.out.println("\t[candidate] - voice file to verify with");
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

		final String licenses = "VoiceMatcher,VoiceExtractor";
		//final String licenses = "VoiceMatcher,VoiceClient";
		//final String licenses = "VoiceFastMatcher,VoiceFastExtractor";

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

		try {
			// Obtain licenses
			if (!NLicense.obtain("/local", 5000, licenses)) {
				System.err.format("Could not obtain licenses: %s%n", licenses);
				System.exit(-1);
			}

			// Create NBiometricClient
			biometricClient = new NBiometricClient();

			// Create subjects with face
			referenceSubject = createSubject(args[0], args[0]);
			candidateSubject = createSubject(args[1], args[1]);

			// Set matching threshold
			biometricClient.setMatchingThreshold(48);
			
			// Verify subjects
			NBiometricStatus status = biometricClient.verify(referenceSubject, candidateSubject);

			if (status == NBiometricStatus.OK || status == NBiometricStatus.MATCH_NOT_FOUND) {
				int score = referenceSubject.getMatchingResults().get(0).getScore();
				System.out.format("Voice scored %d, verification ", score);
				if (status == NBiometricStatus.OK) {
					System.out.println("succeeded");
				} else {
					System.out.println("failed");
				}
			} else {
				System.out.format("Verification failed. Status: %s", status);
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (referenceSubject != null) referenceSubject.dispose();
			if (candidateSubject != null) candidateSubject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}

	public static NSubject createSubject(String fileName, String subjectId)
	{
		NSubject subject = new NSubject();
		NVoice voice = new NVoice();
		voice.setFileName(fileName);
		subject.getVoices().add(voice);
		subject.setId(subjectId);
		return subject;
	}
}