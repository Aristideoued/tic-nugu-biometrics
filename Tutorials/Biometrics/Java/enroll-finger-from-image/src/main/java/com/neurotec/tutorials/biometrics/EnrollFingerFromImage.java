package com.neurotec.tutorials.biometrics;

import java.io.IOException;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.CBEFFBDBFormatIdentifiers;
import com.neurotec.biometrics.standards.CBEFFBiometricOrganizations;
import com.neurotec.biometrics.standards.FMRecord;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class EnrollFingerFromImage {
	private static final String DESCRIPTION = "Demonstrates fingerprint feature extraction from image.";
	private static final String NAME = "enroll-finger-from-image";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:\n");
		System.out.format("\t%s [image] [template] [format]\n", NAME);
		System.out.println("\n");
		System.out.println("\t[image]    - image filename to extract.\n");
		System.out.println("\t[template] - filename to store extracted features.\n");
		System.out.println("\t[format]   - whether proprietary or standard template should be created.\n");
		System.out.println("\t\tIf not specified, proprietary Neurotechnology template is created (recommended).\n");
		System.out.println("\t\tANSI for ANSI/INCITS 378-2004\n");
		System.out.println("\t\tISO for ISO/IEC 19794-2\n");
		System.out.println("\n\nexamples:\n");
		System.out.format("\t%s image.jpg template.dat\n", NAME);
		System.out.format("\t%s image.jpg isoTemplate.dat ISO\n", NAME);
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		BDIFStandard standard = BDIFStandard.UNSPECIFIED;

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 2) {
			usage();
			System.exit(1);
		}
		if (args.length > 2)
		{
			if (args[2].equals("ANSI"))
			{
				standard = BDIFStandard.ANSI;
			}
			if (args[2].equals("ISO"))
			{
				standard = BDIFStandard.ISO;
			}
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

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			NBiometricClient biometricClient = new NBiometricClient();
			NSubject subject = new NSubject();
			NFinger finger = new NFinger();

			finger.setFileName(args[0]);

			subject.getFingers().add(finger);

			biometricClient.setFingersTemplateSize(NTemplateSize.LARGE);

			NBiometricStatus status = biometricClient.createTemplate(subject);

			if (status == NBiometricStatus.OK) {
				System.out.format("%s template extracted. \n", standard == BDIFStandard.ISO ? "ISO" : standard == BDIFStandard.ANSI ? "ANSI" : "Proprietary");
				if (standard == BDIFStandard.ISO)
				{
					NFile.writeAllBytes(args[1], subject.getTemplateBuffer(CBEFFBiometricOrganizations.ISO_IEC_JTC_1_SC_37_BIOMETRICS,
						CBEFFBDBFormatIdentifiers.ISO_IEC_JTC_1_SC_37_BIOMETRICS_FINGER_MINUTIAE_RECORD_FORMAT,
						FMRecord.VERSION_ISO_CURRENT));
				}
				else if (standard == BDIFStandard.ANSI)
				{
					NFile.writeAllBytes(args[1], subject.getTemplateBuffer(CBEFFBiometricOrganizations.INCITS_TC_M1_BIOMETRICS,
						CBEFFBDBFormatIdentifiers.INCITS_TC_M1_BIOMETRICS_FINGER_MINUTIAE_U,
						FMRecord.VERSION_ANSI_CURRENT));
				}
				else
				{
					NFile.writeAllBytes(args[1], subject.getTemplateBuffer());
				}
				System.out.println("Template saved successfully");
			} else {
				System.out.format("Extraction failed: %s\n", status);
			}

		} catch (Throwable th) {
			Utils.handleError(th);
		}
	}
}
