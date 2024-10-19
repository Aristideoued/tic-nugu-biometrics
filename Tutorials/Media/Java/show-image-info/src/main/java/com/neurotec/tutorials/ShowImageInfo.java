package com.neurotec.tutorials;

import java.io.File;
import java.io.IOException;

import com.neurotec.images.JPEG2KInfo;
import com.neurotec.images.JPEGInfo;
import com.neurotec.images.NImage;
import com.neurotec.images.NImageFormat;
import com.neurotec.images.PNGInfo;
import com.neurotec.images.WSQInfo;
import com.neurotec.lang.NThrowable;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ShowImageInfo {

	private static final String DESCRIPTION = "Displays information about an image.";
	private static final String NAME = "show-image-info";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [filename]%n", NAME);
		System.out.println();
		System.out.println("\tfilename - image filename.");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 1) {
			usage();
			System.exit(-1);
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

		NImage image = null;
		try {

			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			// Create NImage from file
			image = NImage.fromFile(args[0]);

			// Get image format
			NImageFormat format = image.getInfo().getFormat();

			// Print info common to all formats
			File file = new File(args[0]);
			System.out.println("Image: " + file.getName());
			System.out.println("Size: " + (file.length() * 100 / 1024) / 100.0 + " KB");
			System.out.println("Format: " + format.getName());

			// Print format specific info
			if (NImageFormat.getJPEG2K().equals(format)) {
				JPEG2KInfo info = (JPEG2KInfo) image.getInfo();
				System.out.println("Profile: " + info.getProfile());
				System.out.println("Compression ratio: " + info.getRatio());
			} else if (NImageFormat.getJPEG().equals(format)) {
				JPEGInfo info = (JPEGInfo) image.getInfo();
				System.out.println("Lossless: " + info.isLossless());
				System.out.println("Quality: " + info.getQuality());
			} else if (NImageFormat.getPNG().equals(format)) {
				PNGInfo info = (PNGInfo) image.getInfo();
				System.out.println("Compression level: " + info.getCompressionLevel());
			} else if (NImageFormat.getWSQ().equals(format)) {
				WSQInfo info = (WSQInfo) image.getInfo();
				System.out.println("Bit rate: " + info.getBitRate());
				System.out.println("Implementation number: " + info.getImplementationNumber());
			};
		} catch (Throwable th) {
			th.printStackTrace();

			int errorCode = -1;

			if (th instanceof NThrowable) {
				errorCode = ((NThrowable)th).getCode();
			}

			System.exit(errorCode);
		} finally {
			if (image != null) { image.dispose(); }
		}

	}
}
