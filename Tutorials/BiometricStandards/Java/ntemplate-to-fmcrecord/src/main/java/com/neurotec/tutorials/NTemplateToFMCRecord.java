package com.neurotec.tutorials;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NFMinutiaTruncationAlgorithm;
import com.neurotec.biometrics.NFRecord;
import com.neurotec.biometrics.NFTemplate;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FMCRMinutiaFormat;
import com.neurotec.biometrics.standards.FMCRMinutiaOrder;
import com.neurotec.biometrics.standards.FMCRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;
import com.neurotec.util.NVersion;

public final class NTemplateToFMCRecord {

	private static final String DESCRIPTION = "NTemplate conversion to FMCRecord";
	private static final String NAME = "ntemplate-to-fmcrecord";
	private static final String VERSION = "13.1.0.0";

	private static byte minutiaTruncationQualityThreshold = 0;
	/* NOTE: ISO/IEC 19794-2 (informative) minutiae count range recommendations for card formats:
	 - FMCRecord.DEFAULT_MIN_ENROLL_MC to FMCRecord.DEFAULT_MAX_ENROLL_MC for enroll, 
	 - FMCRecord.DEFAULT_MIN_VERIFY_MC to FMCRecord.DEFAULT_MAX_ENROLL_MC for verify.
	*/
	private static int minutiaTruncationMaximalCount = 48;
	private static EnumSet<NFMinutiaTruncationAlgorithm> minutiaTruncationAlgorithm = EnumSet.of(NFMinutiaTruncationAlgorithm.QUALITY_AND_CENTER_OF_MASS); 

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [NTemplate] [FMCRecord] [Version] [MinutiaeFormat] [SaveBiometricDataTemplate]%n", NAME);
		System.out.println();
		System.out.println("\t[NTemplate] - filename of NFCRecord.");
		System.out.println("\t[FMCRecord] - filename of FMCRecord to be created.");
		System.out.println("\t[Version] - FMCRecord version");
		System.out.println("\t\tISO2 - ISO/IEC 19794-2:2005");
		System.out.println("\t\tISO3 - ISO/IEC 19794-2:2011");
		System.out.println("\t[tMinutiaeFormat] - format of minutiae data.");
		System.out.println("\t\tC - compact size");
		System.out.println("\t\tN - normal size (ISO2 only)");
		System.out.println("\tSaveBiometricDataTemplate - FMCRecord save to buffer option");
		System.out.println("\t\t1 - full Biometric Data Template (BDT) BER-TLV DO (Data Object)");
		System.out.println("\t\t0 - minutiae data only");
		System.out.println("");
		System.out.println("examples:");
		System.out.format("\t%s template.NTemplate fmcrecord.FMCRecord ISO3 C 1%n", NAME);
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

		BDIFStandard standard = BDIFStandard.ISO;
		NVersion standardVersion;
		EnumSet<FMCRMinutiaOrder> minutiaOrder = EnumSet.of(FMCRMinutiaOrder.NONE);
		int flags = FMCRecord.FLAG_SKIP_ALL_EXTENDED_DATA | FMCRecord.FLAG_USE_BIOMETRIC_DATA_TEMPLATE; // the most common use case of minutiae data only within on-card records

		FMCRecord fmcRecord = null;
		NTemplate nTemplate = null;
		NBuffer packedNTemplate = null;
		NBuffer storedFmcRecord = null;
		NBuffer minutiaeBuffer = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			if (args[2].equals("ISO2")) {
				standardVersion = FMCRecord.VERSION_ISO_20;
			} else if (args[2].equals("ISO3")) {
				standardVersion = FMCRecord.VERSION_ISO_30;
			} else {
				throw new Exception("Wrong standard");
			}

			FMCRMinutiaFormat minutiaFormat;
			if (args[3].equals("C")) {
				minutiaFormat = FMCRMinutiaFormat.COMPACT_SIZE;
			} else if (args[3].equals("N")) {
				minutiaFormat = FMCRMinutiaFormat.NORMAL_SIZE;
			} else {
				throw new Exception("Wrong minutia format");
			}

			// Check if full FMCRecord Biometric Data Template (BDT) BER-TLV Data Object (DO) or minutiae buffer only to be saved
			boolean isBdtBerTlv = args[4].equals("1");

			packedNTemplate = NFile.readAllBytes(args[0]);
			nTemplate = new NTemplate(packedNTemplate);
			NFTemplate nfTemplate = nTemplate.getFingers();

			if (nfTemplate != null && !nfTemplate.getRecords().isEmpty()) {
				// Retrieve NFRecord object from NFTemplate object
				NFRecord nfRecord = nfTemplate.getRecords().get(0);

				// Truncate minutiae by quality (if more than desired minutiae with quality above minutiaTruncationQualityThreshold remain)
				nfRecord.truncateMinutiaeByQuality(minutiaTruncationQualityThreshold, minutiaTruncationMaximalCount);

				// Truncate minutiae using specified truncation algorithm
				nfRecord.truncateMinutiae(minutiaTruncationAlgorithm, minutiaTruncationMaximalCount);

				// Create FMCRecord object from NFRecord object
				fmcRecord = new FMCRecord(nfRecord, standard, standardVersion, minutiaFormat, minutiaOrder, 0);

				// Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
				if (fmcRecord.getVersion().equals(FMCRecord.VERSION_ISO_20) && !fmcRecord.isValidateMinutiaeUniqueness()) {
					System.out.println("!!!WARNING!!!:");
					System.out.println("Not all minutiae in FMCRecord are unique!");
					System.out.println("Please, try using ISO3 version to remove non-unique minutiae while conversion.");
				}

				if (isBdtBerTlv) {
					// Store FMCRecord object in memory as ISO/IEC 19794-2 and ISO/IEC 7816-11 compliant Biometric Data Template (BDT) BER-TLV Data Object (DO)
					storedFmcRecord = fmcRecord.save(flags);
					NFile.writeAllBytes(args[1], storedFmcRecord);
				} else {
					// Get minutiae data as buffer
					minutiaeBuffer = fmcRecord.getMinutiaeBuffer();
					NFile.writeAllBytes(args[1], minutiaeBuffer);
				}
			} else {
				System.out.println("There are no NFRecords in NTemplate");
			}

		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (fmcRecord != null) fmcRecord.dispose(); // explicit resource clean-up
			if (nTemplate != null) nTemplate.dispose();
			if (packedNTemplate != null) packedNTemplate.dispose();
			if (storedFmcRecord != null) storedFmcRecord.dispose();
			if (minutiaeBuffer != null) minutiaeBuffer.dispose();
		}
	}

}
