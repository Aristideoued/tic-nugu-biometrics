package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;
import java.util.Scanner;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NFScanner;
import com.neurotec.devices.NDeviceManager.DeviceCollection;
import com.neurotec.io.NFile;
import com.neurotec.lang.NCore;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class EnrollFingerFromScanner {
	private static final String DESCRIPTION = "Demonstrates fingerprint feature extraction from fingerprint scanning device.";
	private static final String NAME = "enroll-finger-from-scanner";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [image] [template]%n", NAME);
		System.out.println("\t[image]    - image filename to store scanned image.");
		System.out.println("\t[template] - filename to store finger template.");
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

		NBiometricClient biometricClient = null;
		NSubject subject = null;
		NFinger finger = null;
		
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			finger = new NFinger();

			biometricClient.setUseDeviceManager(true);
			NDeviceManager deviceManager = biometricClient.getDeviceManager();

			deviceManager.setDeviceTypes(EnumSet.of(NDeviceType.FINGER_SCANNER));

			deviceManager.initialize();

			DeviceCollection devices = deviceManager.getDevices();

			if (devices.size() > 0) {
				System.out.format("Found %d fingerprint scanner\n", devices.size());
			} else {
				System.out.format("No scanners found\n");
				return;
			}

			if (devices.size() > 1)
				System.out.println("Please select finger scanner from the list:");

			for (int i = 0; i < devices.size(); i++)
				System.out.format("\t%d. %s\n", i + 1, devices.get(i).getDisplayName());

			int selection = 0;
			if (devices.size() > 1) {
				Scanner scanner = new Scanner(System.in);
				selection = scanner.nextInt() - 1;
				scanner.close();
			}

			biometricClient.setFingerScanner((NFScanner) devices.get(selection));

			subject.getFingers().add(finger);

			System.out.println("Capturing....");
			NBiometricStatus status = biometricClient.capture(subject);
			if (status != NBiometricStatus.OK) {
				System.out.format("Failed to capture: $s\n", status);
				System.exit(-1);
			}

			biometricClient.setFingersTemplateSize(NTemplateSize.LARGE);

			status = biometricClient.createTemplate(subject);

			if (status == NBiometricStatus.OK) {
				System.out.println("Template extracted");
			} else {
				System.out.format("Extraction failed: %s\n", status);
				System.exit(-1);
			}

			subject.getFingers().get(0).getImage().save(args[0]);
			System.out.println("Fingerprint image saved successfully...");

			NFile.writeAllBytes(args[1], subject.getTemplate().save());
			System.out.println("Template file saved successfully...");
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (finger != null) finger.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}
}
