package com.neurotec.tutorials;

import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseInfo;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.licensing.NLicenseProductInfo;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class LicenseInfo {

	private static final String DESCRIPTION = "Demonstrates how to get information about specified license/hardware id/serial number";
	private static final String NAME = "license-info";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [license file name]", NAME);
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 1) {
			usage();
			System.exit(-1);
		}

		try {
			NLicenseInfo licenseInfo = NLicense.getLicenseInfoOnline(Utils.readText(args[0]));
			System.out.println("Specified license information:");
			System.out.format("\tType: %s", licenseInfo.getType());
			System.out.format("\tSource type: %s", licenseInfo.getSourceType());
			System.out.format("\tDistributor id: %d", licenseInfo.getDistributorID());
			System.out.format("\tSequence number: %d", licenseInfo.getSequenceID());
			System.out.format("\tLicense id: %s", licenseInfo.getLicenseID());
			System.out.println("\tProducts:");

			NLicenseProductInfo[] licenses = licenseInfo.getLicenses();

			for (NLicenseProductInfo license : licenses) {
				System.out.format("\t\t%s OS: %s, Count: %d", NLicenseManager.getShortProductName(license.getID(), license.getLicenseType()), license.getOSFamily(), license.getLicenseCount());
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		}
	}
}
