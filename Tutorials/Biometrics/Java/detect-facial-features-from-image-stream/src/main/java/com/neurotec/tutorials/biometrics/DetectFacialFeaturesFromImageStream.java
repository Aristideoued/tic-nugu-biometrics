package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NFace;
import com.neurotec.biometrics.NLAttributes;
import com.neurotec.biometrics.NLFeaturePoint;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.images.NImage;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.media.NMediaReader;
import com.neurotec.media.NMediaSource;
import com.neurotec.media.NMediaType;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class DetectFacialFeaturesFromImageStream {

	private static final String DESCRIPTION = "Demonstrates facial features detection from image stream";
	private static final String NAME = "detect-facial-features-from-image-stream";
	private static final String VERSION = "13.1.0.0";

	private static final int MAX_FRAME_COUNT = 100;

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [-u url]%n", NAME);
		System.out.format("\t%s [-f filename]%n", NAME);
		System.out.format("\t%s [-d directory]%n", NAME);
		System.out.println();
		System.out.println("\t[-u url] - url to RTSP stream");
		System.out.println("\t[-f filename] -  video file containing a face");
		System.out.println("\t[-d directory] - directory containing face images");
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

		//final String license = "FaceExtractor";
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
			subject = new NSubject();
			face = new NFace();
			face.setHasMoreSamples(true);

			// Add NFace to NSubject
			subject.getFaces().add(face);

			// Create NMedia reader or prepare to use a gallery
			NMediaReader reader = null;
			String[] files = null;
			if (args[0].equals("-f")) {
				reader = new NMediaReader(NMediaSource.fromFile(args[1]), EnumSet.of(NMediaType.VIDEO), true);
			} else if (args[0].equals("-u")) {
				reader = new NMediaReader(NMediaSource.fromUrl(args[1]), EnumSet.of(NMediaType.VIDEO), true);
			} else if (args[0].equals("-d")) {
				files = Utils.getDirectoryFilesList(args[1]);
			} else {
				throw new Exception("Unknown input options specified!");
			}

			// Set from how many frames to detect
			boolean isReaderUsed = reader != null;
			int maximumFrames = isReaderUsed ? MAX_FRAME_COUNT : files.length;

			// Create Detection task
			NBiometricTask task = biometricClient.createTask(EnumSet.of(NBiometricOperation.DETECT_SEGMENTS), subject);

			// Start the reader if gallery is not used
			if (isReaderUsed) reader.start();

			NImage image = null;
			for (int i = 0; i < maximumFrames; i++) {
				// Read from reader otherwise create an image from specified gallery
				image = isReaderUsed ? reader.readVideoSample().getImage() : NImage.fromFile(files[i]);

				// Image will be null when reader has read all available frames
				if (image == null) break;
				face.setImage(image);
				biometricClient.performTask(task);

				System.out.format("[%d] detection status: {%s}", i, task.getStatus());
				if (task.getStatus() == NBiometricStatus.OK) {
					printFaceAttributes(face);
				} else if (task.getStatus() != NBiometricStatus.OBJECT_NOT_FOUND) {
					System.out.format("Detection failed! Status: %s", task.getStatus());
					if (task.getError() != null) throw task.getError();
					return;
				}
				image.dispose();
			}

			if (isReaderUsed) reader.stop();

			// Reset HasMoreSamples value since we finished loading images
			face.setHasMoreSamples(false);

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
		}
	}

	private static void printNleFeaturePoint(String name, NLFeaturePoint point) {
		if (point.confidence == 0) {
			System.out.format("\t\t{0} feature unavailable. confidence: 0%n", name);
			return;
		}
		System.out.format("\t\t%s feature found. X: %d, Y: %d, confidence: %d%n", name, point.x, point.y, point.confidence);
	}

}
