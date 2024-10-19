package com.neurotec.tutorials;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.devices.NCamera;
import com.neurotec.devices.NDevice;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.devices.NDeviceType;
import com.neurotec.images.NImage;
import com.neurotec.lang.NCore;
import com.neurotec.lang.NThrowable;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ImageCapture {

	private static final String DESCRIPTION = "Demonstrates capturing images from cameras";
	private static final String NAME = "image-capture";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [frameCount]%n", NAME);
		System.out.println();
		System.out.println("\tframeCount - number of frames to capture from each camera to current directory.");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 1) {
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
		//final String license = "SentiVeillance"

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

		NDeviceManager deviceManager = null;
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			int frameCount = Integer.parseInt(args[0]);
			if (frameCount <= 0) {
				System.out.println("No frames will be captured as frame count is not specified");
			}

			deviceManager = new NDeviceManager();
			deviceManager.setDeviceTypes(EnumSet.of(NDeviceType.CAMERA));
			deviceManager.setAutoPlug(true);
			deviceManager.initialize();
			System.out.println("Device manager created. Found cameras: " + deviceManager.getDevices().size());

			for (NDevice device : deviceManager.getDevices()) {
				NCamera camera = (NCamera) device;
				System.out.print("Found camera " + camera.getDisplayName());
				try {
					camera.startCapturing();
					if (frameCount > 0) {
						System.out.print(", capturing");
						for (int i = 0; i < frameCount; ++i) {
							NImage image = null;
							try {
								image = camera.getFrame();
								image.save(String.format("%s_%d.jpg", camera.getDisplayName(), i));
							} finally {
								if (image != null) image.dispose();
							}
							System.out.print(".");
						}
						System.out.println(" Done");
					}
				} finally {
					if (camera  != null) camera.stopCapturing();
				}
			}
			System.out.println("Done");
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (deviceManager != null) deviceManager.dispose();
			NCore.shutdown();
		}
	}
}
