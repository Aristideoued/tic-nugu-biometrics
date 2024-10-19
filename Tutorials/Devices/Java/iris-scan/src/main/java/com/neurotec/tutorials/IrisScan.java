package com.neurotec.tutorials;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NEPosition;
import com.neurotec.biometrics.NIris;
import com.neurotec.devices.NDevice;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NIrisScanner;
import com.neurotec.lang.NCore;
import com.neurotec.lang.NThrowable;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class IrisScan {

	private static final String DESCRIPTION = "Demonstrates capturing iris image from iris scanner";
	private static final String NAME = "iris-scan";
	private static final String VERSION = "13.1.0.0";

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "IrisExtractor";
		//final String license = "IrisClient";
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

		NDeviceManager deviceManager = null;
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			deviceManager = new NDeviceManager();
			deviceManager.setDeviceTypes(EnumSet.of(NDeviceType.IRIS_SCANNER));
			deviceManager.setAutoPlug(true);
			deviceManager.initialize();
			System.out.println("Device manager created. Found scanners: " + deviceManager.getDevices().size());

			for (NDevice device : deviceManager.getDevices()) {
				NIrisScanner scanner = (NIrisScanner) device;
				System.out.println("Found scanner " + scanner.getDisplayName());
				captureIris(scanner, NEPosition.RIGHT);
				captureIris(scanner, NEPosition.LEFT);
			}
			System.out.println("Done");
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (deviceManager != null) deviceManager.dispose();
			NCore.shutdown();
		}
	}

	private static void captureIris(NIrisScanner scanner, NEPosition position) throws IOException {
		NIris iris = null;
		try {
			System.out.format("\tCapturing %s iris:%n", position.name().toLowerCase());
			iris = new NIris();
			iris.setPosition(position);
			NBiometricStatus status = scanner.capture(iris, -1);
			if (status != NBiometricStatus.OK) {
				System.err.format("Failed to capture from scanner, status: %s%n", status);
			} else {
				iris.getImage().save(String.format("%s_iris_%s.jpg", scanner.getDisplayName(), position.name().toLowerCase()));
				System.out.println("Done");
			}
		} finally {
			if (iris != null) iris.dispose();
		}
	}
}
