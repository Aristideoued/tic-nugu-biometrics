package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NBiometricTypes;
import com.neurotec.biometrics.NFIQQuality;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;
import com.neurotec.util.NVersion;

public final class EvaluateNfiq {

	private static final String DESCRIPTION = "Demonstrates fingerprint image quality evaluation.";
	private static final String NAME = "evaluate-nfiq";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [image]%n", NAME);
		System.out.println("");
		System.out.println("\t[image] - image of fingerprint to be evaluated.");
		System.out.println("");
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

		final String license = "FingerClient";
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
		NBiometricTask task = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			finger = new NFinger();

			finger.setFileName(args[0]);

			subject.getFingers().add(finger);

			biometricClient.setFingersCalculateNFIQ(true);
			biometricClient.setFingersCalculateNFIQ2(true);

			task = biometricClient.createTask(EnumSet.of(NBiometricOperation.ASSESS_QUALITY), subject);

			biometricClient.performTask(task);

			if (task.getStatus() == NBiometricStatus.OK) {
				NFIQQuality quality = NBiometricTypes.NFIQ1ToNFIQQuality(subject.getFingers().get(0).getObjects().get(0).getNFIQ(new NVersion(1, 0)));

				System.out.format("NFIQ1 is: %s(%s) and NFIQ2 is: %s\n",
						subject.getFingers().get(0).getObjects().get(0).getNFIQ(new NVersion(1, 0)),
						quality,
						subject.getFingers().get(0).getObjects().get(0).getNFIQ(new NVersion(2, 0)));
			} else {
				System.out.format("Quality assessment failed: %s\n", task.getStatus());
				if (task.getError() != null) throw task.getError();
				System.exit(-1);
			}

		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (task != null) task.dispose();
			if (finger != null) finger.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}
}
