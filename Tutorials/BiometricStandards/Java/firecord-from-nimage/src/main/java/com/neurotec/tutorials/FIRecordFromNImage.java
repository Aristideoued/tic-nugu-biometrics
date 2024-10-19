package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.biometrics.standards.BDIFFPPosition;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FIRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;
import com.neurotec.util.NVersion;

public final class FIRecordFromNImage {

	private static final String DESCRIPTION = "Create FIRecord from image tutorial";
	private static final String NAME = "firecord-from-nimage";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.format("usage: %s [FIRecord] [Standard] [Encoding] [Version] {[image]}%n", NAME);
		System.out.println("\t[FIRecord] - output FIRecord");
		System.out.println("\t[Standard] - standard for the record (ANSI or ISO)");
		System.out.println("\t[Encoding] - encoding for the record (TRADITIONAL or XML)");
		System.out.println("\t[Version] - version for the record");
		System.out.println("\t\t 1 - ANSI/INCITS 381-2004");
		System.out.println("\t\t 2.5 - ANSI/INCITS 381-2009");
		System.out.println("\t\t 1 - ISO/IEC 19794-4:2005");
		System.out.println("\t\t 2 - ISO/IEC 19794-4:2011");
		System.out.println("\t[image] - one or more images");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 5) {
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

		FIRecord fi = null;
		NBuffer imgBuffer = null;
		int vertScanResolution = 500;
		int horzScanResolution = 500;
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			BDIFStandard standard = BDIFStandard.valueOf(args[1]);
			BDIFEncodingType encoding = BDIFEncodingType.valueOf(args[2]);
			
			NVersion version;
			if (args[3].equals("1")) {
				version = (standard == BDIFStandard.ANSI) ? FIRecord.VERSION_ANSI_10 : FIRecord.VERSION_ISO_10;
			} else if (args[3].equals("2")) {
				if (standard != BDIFStandard.ISO) {
					throw new IllegalArgumentException("Standard and version is incompatible.");
				}
				version = FIRecord.VERSION_ISO_20;
			} else if (args[3].equals("2.5")) {
				if (standard != BDIFStandard.ANSI) {
					throw new IllegalArgumentException("Standard and version is incompatible.");
				}
				version = FIRecord.VERSION_ANSI_25;
			} else {
				throw new IllegalArgumentException("Version was not recognized.");
			}
			
			if(encoding == BDIFEncodingType.XML && version != FIRecord.VERSION_ISO_20)
			{
				throw new IllegalArgumentException("XML encoded record is only availabe for ISO version 2.");
			}

			for (int i = 4; i < args.length; i++) {
				try {
					imgBuffer = NFile.readAllBytes(args[i]);
					if (fi == null) {
						fi = new FIRecord(standard, version, (short) 10, BDIFFPPosition.RIGHT_THUMB, horzScanResolution, vertScanResolution, imgBuffer);
					} else {
						fi.getFingerViews().add(BDIFFPPosition.RIGHT_THUMB, horzScanResolution, vertScanResolution, imgBuffer);
					}
				} finally {
					if (imgBuffer != null) imgBuffer.dispose();
				}
			}

			if (fi != null) {
				NFile.writeAllBytes(args[0], fi.save(encoding));
				System.out.println("FIRecord saved to " + args[0]);
			} else {
				System.out.println("No images were added to FIRecord");
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (fi != null) fi.dispose();
		}
	}
}
