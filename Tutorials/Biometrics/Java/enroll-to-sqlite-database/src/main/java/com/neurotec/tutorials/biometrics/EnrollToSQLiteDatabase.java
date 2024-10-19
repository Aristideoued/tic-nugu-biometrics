package com.neurotec.tutorials.biometrics;

import java.io.File;
import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class EnrollToSQLiteDatabase {
	
	private static final String DESCRIPTION = "Demonstrates how to enroll template to SQLite database";
	private static final String NAME = "enroll-to-sqlite-database";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [template] [path to database file]%n", NAME);
		System.out.format("\t%s [folder] [path to database file]%n", NAME);
		System.out.println();
		System.out.println("\ttemplate                   - template for enrollment");
		System.out.println("\tfolder                     - folder containing templates");
		System.out.println("\tpath to database file      - path to SQLite database file");

	}
	
	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 2) {
			usage();
			System.exit(1);
		}

		NBiometricClient biometricClient = null;
		
		try {
			biometricClient = new NBiometricClient();
			// Set connection to SQLite database
			biometricClient.setDatabaseConnectionToSQLite(args[1]);
			
			File f = new File(args[0]);
			if (f.isDirectory()) {
				for (File file : f.listFiles()) {
					enrollTemplate(biometricClient, file.getAbsolutePath());
				}
			} else {
				enrollTemplate(biometricClient, args[0]);
			}
			
			System.out.format("Enrollment was successful. The SQLite database contains these IDs:%n");
			
			NSubject[] subjects = null;
			NBiometricTask listTask = biometricClient.createTask(EnumSet.of(NBiometricOperation.LIST), null);
			do {
				biometricClient.performTask(listTask);
				if (listTask.getStatus() != NBiometricStatus.OK) {
					if (listTask.getError() != null)
						throw listTask.getError();
					throw new Exception("Subject list task failed. Status: " + listTask.getStatus().toString());
				}
				
				// Task will return subject in batches
				// when all subjects are listed, task will return an empty array
				subjects = (NSubject[])listTask.getSubjects().toArray();
				for (NSubject s : subjects) {
					System.out.format("\t%s%n", s.getId());
				}
			} while (subjects.length != 0);
			
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (biometricClient != null) biometricClient.dispose();
		}
	}
	
	private static NSubject createSubject(String fileName) throws IOException {
		NSubject subject = new NSubject();
		subject.setTemplateBuffer(NFile.readAllBytes(fileName));
		subject.setId(fileName);

		return subject;
	}
	
	private static void enrollTemplate(NBiometricClient biometricClient, String fileName) throws Exception {
		NSubject subject = createSubject(fileName);
		NBiometricStatus status = biometricClient.enroll(subject);
		if (status != NBiometricStatus.OK)
			throw new Exception("Enrollment was unsuccessful. Status: " + status.toString());
		subject.dispose();
	}
}
