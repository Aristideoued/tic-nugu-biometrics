package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.NFTemplate;
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
import com.neurotec.util.NVersion;

public final class NTemplateToFMRecord {

	private static final String DESCRIPTION = "NTemplate conversion to FMRecord";
	private static final String NAME = "ntemplate-to-fmrecord";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [NTemplate] [FMRecord] [Standard&Version] [FlagUseNeurotecFields] [Encoding]%n", NAME);
		System.out.println();
		System.out.println("\t[NTemplate] - filename of NFRecord.");
		System.out.println("\t[FMRecord] - filename of FMRecord to be created.");
		System.out.println("\t[Standard&Version] - FMRecord standard version.");
		System.out.println("\t\tANSI2 - ANSI/INCITS 378-2004");
		System.out.println("\t\tANSI3.5 - ANSI/INCITS 378-2009");
		System.out.println("\t\tISO2 - ISO/IEC 19794-2:2005");
		System.out.println("\t\tISO3 - ISO/IEC 19794-2:2011");
		System.out.println("\t\tMINEX - Minex compliant record (ANSI/INCITS 378-2004 without extended data)");
		System.out.println("\t[FlagUseNeurotecFields] - 1 if FMRFingerView.FlagUseNeurotecFields flag is used; otherwise, 0 if flag is not used. For Minex compliant record must be 0.");
		System.out.println("\t[Encoding] - specifies FMRecord encoding type");
		System.out.println("\t\t0 - Traditional binary encoding");
		System.out.println("\t\t1 - XML encoding (supported only for ISO3)");
		System.out.println();
		System.out.println("example:");
		System.out.format("\t%s ntemplate.dat fmrecord.dat ISO3 1 0%n", NAME);
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

		if ("/?".equals(args[0]) || "help".equals(args[0])) {
			usage();
			System.exit(-1);
		}

		NTemplate nTemplate = null;
		NFTemplate nfTemplate = null;
		FMRecord fmRecord = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String nTemplateFileName = args[0];
			String outputFileName = args[1];
			BDIFStandard standard = BDIFStandard.UNSPECIFIED;
			NVersion version;
			int flags = 0;
			int flagUseNeurotecFields = Integer.parseInt(args[3]);
			if (args[2].equals("ANSI2")) {
				standard = BDIFStandard.ANSI;
				version = FMRecord.VERSION_ANSI_20;
			} else if (args[2].equals("ISO2")) {
				standard = BDIFStandard.ISO;
				version = FMRecord.VERSION_ISO_20;
			} else if (args[2].equals("ISO3")) {
				standard = BDIFStandard.ISO;
				version = FMRecord.VERSION_ISO_30;
			} else if (args[2].equals("ANSI3.5")) {
				standard = BDIFStandard.ANSI;
				version = FMRecord.VERSION_ANSI_35;
			} else if (args[2].equals("MINEX")) {
				if (flagUseNeurotecFields != 0) 
					throw new IllegalArgumentException("MINEX compliant record and FlagUseNeurotecFields is incompatible");
				standard = BDIFStandard.ANSI;
				version = FMRecord.VERSION_ANSI_20;
				flags = FMRFingerView.FLAG_SKIP_RIDGE_COUNTS | FMRFingerView.FLAG_SKIP_SINGULAR_POINTS | FMRFingerView.FLAG_SKIP_NEUROTEC_FIELDS;
			} else {
				throw new IllegalArgumentException("Version was not recognized");
			}
			flags |= flagUseNeurotecFields == 1 ? FMRFingerView.FLAG_USE_NEUROTEC_FIELDS : 0;

			NBuffer packedNTemplate = NFile.readAllBytes(nTemplateFileName);

			// Creating NTemplate object from packed NTemplate
			nTemplate = new NTemplate(packedNTemplate);

			// Retrieving NFTemplate object from NTemplate object
			nfTemplate = nTemplate.getFingers();

			if (nfTemplate != null) {

				// Creating FMRecord object from NFTemplate object
				fmRecord = new FMRecord(nfTemplate, standard, version);

				// Storing FMRecord object in memory
				BDIFEncodingType encoding = Integer.parseInt(args[4]) == 1 ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;
				NBuffer storedFmRecord = fmRecord.save(encoding, flags);
				NFile.writeAllBytes(outputFileName, storedFmRecord);
			} else {
				System.out.println("There are no NFRecords in NTemplate");
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (nTemplate != null) nTemplate.dispose();
			if (nfTemplate != null) nfTemplate.dispose();
			if (fmRecord != null) fmRecord.dispose();
		}
	}

}
