package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.BDIFEyePosition;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.IIRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;
import com.neurotec.util.NVersion;

public final class IIRecordFromNImage {

	private static final String DESCRIPTION = "Create IIRecord from image tutorial";
	private static final String NAME = "iirecord-from-inmage";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.format("usage: %s [IIRecord] [Standard] [Version] {[image]}%n", NAME);
		System.out.println("\t[IIRecord] - output IIRecord");
		System.out.println("\t[Standard] - standard for the record (ANSI or ISO)");
		System.out.println("\t[Version] - version for the record");
		System.out.println("\t\t 1 - ANSI/INCITS 379-2004");
		System.out.println("\t\t 1 - ISO/IEC 19794-6:2005");
		System.out.println("\t\t 2 - ISO/IEC 19794-6:2011");
		System.out.println("\t[image] - one or more images");
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

		IIRecord iiRec = null;
		NVersion version = null;
		NBuffer imgBuffer = null;
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			BDIFStandard standard = BDIFStandard.valueOf(args[1]);
			BDIFEyePosition irisPosition = BDIFEyePosition.LEFT; 
			if (args[2].equals("1")) {
				version = (standard == BDIFStandard.ANSI) ? IIRecord.VERSION_ANSI_10 : IIRecord.VERSION_ISO_10;
			} else if (args[2].equals("2")) {
				if (standard != BDIFStandard.ISO) {
					throw new IllegalArgumentException("Standard and version is incompatible");
				}
				version = IIRecord.VERSION_ISO_20;
			} else {
				throw new IllegalArgumentException("Version was not recognized");
			}

			for (int i = 3; i < args.length; i++) {
				try {
					imgBuffer = NFile.readAllBytes(args[i]);
					if (iiRec == null) {
						iiRec = new IIRecord(standard, version, irisPosition, imgBuffer);
					} else {
						iiRec.getIrisImages().add(irisPosition, imgBuffer);
					}
				} finally {
					if (imgBuffer != null) imgBuffer.dispose();
				}
			}

			if (iiRec != null) {
				NFile.writeAllBytes(args[0], iiRec.save());
				System.out.println("IIRecord saved to " + args[0]);
			} else {
				System.out.println("No images were added to IIRecord");
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (iiRec != null) iiRec.dispose();
		}
	}

}
