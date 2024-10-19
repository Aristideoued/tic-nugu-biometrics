package com.neurotec.tutorials;

import com.neurotec.licensing.NLicManDongle;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.licensing.NLicenseProductInfo;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class DongleInfo {

	private static final String DESCRIPTION = "Demonstrates dongle information retrieval";
	private static final String NAME = "dongle-info";
	private static final String VERSION = "13.1.0.0";

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);
		try {
			NLicManDongle[] dongles = NLicenseManager.getDongles();
			if (dongles.length == 0) {
				System.out.println("No dongles found");
				System.exit(-1);
			}

			for (int x = 0; x < dongles.length; x++) {

				System.out.format("=== Dongle Id: %d ===\n", dongles[x].getDistributorID());
				NLicenseProductInfo[] licenses = dongles[x].getLicenses();
				for (NLicenseProductInfo licenseInfo : licenses) {
					System.out.format("%s OS: %s, Count: %d\n",
							NLicenseManager.getShortProductName(licenseInfo.getID(), licenseInfo.getLicenseType()),
							licenseInfo.getOSFamily().toString(), licenseInfo.getLicenseCount());
				}
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		}
	}

}
