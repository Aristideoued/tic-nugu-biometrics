package com.neurotec.tutorials;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFPosition;
import com.neurotec.biometrics.NFinger;
import com.neurotec.devices.NDevice;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NFScanner;
import com.neurotec.lang.NCore;
import com.neurotec.lang.NThrowable;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class FingerScan {

	private static final String DESCRIPTION = "Demonstrates fingerprint image capturing from scanner";
	private static final String NAME = "finger-scan";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [imageCount]%n", NAME);
		System.out.println();
		System.out.println("\timageCount - count of fingerprint images to be scanned.");
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

		final String license = "FingerExtractor";
		//final String license = "FingerClient";
		//final String license = "FingerFastExtractor";

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

			int imageCount = Integer.parseInt(args[0]);
			if (imageCount <= 0) {
				System.err.println("No frames will be captured as frame count is not specified");
				System.exit(-1);
			}

			deviceManager = new NDeviceManager();
			deviceManager.setDeviceTypes(EnumSet.of(NDeviceType.FINGER_SCANNER));
			deviceManager.setAutoPlug(true);
			deviceManager.initialize();
			System.out.println("Device manager created. Found scanners: " + deviceManager.getDevices().size());

			for (NDevice device : deviceManager.getDevices()) {
				NFScanner scanner = (NFScanner) device;
				System.out.format("Found scanner %s, capturing fingerprints%n", scanner.getDisplayName());

				for (int i = 0; i < imageCount; i++) {
					System.out.format("\tImage %d of %d. Please put your fingerprint on scanner:", i + 1, imageCount);
					String filename = String.format("%s_%d.jpg", scanner.getDisplayName(), i);
					NFinger biometric = null;
					try {
						biometric = new NFinger();
						biometric.setPosition(NFPosition.UNKNOWN);
						NBiometricStatus status = scanner.capture(biometric, -1);
						if (status != NBiometricStatus.OK) {
							System.err.format("Failed to capture from scanner, status: %s%n", status);
							continue;
						}
						biometric.getImage().save(filename);
						System.out.println("Image captured");
					} finally {
						if (biometric != null) biometric.dispose();
					}
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
