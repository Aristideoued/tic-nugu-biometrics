package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.NFRecord;
import com.neurotec.biometrics.NFTemplate;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FMCRMinutiaFormat;
import com.neurotec.biometrics.standards.FMCRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;
import com.neurotec.util.NVersion;

public final class FMCRecordToNTemplate {

	private static final String DESCRIPTION = "Converting FMCRecord to NTemplate";
	private static final String NAME = "fmcrecord-to-ntemplate";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t %s [FMCRecord] [NTemplate] [Version] [MinutiaeFormat] [ReadBerTlv]%n", NAME);
		System.out.println();
		System.out.println("\t[FMCRecord] - filename of FMCRecord.");
		System.out.println("\t[NTemplate] - filename of NTemplate to be created.");
		System.out.println("\t[Version] - FMCRecord version.");
		System.out.println("\t\tISO2 - ISO/IEC 19794-2:2005.");
		System.out.println("\t\tISO3 - ISO/IEC 19794-2:2011.");
		System.out.println("\t[MinutiaeFormat] - card format of minutiae data.");
		System.out.println("\t\tC - compact size.");
		System.out.println("\t\tN - normal size (ISO2 only).");
		System.out.println("\tReadBerTlvDo - FMCRecord read from buffer option");
		System.out.println("\t\t1 - Biometric Data Template (BDT) or Cardholder");
		System.out.println("\t\t    Biometric Data (CBD) BER-TLV DO (Data Object)");
		System.out.println("\t\t0 - minutiae data buffer only.\n");
		System.out.println();
		System.out.println("example:");
		System.out.format("\t%s fmcRecord.FMCRecord template.NTemplate ISO3 C 1%n", NAME);
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

		FMCRecord fmcRecord = null;
		NTemplate nTemplate = null;
		NBuffer storedFmcRecord = null;
		NBuffer packedNTemplate = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			BDIFStandard standard = BDIFStandard.ISO;
			int flags = 0; // BDIFTypes.FLAG_NON_STRICT_READ - removes non-unique minutiae for FMCRecord.VERSION_ISO_30 only

			NVersion standardVersion;
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

			// Check if full FMCRecord BER-TLV Data Object (DO) (e.g., Biometric Data Template (BDT) or Cardholder Biometric Data (CBD)) or minutiae buffer only is available
			boolean isBerTlv = args[4].equals("1");

			storedFmcRecord = NFile.readAllBytes(args[0]);
			if (isBerTlv) {
				// Create FMCRecord object from FMCRecord BER-TLV Data Object (DO) stored in memory (e.g., BDT or CBD BER-TLV DO)
				fmcRecord = new FMCRecord(storedFmcRecord, standard, standardVersion, minutiaFormat, flags);
			} else { // if (!isBerTlv)
				// Create FMCrecord and read minutiae data from buffer to FMCRecord
				fmcRecord = new FMCRecord(standard, standardVersion, minutiaFormat);
				fmcRecord.setMinutiaeBuffer(storedFmcRecord);
			}

			// Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
			if (fmcRecord.getVersion().equals(FMCRecord.VERSION_ISO_20) && !fmcRecord.isValidateMinutiaeUniqueness()) {
				System.out.println("!!!WARNING!!!:");
				System.out.println("Not all minutiae in FMCRecord are unique!");
				System.out.println(
						"Please, try using ISO3 version with BDIFTypes.FLAG_NON_STRICT_READ flag to remove non-unique minutiae while reading.");
			}

			// Convert FMCRecord to NFRecord
			NFRecord nfRecord = fmcRecord.toNFRecord();

			// Add NFRecord to NFTemplate
			NFTemplate nfTemplate = new NFTemplate();
			nfTemplate.getRecords().add(nfRecord);
			// Set NFTemplate to NTemplate
			nTemplate = new NTemplate();
			nTemplate.setFingers(nfTemplate);

			// Pack NTemplate object
			packedNTemplate = nTemplate.save();
			NFile.writeAllBytes(args[1], packedNTemplate);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (fmcRecord != null) fmcRecord.dispose(); // explicit resource clean-up
			if (nTemplate != null) nTemplate.dispose();
			if (storedFmcRecord != null) storedFmcRecord.dispose();
			if (packedNTemplate != null) packedNTemplate.dispose();
		}
	}
}
