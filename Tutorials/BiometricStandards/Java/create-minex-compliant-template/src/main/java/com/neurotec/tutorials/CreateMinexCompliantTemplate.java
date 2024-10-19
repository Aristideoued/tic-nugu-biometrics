package com.neurotec.tutorials;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricEngine;
import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NExtractionScenario;
import com.neurotec.biometrics.NFIQQuality;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.BDIFTypes;
import com.neurotec.biometrics.standards.FMRFingerView;
import com.neurotec.biometrics.standards.FMRecord;
import com.neurotec.biometrics.standards.CBEFFBDBFormatIdentifiers;
import com.neurotec.biometrics.standards.CBEFFBiometricOrganizations;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.Utils;
import com.neurotec.util.NVersion;

public final class CreateMinexCompliantTemplate {
	private static final String DESCRIPTION = "Create Minex compliant template";
	private static final String NAME = "create-minex-compliant-template";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t %s [image] [template]%n", NAME);
		System.out.println();
		System.out.println("\t[image] - image filename to extract.");
		System.out.println("\t[template] - FMRecord to store extracted features.");
		System.out.println();
		System.out.println("example:");
		System.out.format("\t%s image.jpg fmrecord.FMRecord%n", NAME);
	}

	public static void main(String[] args) {
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

		NBiometricEngine biometricEngine = null;
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String imageFileName = args[0];
			String outputFileName = args[1];

			biometricEngine = new NBiometricEngine();
			NSubject subject = new NSubject();
			NFinger finger = new NFinger();
			
			finger.setFileName(imageFileName);
			subject.getFingers().add(finger);
			
			biometricEngine.setFingersExtractionScenario(NExtractionScenario.Minex);
			
			NBiometricTask task = biometricEngine.createTask(EnumSet.of(NBiometricOperation.CREATE_TEMPLATE, NBiometricOperation.ASSESS_QUALITY) , subject);
			
			biometricEngine.performTask(task);
			NBiometricStatus biometricStatus = task.getStatus();
			
			if (biometricStatus == NBiometricStatus.OK)
			{
				System.out.println("ANSI template extracted.");

				// save FMRecord
				NBuffer storedFmRecord = subject.getTemplateBuffer(CBEFFBiometricOrganizations.INCITS_TC_M1_BIOMETRICS,
					CBEFFBDBFormatIdentifiers.INCITS_TC_M1_BIOMETRICS_FINGER_MINUTIAE_U,
					FMRecord.VERSION_ANSI_20);
				NFile.writeAllBytes(outputFileName, storedFmRecord);
			}
			else {
				System.out.println("Template extraction failed!");
				System.out.println("Biometric status = " + biometricStatus);
				System.out.println("Task error:" + task.getError().getMessage());
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (biometricEngine != null) {
				biometricEngine.close();
			}
		}
	}
}
