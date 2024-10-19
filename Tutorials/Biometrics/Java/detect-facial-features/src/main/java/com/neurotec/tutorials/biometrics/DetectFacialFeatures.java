package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NFace;
import com.neurotec.biometrics.NLAttributes;
import com.neurotec.biometrics.NLFeaturePoint;
import com.neurotec.biometrics.NLProperty;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.NBiometricAttributeId;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class DetectFacialFeatures {
	private static final String DESCRIPTION = "Demonstrates detection of face and facial features in the image.";
	private static final String NAME = "detect-facial-features";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [image]%n", NAME);
		System.out.println();
		System.out.println("\t [image] - filename of image.");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 1) {
			usage();
			System.exit(1);
		}

		// =========================================================================
		// CHOOSE LICENCES !!!
		// =========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's
		// functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		// final String license = "FaceExtractor";
		final String license = "FaceClient";
		// final String license = "FaceFastExtractor";
		// final String license = "SentiVeillance";

		// =========================================================================

		// =========================================================================
		// TRIAL MODE
		// =========================================================================
		// Below code line determines whether TRIAL is enabled or not. To use purchased
		// licenses, don't use below code line.
		// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file.
		// So to easily change mode for all our examples, modify that file.
		// Also you can just set TRUE to "TrialMode" property in code.
		// =========================================================================

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

			subject.setMultipleSubjects(true);

			boolean isAdditionalFunctionalityEnabled = license.equals("FaceClient") || license.equals("FaceFastExtractor") || license.equals("SentiVeillance");
			if (isAdditionalFunctionalityEnabled) {
				biometricClient.setFacesDetectAllFeaturePoints(true);
				biometricClient.setFacesRecognizeEmotion(true);
				biometricClient.setFacesDetectProperties(true);
				biometricClient.setFacesDetermineGender(true);
				biometricClient.setFacesDetermineAge(true);
				biometricClient.setFacesDetermineEthnicity(true);
			}

			task = biometricClient.createTask(EnumSet.of(NBiometricOperation.DETECT_SEGMENTS), subject);

			biometricClient.performTask(task);

			if (task.getStatus() == NBiometricStatus.OK) {
				System.out.format("Found %d face(s)\n", face.getObjects().size());

				for (NLAttributes attributes : face.getObjects()) {
					System.out.format("\tLocation = (%d, %d), width = %d, height = %d\n",
							attributes.getBoundingRect().x, attributes.getBoundingRect().y,
							attributes.getBoundingRect().width, attributes.getBoundingRect().height);

					printNleFeaturePoint("LeftEyeCenter", attributes.getLeftEyeCenter());
					printNleFeaturePoint("RightEyeCenter", attributes.getRightEyeCenter());

					if (isAdditionalFunctionalityEnabled) {
						printNleFeaturePoint("MouthCenter", attributes.getMouthCenter());
						printNleFeaturePoint("NoseTip", attributes.getNoseTip());

						System.out.println();
						for (NLFeaturePoint featurePoint : attributes.getFeaturePoints()) {
							printBaseFeaturePoint(featurePoint);
						}

						System.out.println();
						if (attributes.getAttributeValue(NBiometricAttributeId.AGE) == 254) {
							System.out.format("\t\tAge not detected\n");
						} else {
							System.out.format("\t\tAge: %d\n", attributes.getAttributeValue(NBiometricAttributeId.AGE));
						}
						if (attributes.getGenderConfidence() == 255) {
							System.out.format("\t\tGender not detected\n");
						} else {
							System.out.format("\t\tGender: %s, Confidence: %d\n", attributes.getGender(), attributes.getGenderConfidence());
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.SMILE) == 255) {
							System.out.format("\t\tSmile not detected\n");
						} else {
							System.out.format("\t\tSmile confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.SMILE));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.EYES_OPEN) == 255) {
							System.out.format("\t\tEyes open detected\n");
						} else {
							System.out.format("\t\tEyes open confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EYES_OPEN));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.MOUTH_OPEN) == 255) {
							System.out.format("\t\tMouth open not detected\n");
						} else {
							System.out.format("\t\tMouth open confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.MOUTH_OPEN));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.GLASSES) == 255) {
							System.out.format("\t\tGlasses not detected\n");
						} else {
							System.out.format("\t\tGlasses confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.GLASSES));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.DARK_GLASSES) == 255) {
							System.out.format("\t\tDark glasses not detected\n");
						} else {
							System.out.format("\t\tDark glasses confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.DARK_GLASSES));
						}
						System.out.println();
						System.out.println("\t\tEmotion:");

						if (attributes.getAttributeValue(NBiometricAttributeId.EMOTION_ANGER) == 255) {
							System.out.format("\t\tAnger not detected\n");
						} else {
							System.out.format("\t\tAnger confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EMOTION_ANGER));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.EMOTION_CONTEMPT) == 255) {
							System.out.format("\t\tContempt not detected\n");
						} else {
							System.out.format("\t\tContempt confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EMOTION_CONTEMPT));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.EMOTION_DISGUST) == 255) {
							System.out.format("\t\tDisgust not detected\n");
						} else {
							System.out.format("\t\tDisgust confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EMOTION_DISGUST));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.EMOTION_FEAR) == 255) {
							System.out.format("\t\tFear not detected\n");
						} else {
							System.out.format("\t\tFear confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EMOTION_FEAR));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.EMOTION_HAPPINESS) == 255) {
							System.out.format("\t\tHappiness not detected\n");
						} else {
							System.out.format("\t\tHappiness confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EMOTION_HAPPINESS));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.EMOTION_NEUTRAL) == 255) {
							System.out.format("\t\tNeutral not detected\n");
						} else {
							System.out.format("\t\tNeutral confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EMOTION_NEUTRAL));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.EMOTION_SADNESS) == 255) {
							System.out.format("\t\tSadness not detected\n");
						} else {
							System.out.format("\t\tSadness confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EMOTION_SADNESS));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.EMOTION_SURPRISE) == 255) {
							System.out.format("\t\tSurprise not detected\n");
						} else {
							System.out.format("\t\tSurprise confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.EMOTION_SURPRISE));
						}

						System.out.println();
						System.out.println("\t\tEthnicity:");
						if (attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_ASIAN) == 255) {
							System.out.format("\t\tAsian not detected\n");
						} else {
							System.out.format("\t\tAsian confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_ASIAN));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_BLACK) == 255) {
							System.out.format("\t\tBlack not detected\n");
						} else {
							System.out.format("\t\tBlack confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_BLACK));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_HISPANIC) == 255) {
							System.out.format("\t\tHispanic not detected\n");
						} else {
							System.out.format("\t\tHispanic confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_HISPANIC));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_INDIAN) == 255) {
							System.out.format("\t\tIndian not detected\n");
						} else {
							System.out.format("\t\tIndian confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_INDIAN));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_WHITE) == 255) {
							System.out.format("\t\tWhite not detected\n");
						} else {
							System.out.format("\t\tWhite confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_WHITE));
						}
						if (attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_ARABIAN) == 255) {
							System.out.format("\t\tArabian not detected\n");
						} else {
							System.out.format("\t\tArabian confidence: %d\n", attributes.getAttributeValue(NBiometricAttributeId.ETHNICITY_ARABIAN));
						}
					}
				}
			} else {
				System.out.format("Face detection failed! Status = %s\n", task.getStatus());
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

	private static void printNleFeaturePoint(String name, NLFeaturePoint point) {
		if (point.confidence == 0) {
			System.out.format("\t\t%s feature unavailable. confidence: 0%n", name);
			return;
		}
		System.out.format("\t\t%s feature found. X: %d, Y: %d, confidence: %d%n", name, point.x, point.y, point.confidence);
	}

	private static void printBaseFeaturePoint(NLFeaturePoint point) {
		if (point.confidence == 0) {
			System.out.println("\t\tBase feature point unavailable. confidence: 0");
			return;
		}
		System.out.format("\t\tBase feature point found. X: %d, Y: %d, confidence: %d, Code: %d\n", point.x, point.y, point.confidence, point.code);
	}
}
