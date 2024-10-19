package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricType;
import com.neurotec.biometrics.NEMatchingDetails;
import com.neurotec.biometrics.NFMatchingDetails;
import com.neurotec.biometrics.NLMatchingDetails;
import com.neurotec.biometrics.NMatchingDetails;
import com.neurotec.biometrics.NMatchingResult;
import com.neurotec.biometrics.NSMatchingDetails;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class Verify {

	private static final String DESCRIPTION = "Demonstrates template verification";
	private static final String NAME = "verify";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [reference template] [candidate template]%n", NAME);
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

		NBiometricClient biometricClient = null;
		NSubject probeSubject = null;
		NSubject candidateSubject = null;

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

			biometricClient = new NBiometricClient();

			probeSubject = createSubject(args[0], args[0]);
			candidateSubject = createSubject(args[1], args[1]);

			biometricClient.setMatchingThreshold(48);

			biometricClient.setMatchingWithDetails(true);

			NBiometricStatus status = biometricClient.verify(probeSubject, candidateSubject);

			if (status == NBiometricStatus.OK) {
				for (NMatchingResult matchResult : probeSubject.getMatchingResults()) {
					System.out.format("Matched with ID: '%s' with score %d\n", matchResult.getId(), matchResult.getScore());
					if (matchResult.getMatchingDetails() != null) {
						System.out.println(matchingDetailsToString(matchResult.getMatchingDetails()));
					}
				}
			} else if (status == NBiometricStatus.MATCH_NOT_FOUND) {
				System.out.format("Match not found");
			} else {
				System.out.format("Verification failed. Status: %s.\n", status);
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (candidateSubject != null) candidateSubject.dispose();
			if (probeSubject != null) probeSubject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}

	private static NSubject createSubject(String fileName, String subjectId) throws IOException {
		NSubject subject = new NSubject();
		subject.setTemplate(new NTemplate(NFile.readAllBytes(fileName)));
		subject.setId(subjectId);

		return subject;
	}

	private static String matchingDetailsToString(NMatchingDetails details) {
		StringBuffer sb = new StringBuffer();
		if (details.getBiometricType().contains(NBiometricType.FINGER)) {
			sb.append("    Fingerprint match details: ");
			sb.append(String.format(" score = %d%n", details.getFingersScore()));
			for (NFMatchingDetails fngrDetails : details.getFingers()) {
				sb.append(String.format("    fingerprint index: %d; score: %d;%n", fngrDetails.getMatchedIndex(), fngrDetails.getScore()));
			}
		}

		if (details.getBiometricType().contains(NBiometricType.FACE)) {
			sb.append("    Face match details: ");
			sb.append(String.format(" score = %d%n", details.getFacesScore()));
			for (NLMatchingDetails faceDetails : details.getFaces()) {
				sb.append(String.format("    face index: %d; score: %d;%n", faceDetails.getMatchedIndex(), faceDetails.getScore()));
			}
		}

		if (details.getBiometricType().contains(NBiometricType.IRIS)) {
			sb.append("    Irises match details: ");
			sb.append(String.format(" score = %d%n", details.getIrisesScore()));
			for (NEMatchingDetails irisesDetails : details.getIrises()) {
				sb.append(String.format("    irises index: %d; score: %d;%n", irisesDetails.getMatchedIndex(), irisesDetails.getScore()));
			}
		}

		if (details.getBiometricType().contains(NBiometricType.PALM)) {
			sb.append("    Palmprint match details: ");
			sb.append(String.format(" score = %d%n", details.getPalmsScore()));
			for (NFMatchingDetails fngrDetails : details.getPalms()) {
				sb.append(String.format("    palmprint index: %d; score: %d;%n", fngrDetails.getMatchedIndex(), fngrDetails.getScore()));
			}
		}

		if (details.getBiometricType().contains(NBiometricType.VOICE)) {
			sb.append("    Voice match details: ");
			sb.append(String.format(" score = %d%n", details.getVoicesScore()));
			for (NSMatchingDetails voicesDetails : details.getVoices()) {
				sb.append(String.format("    voices index: %d; score: %d;%n", voicesDetails.getMatchedIndex(), voicesDetails.getScore()));
			}
		}
		return sb.toString();
	}
}
