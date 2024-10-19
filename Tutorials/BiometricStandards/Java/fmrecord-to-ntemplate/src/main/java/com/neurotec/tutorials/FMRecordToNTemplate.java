package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.NTemplate;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FMRFingerView;
import com.neurotec.biometrics.standards.FMRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class FMRecordToNTemplate {

	private static final String DESCRIPTION = "Converting FMRecord to NTemplate";
	private static final String NAME = "fmrecord-to-ntemplate";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t %s [FMRecord] [NTemplate] [Standard] [FlagUseNeurotecFields]%n", NAME);
		System.out.println();
		System.out.println("\t[FMRecord] - filename of FMRecord.");
		System.out.println("\t[NTemplate] - filename of NTemplate to be created.");
		System.out.println("\t[Standard] - FMRecord standard (ISO or ANSI).");
		System.out.println("\t[FlagUseNeurotecFields] - 1 if FMRFingerView.FlagUseNeurotecFields flag is used; otherwise, 0 if flag is not used.");
		System.out.println();
		System.out.println("example:");
		System.out.format("\t%s fmrecord.dat ntemplate.dat ISO 1%n", NAME);
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

		FMRecord fmRecord = null;
		NTemplate nTemplate = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String fmRecordFileName = args[0];
			String outputFileName = args[1];
			BDIFStandard standard = BDIFStandard.valueOf(args[2]);
			int flagUseNeurotecFields = Integer.parseInt(args[3]);

			if ("/?".equals(fmRecordFileName) || "help".equals(fmRecordFileName)) {
				usage();
				System.exit(0);
			}

			NBuffer storedFmRecord = NFile.readAllBytes(fmRecordFileName);

			// Creating FMRecord object from FMRecord stored in memory
			if (flagUseNeurotecFields == 1) {
				fmRecord = new FMRecord(storedFmRecord, FMRFingerView.FLAG_USE_NEUROTEC_FIELDS, standard);
			} else {
				fmRecord = new FMRecord(storedFmRecord, standard);
			}

			// Converting FMRecord object to NTemplate object
			nTemplate = fmRecord.toNTemplate();
			// Packing NTemplate object
			NBuffer packedNTemplate = nTemplate.save();

			NFile.writeAllBytes(outputFileName, packedNTemplate);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (fmRecord != null) fmRecord.dispose();
			if (nTemplate != null) nTemplate.dispose();
		}
	}
}
