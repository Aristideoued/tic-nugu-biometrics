package com.neurotec.tutorials.biometrics;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.swing.NFingerView;
import com.neurotec.images.NImage;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class DrawMinutiaeOnImage {
	private static final String DESCRIPTION = "Demonstrates minutiae drawing on image";
	private static final String NAME = "draw-minutiae-on-image";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("%s [input image] [output image]%n", NAME);
		System.out.println("\t[input image] - image file containing a finger");
		System.out.println("\t[output image] - filename to store image with minutiae");
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
		NFingerView fingerView = null;
		NSubject subject = null;
		NFinger finger = null;
		NImage image = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();
			finger = new NFinger();
			fingerView = new NFingerView();

			image = NImage.fromFile(args[0]);
			// Setting finger image
			finger.setImage(image);

			subject.getFingers().add(finger);

			NBiometricStatus status = biometricClient.createTemplate(subject);

			if (status == NBiometricStatus.OK) {
				System.out.println("Image with minutiae creation succeeded");

				fingerView.setSize(image.getWidth(), image.getHeight());

				// Settings finger with template to finger view
				fingerView.setFinger(subject.getFingers().get(0));


				BufferedImage tempImage = new BufferedImage(fingerView.getWidth(), fingerView.getHeight(), BufferedImage.TYPE_INT_RGB);
				Graphics2D g2d = tempImage.createGraphics();
				fingerView.printAll(g2d);
				g2d.dispose();

				ImageIO.write(tempImage, "jpg", new File(args[1]));

			} else {
				System.err.format("Image with minutiae creation failed: %s%n", status.toString());
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (finger != null) finger.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}
}
