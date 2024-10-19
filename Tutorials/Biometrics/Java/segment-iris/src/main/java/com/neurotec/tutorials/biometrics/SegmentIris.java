package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NEAttributes;
import com.neurotec.biometrics.NEImageType;
import com.neurotec.biometrics.NIris;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.NBiometricAttributeId;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class SegmentIris {

	private static final String DESCRIPTION = "Demonstrates iris segmenter";
	private static final String NAME = "segment-iris";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [input image] [output image]%n", NAME);
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

		final String license = "IrisClient";
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
		NBiometricTask task = null;
		
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			iris = new NIris();

			iris.setFileName(args[0]);

			iris.setImageType(NEImageType.CROPPED_AND_MASKED);
			subject.getIrises().add(iris);

			task = biometricClient.createTask(EnumSet.of(NBiometricOperation.SEGMENT), subject);

			biometricClient.performTask(task);

			if (task.getStatus() == NBiometricStatus.OK) {
				for (NEAttributes attributes : iris.getObjects()) {
					System.out.format("overall quality\t%d\n", attributes.getQuality());
					System.out.format("GrayScaleUtilisation\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.GRAYSCALE_UTILISATION));
					System.out.format("Interlace\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.INTERLACE));
					System.out.format("IrisPupilConcentricity\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.IRIS_PUPIL_CONCENTRICITY));
					System.out.format("IrisPupilContrast\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.IRIS_PUPIL_CONTRAST));
					System.out.format("IrisScleraContrast\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.IRIS_SCLERA_CONTRAST));
					System.out.format("MarginAdequacy\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.MARGIN_ADEQUACY));
					System.out.format("PupilBoundaryCircularity\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.PUPIL_BOUNDARY_CIRCULARITY));
					System.out.format("PupilToIrisRatio\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.PUPIL_TO_IRIS_RATIO));
					System.out.format("Sharpness\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.SHARPNESS));
					System.out.format("UsableIrisArea\t%d\n", attributes.getAttributeValue(NBiometricAttributeId.USABLE_IRIS_AREA));
				}

				// Save segmented image
				((NIris) iris.getObjects().get(0).getChild()).getImage().save(args[1]);
			} else {
				System.err.println("Segmentation failed: " + task.getStatus());
				if (task.getError() != null) throw task.getError();
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (task != null) task.dispose();
			if (iris != null) iris.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}
}
