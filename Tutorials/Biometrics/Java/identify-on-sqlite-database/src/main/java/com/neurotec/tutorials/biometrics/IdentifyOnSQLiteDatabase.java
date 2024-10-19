package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.List;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NMatchingResult;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class IdentifyOnSQLiteDatabase {

	private static final String DESCRIPTION = "Demonstrates how to identify template on SQLite database";
	private static final String NAME = "identify-on-sqlite-database";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.format("usage:\n");
		System.out.format("\t%s [template] [path to database file]\n", NAME);
		System.out.format("\n");
		System.out.format("\ttemplate                   - template for identification\n");
		System.out.format("\tpath to database file      - path to SQLite database file\n");
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
		// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String[] licenses = { "FingerMatcher", "FaceMatcher", "IrisMatcher", "PalmMatcher", "VoiceMatcher" };
		//final String[] licenses = { "FingerFastMatcher", "FaceFastMatcher", "IrisFastMatcher", "PalmFastMatcher", "VoiceFastMatcher" };

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

		NBiometricClient biometricClient = null;
		NSubject subject = null;
		NBiometricTask task = null;

		boolean anyMatchingComponent = false;
		try {
			// Obtain licenses
			for (String license : licenses) {
				if (NLicense.obtain("/local", 5000, license)) {
					System.out.format("Obtained license: %s%n", license);
					anyMatchingComponent = true;
				}
			}
			if (!anyMatchingComponent) {
				System.err.println("Could not obtain any matching license");
				System.exit(-1);
			}

			biometricClient = new NBiometricClient();
			subject = createSubject(args[0], args[0]);

			biometricClient.setDatabaseConnectionToSQLite(args[1]);

			task = biometricClient.createTask(EnumSet.of(NBiometricOperation.IDENTIFY), subject);

			biometricClient.performTask(task);

			if (task.getStatus() != NBiometricStatus.OK) {
				System.out.format("Identification was unsuccessful. Status: %s.", task.getStatus());
				if (task.getError() != null) throw task.getError();
				System.exit(-1);
			}
			for (NMatchingResult matchingResult : subject.getMatchingResults()) {
				System.out.format("Matched with ID: '%s' with score %d\n", matchingResult.getId(), matchingResult.getScore());
			}

		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (task != null) task.dispose();
			if (subject != null) subject.dispose();
			if (biometricClient != null) biometricClient.dispose();
		}
	}

	private static NSubject createSubject(String fileName, String subjectId) throws IOException {
		NSubject subject = new NSubject();
		subject.setTemplateBuffer(NFile.readAllBytes(fileName));
		subject.setId(subjectId);

		return subject;
	}

}
