package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FCRFaceImageType;
import com.neurotec.biometrics.standards.FCRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;
import com.neurotec.util.NVersion;

public final class FCRecordFromNImage {

	private static final String DESCRIPTION = "Create FCRecord from image tutorial";
	private static final String NAME = "fcrecord-from-nimage";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.format("usage: %s [FCRecord] [Standard] [Version] {[image]}%n", NAME);
		System.out.println("\t[FCRecord] - output FCRecord");
		System.out.println("\t[Standard] - standard for the record (ISO or ANSI)");
		System.out.println("\t[Version] - version for the record");
		System.out.println("\t\t 1 - ANSI/INCITS 375-2004");
		System.out.println("\t\t 1 - ISO/IEC 19794-5:2005");
		System.out.println("\t\t 3 - ISO/IEC 19794-5:2011");
		System.out.println("\t[image]    - one or more images");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 4) {
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "FaceClient";
		//final String license = "FaceFastExtractor";

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

		FCRecord fc = null;
		BDIFStandard standard;
		NVersion version;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}
			standard  = BDIFStandard.valueOf(args[1]);

			switch (Integer.parseInt(args[2])) {
			case 1: {
				version = standard == BDIFStandard.ANSI ? FCRecord.VERSION_ANSI_10 : FCRecord.VERSION_ISO_10; 
			}break;
			case 3: {
				if (standard != BDIFStandard.ISO) throw new IllegalArgumentException("Standard and version is incompatible");
				version = FCRecord.VERSION_ISO_30; 
			}break;
			default:
				throw new IllegalArgumentException("Version was not recognised");
			}

			FCRFaceImageType faceImageType = FCRFaceImageType.BASIC;
			NBuffer imageBuffer = null;
			for (int i = 3; i < args.length; i++) {
				imageBuffer = NFile.readAllBytes(args[i]);
				if (fc == null) {
					fc = new FCRecord(standard, version, faceImageType, imageBuffer);
				} else {
					fc.getFaceImages().add(faceImageType, imageBuffer);
				}
				if (imageBuffer != null) {
					imageBuffer.dispose();
				}
			}
			if (fc != null) {
				NFile.writeAllBytes(args[0], fc.save());
				System.out.println("FCRecord saved to " + args[0]);
			} else {
				System.out.println("No images were added to FCRecord");
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (fc != null) fc.dispose();
		}
	}
}
