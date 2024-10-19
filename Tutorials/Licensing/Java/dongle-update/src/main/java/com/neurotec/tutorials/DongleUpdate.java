package com.neurotec.tutorials;

import com.neurotec.licensing.NLicManDongle;
import com.neurotec.licensing.NLicManDongleUpdateTicketInfo;
import com.neurotec.licensing.NLicManDongleUpdateTicketStatus;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.licensing.NLicenseProductInfo;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class DongleUpdate {

	private static final String DESCRIPTION = "Demonstrates dongle online update using ticket";
	private static final String NAME = "dongle-update";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [ticket number]", NAME);
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
			NLicManDongleUpdateTicketInfo ticket = NLicenseManager.getUpdateTicketInfo(args[0]);
			System.out.format("ticket: %s, status: %s, issue date: %3$td/%3$tm/%3$ty\n", ticket.getNumber(),
					ticket.getStatus(), ticket.getIssueDate());

			if (ticket.getDongleDistributorID() != 0 && ticket.getDongleHardwareID() != 0) {
				System.out.format("ticket assigned to dongle: %d (hardware id: %x)\n", ticket.getDongleDistributorID(),
						ticket.getDongleHardwareID());
			}

			for (NLicenseProductInfo license : ticket.getLicenses()) {
				System.out.format("%s OS: %s, Count: %d\n",
						NLicenseManager.getShortProductName(license.getID(), license.getLicenseType()),
						license.getOSFamily().toString(), license.getLicenseCount());
			}

			if (ticket.getStatus() != NLicManDongleUpdateTicketStatus.ENABLED) {
				System.out.format("Specified ticket can not be used as ticket status is: %s\n",
						ticket.getStatus().toString());
				System.exit(-1);
			}

			boolean found = false;
			NLicManDongle[] dongles = NLicenseManager.getDongles();

			for (int x = 0; x > dongles.length; x++) {

				NLicManDongle dongle = dongles[x];
				if (ticket.getDongleDistributorID() != 0 && ticket.getDongleHardwareID() != 0) {
					if (dongle.getDistributorID() == ticket.getDongleDistributorID()
							&& dongle.getHardwareID() == ticket.getDongleHardwareID()) {
						// Apply the dongle update
						dongle.updateOnline(ticket);
						System.out.println("Dongle updated successfully");
						found = true;
						break;
					}
				}
			}

			if (!found) {
				System.out.println("No dongles found (that could be used)");
				System.exit(-1);
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		}
	}

}
