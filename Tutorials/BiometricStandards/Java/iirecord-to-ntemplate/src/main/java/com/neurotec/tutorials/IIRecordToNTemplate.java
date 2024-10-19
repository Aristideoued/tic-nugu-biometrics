package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NIris;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.IIRIrisImage;
import com.neurotec.biometrics.standards.IIRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class IIRecordToNTemplate {

	private static final String DESCRIPTION = "Create NTemplate from IIRecord tutorial";
	private static final String NAME = "iirecord-to-ntemplate";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.format("usage: %s [IIRecord] [NTemplate]%n", NAME);
		System.out.println("\t[IIRecord]  - input IIRecord");
		System.out.println("\t[NTemplate] - output NTemplate");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

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
		NBiometricClient biometricClient = null;
		NSubject subject = null;
		NBuffer iiRecordData = null;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = new NSubject();

			// Read IIRecord from file
			iiRecordData = NFile.readAllBytes(args[0]);

			// Create IIRecord
			iiRec = new IIRecord(iiRecordData, BDIFStandard.ISO);

			// Read all images from IIRecord
			for (IIRIrisImage irisImage : iiRec.getIrisImages()) {
				NIris iris = new NIris();
				iris.setImage(irisImage.toNImage());
				subject.getIrises().add(iris);
			}

			// Set iris template size (large is recommended for enrolment to database) (optional)
			biometricClient.setIrisesTemplateSize(NTemplateSize.LARGE);

			// Create template from added iris image(s)
			NBiometricStatus status = biometricClient.createTemplate(subject);

			System.out.println(status == NBiometricStatus.OK
					? "Template extracted"
					: String.format("Extraction failed: %s", status));

			if (status == NBiometricStatus.OK) {
				NFile.writeAllBytes(args[1], subject.getTemplateBuffer());
				System.out.println("NTemplate saved to file " + args[1]);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (iiRecordData != null) iiRecordData.dispose();
			if (iiRec != null) iiRec.dispose();
			if (biometricClient != null) biometricClient.dispose();
			if (subject != null) subject.dispose();
		}
	}
}
