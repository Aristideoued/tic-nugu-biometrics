package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;
import java.util.Scanner;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NEPosition;
import com.neurotec.biometrics.NIris;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NDeviceManager.DeviceCollection;
import com.neurotec.devices.NIrisScanner;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class EnrollIrisFromScanner {
	private static final String DESCRIPTION = "Demonstrates iris feature extraction from iris scanning device.";
	private static final String NAME = "enroll-iris-from-scanner";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [image1] [image2] [template]%n", NAME);
		System.out.println("\t[image1]    - image filename to store scanned left iris image.");
		System.out.println("\t[image2]    - image filename to store scanned right iris image.");
		System.out.println("\t[template] - filename to store iris template.");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 3) {
			usage();
			System.exit(1);
		}

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

		NBiometricClient biometricClient = null;
		NSubject subject = null;
		NIris irisLeft = null;
		NIris irisRight = null;
		
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			irisLeft = new NIris();
			irisRight = new NIris();

			irisLeft.setPosition(NEPosition.LEFT);
			irisRight.setPosition(NEPosition.RIGHT);

			biometricClient.setUseDeviceManager(true);
			NDeviceManager deviceManager = biometricClient.getDeviceManager();

			deviceManager.setDeviceTypes(EnumSet.of(NDeviceType.IRIS_SCANNER));

			deviceManager.initialize();

			DeviceCollection devices = deviceManager.getDevices();

			if (devices.size() > 0) {
				System.out.format("Found %d iris scanner\n", devices.size());
			} else {
				System.out.format("No scanners found\n");
				return;
			}

			if (devices.size() > 1)
				System.out.println("Please select iris scanner from the list:");

			for (int i = 0; i < devices.size(); i++)
				System.out.format("\t%d. %s\n", i + 1, devices.get(i).getDisplayName());

			int selection = 0;
			if (devices.size() > 1) {
				Scanner scanner = new Scanner(System.in);
				selection = scanner.nextInt() - 1;
				scanner.close();
			}

			System.out.println("Capturing....");
			biometricClient.setIrisScanner((NIrisScanner) devices.get(selection));

			subject.getIrises().add(irisLeft);
			subject.getIrises().add(irisRight);

			NBiometricStatus status = biometricClient.capture(subject);

			biometricClient.setIrisesTemplateSize(NTemplateSize.LARGE);

			status = biometricClient.createTemplate(subject);

			if (status == NBiometricStatus.OK) {
				System.out.println("Template extracted");
			} else {
				System.out.format("Extraction failed: %s\n", status);
			}

			subject.getIrises().get(0).getImage().save(args[0]);
			System.out.println("Left iris image saved successfully...");

			subject.getIrises().get(1).getImage().save(args[1]);
			System.out.println("Right iris image saved successfully...");

			NFile.writeAllBytes(args[2], subject.getTemplate().save());
			System.out.println("Irises template file saved successfully...");
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (irisRight != null) irisRight.dispose();
			if (irisLeft != null) irisLeft.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}
}
