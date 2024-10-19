package com.neurotec.tutorials.biometrics;

import com.neurotec.beans.NParameterBag;
import com.neurotec.beans.NParameterDescriptor;
import com.neurotec.biometrics.NBiometricCaptureOption;
import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NBiometricType;
import com.neurotec.biometrics.NFace;
import com.neurotec.biometrics.NLAttributes;
import com.neurotec.biometrics.NLFeaturePoint;
import com.neurotec.biometrics.NLProperty;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.NBiometricAttributeId;
import com.neurotec.devices.NCamera;
import com.neurotec.devices.NDevice;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.plugins.NPlugin;
import com.neurotec.plugins.NPluginState;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

import java.io.IOException;
import java.util.EnumSet;

public final class DetectFacialFeaturesFromCamera {

	private static final String DESCRIPTION = "Demonstrates facial features detection from camera";
	private static final String NAME = "detect-facial-features-from-camera";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [FaceTemplate] [FaceImage] [TokenFaceImage]%n", NAME);
		System.out.format("\t%s [FaceTemplate] [FaceImage] [TokenFaceImage] [-u url](optional)%n", NAME);
		System.out.format("\t%s [FaceTemplate] [FaceImage] [TokenFaceImage] [-f filename](optional)%n", NAME);
		System.out.println();
		System.out.println("\t[FaceTemplate] - filename for template.");
		System.out.println("\t[FaceImage] -	filename for face image.");
		System.out.println("\t[TokenFaceImage] - filename for token face image.");
		System.out.println("\t[-u url] - (optional) url to RTSP stream.");
		System.out.println("\t[-f filename] - (optional) video file containing a face.");
		System.out.println("\tIf url(-u) or filename(-f) attribute is not specified first attached camera will be used.");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if ((args.length != 3) && (args.length != 5)) {
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

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			biometricClient.setUseDeviceManager(true);
			biometricClient.setBiometricTypes(EnumSet.of(NBiometricType.FACE));
			subject = new NSubject();
			face = new NFace();
			face.setCaptureOptions(EnumSet.of(NBiometricCaptureOption.STREAM));

			biometricClient.initialize();

			// Create camera from filename or RTSP stream if attached
			NCamera camera;
			NDeviceManager deviceManager = biometricClient.getDeviceManager();
			if (args.length == 5) {
				camera = (NCamera) connectDevice(deviceManager, args[4], args[3].equals("-u"));
			} else {
				// Get count of connected devices
				int count = deviceManager.getDevices().size();
				if (count == 0) {
					System.out.format("No cameras found, exiting ...\n");
					return;
				}
				// Select the first available camera
				camera = (NCamera) deviceManager.getDevices().get(0);
			}

			// Set the selected camera as NBiometricClient Face Capturing Device
			biometricClient.setFaceCaptureDevice(camera);

			// Set which features should be detected
			biometricClient.setFacesDetectAllFeaturePoints(true);
			biometricClient.setFacesRecognizeEmotion(true);
			biometricClient.setFacesDetectProperties(true);
			biometricClient.setFacesDetermineGender(true);
			biometricClient.setFacesDetermineAge(true);

			// Add NFace to NSubject
			subject.getFaces().add(face);

			NBiometricTask task = biometricClient.createTask(EnumSet.of(NBiometricOperation.CAPTURE,
																		NBiometricOperation.DETECT_SEGMENTS,
																		NBiometricOperation.SEGMENT,
																		NBiometricOperation.ASSESS_QUALITY), subject);

			// Start capturing
			System.out.print("Starting to capture. Please look into the camera... ");
			biometricClient.performTask(task);
			System.out.println("Done.");

			if (task.getStatus() == NBiometricStatus.OK) {

				// Print face attributes
				printFaceAttributes(face);

				// Save template to file
				NFile.writeAllBytes(args[0], subject.getTemplateBuffer());

				// Save original face
				face.getImage().save(args[1]);

				// Save token face image
				subject.getFaces().get(1).getImage().save(args[2]);
			} else {
				System.out.format("Capturing failed: %s\n", task.getStatus());
				System.exit(-1);
			}

		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (face != null) {
				face.dispose();
			}
			if (subject != null) {
				subject.dispose();
			}
			if (biometricClient != null) {
				biometricClient.dispose();
			}
		}
	}

	private static NDevice connectDevice(NDeviceManager deviceManager, String url, boolean isUrl) {
		NPlugin plugin = NDeviceManager.getPluginManager().getPlugins().get("Media");
		if ((plugin.getState() == NPluginState.PLUGGED) && (NDeviceManager.isConnectToDeviceSupported(plugin))) {
			NParameterDescriptor[] parameters = NDeviceManager.getConnectToDeviceParameters(plugin);
			NParameterBag bag = new NParameterBag(parameters);
			if (isUrl) {
				bag.setProperty("DisplayName", "IP Camera");
				bag.setProperty("Url", url);
			} else {
				bag.setProperty("DisplayName", "Video file");
				bag.setProperty("FileName", url);
			}
			return deviceManager.connectToDevice(plugin, bag.toPropertyBag());
		}
		throw new RuntimeException("Failed to connect specified device!");
	}

	private static void printFaceAttributes(NFace face) {
		for (NLAttributes attributes : face.getObjects()) {
			System.out.format("\tLocation = (%d, %d), width = %d, height = %d%n",
							  attributes.getBoundingRect().x,
							  attributes.getBoundingRect().y,
							  attributes.getBoundingRect().width,
							  attributes.getBoundingRect().height);

			printNleFeaturePoint("LeftEyeCenter", attributes.getLeftEyeCenter());
			printNleFeaturePoint("RightEyeCenter", attributes.getRightEyeCenter());
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
				System.out.println("\t\tGender not detected");
			} else {
				System.out.format("\t\tGender: %s, Confidence: %d%n", attributes.getGender(), attributes.getGenderConfidence());
			}
			if (attributes.getAttributeValue(NBiometricAttributeId.SMILE) == 255) {
				System.out.println("\t\tSmile not detected");
			} else {
				System.out.format("\t\tSmile confidence: %d%n", attributes.getAttributeValue(NBiometricAttributeId.SMILE));
			}
			if (attributes.getAttributeValue(NBiometricAttributeId.EYES_OPEN) == 255) {
				System.out.println("\t\tEyes open detected");
			} else {
				System.out.format("\t\tEyes open confidence: %d%n", attributes.getAttributeValue(NBiometricAttributeId.EYES_OPEN));
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
		}
	}

	private static void printNleFeaturePoint(String name, NLFeaturePoint point) {
		if (point.confidence == 0) {
			System.out.format("\t\t{0} feature unavailable. confidence: 0%n", name);
			return;
		}
		System.out.format("\t\t%s feature found. X: %d, Y: %d, confidence: %d%n", name, point.x, point.y, point.confidence);
	}

	private static void printBaseFeaturePoint(NLFeaturePoint point) {
		if (point.confidence == 0) {
			System.out.println("\t\tBase feature point unavailable. confidence: 0");
			return;
		}
		System.out.format("\t\tBase feature point found. X: %d, Y: %d, confidence: %d, Code: %d%n", point.x, point.y, point.confidence, point.code);
	}

}
