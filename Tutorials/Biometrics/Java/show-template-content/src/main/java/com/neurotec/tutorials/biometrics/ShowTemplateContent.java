package com.neurotec.tutorials.biometrics;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.biometrics.NERecord;
import com.neurotec.biometrics.NFCore;
import com.neurotec.biometrics.NFDelta;
import com.neurotec.biometrics.NFDoubleCore;
import com.neurotec.biometrics.NFMinutia;
import com.neurotec.biometrics.NFMinutiaFormat;
import com.neurotec.biometrics.NFRecord;
import com.neurotec.biometrics.NLRecord;
import com.neurotec.biometrics.NSRecord;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ShowTemplateContent {

	private static final String DESCRIPTION = "Displays data contained in a template.";
	private static final String NAME = "show-template-content";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [NTemplate]%n", NAME);
		System.out.println();
		System.out.println("\tNTemplate  - file containing NTemplate.");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 1 || args[0] == "/?" || args[0] == "--help") {
			usage();
			System.exit(1);
		}

		NTemplate template = null;
		NBuffer templateBuffer = null;
		try {
			templateBuffer = NFile.readAllBytes(args[0]);

			System.out.println();
			System.out.format("template %s contains:%n", args[0]);
			template = new NTemplate(templateBuffer);
			if (template.getFingers() != null) {
				System.out.format("%d fingers%n", template.getFingers().getRecords().size());
				for (NFRecord nfRec : template.getFingers().getRecords()) {
					printNFRecord(nfRec);
				}
			} else {
				System.out.println("0 fingers");
			}
			if (template.getFaces() != null) {
				System.out.format("%d faces%n", template.getFaces().getRecords().size());
				for (NLRecord nlRec : template.getFaces().getRecords()) {
					printNLRecord(nlRec);
				}
			} else {
				System.out.println("0 faces");
			}
			if (template.getIrises() != null) {
				System.out.format("%d irises%n", template.getIrises().getRecords().size());
				for (NERecord neRec : template.getIrises().getRecords()) {
					printNERecord(neRec);
				}
			} else {
				System.out.println("0 irises");
			}
			if (template.getVoices() != null) {
				System.out.format("%d voices%n", template.getVoices().getRecords().size());
				for (NSRecord nsRec : template.getVoices().getRecords()) {
					printNSRecord(nsRec);
				}
			} else {
				System.out.println("0 voices");
			}
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (template != null) template.dispose();
			if (templateBuffer != null) templateBuffer.dispose();
		}
	}

	private static void printNFRecord(NFRecord nfRec) {
		System.out.format("\tg: %d%n", nfRec.getG());
		System.out.format("\timpression type: %s%n", nfRec.getImpressionType());
		System.out.format("\tpattern class: %s%n", nfRec.getPatternClass());
		System.out.format("\tcbeff product type: %d%n", nfRec.getCBEFFProductType());
		System.out.format("\tposition: %s%n", nfRec.getPosition());
		System.out.format("\tridge counts type: %s%n", nfRec.getRidgeCountsType());
		System.out.format("\twidth: %d%n", nfRec.getWidth());
		System.out.format("\theight: %d%n", nfRec.getHeight());
		System.out.format("\thorizontal resolution: %d%n", nfRec.getHorzResolution());
		System.out.format("\tvertical resolution: %d%n", nfRec.getVertResolution());
		System.out.format("\tquality: %d%n", nfRec.getQuality());
		System.out.format("\tsize: %d%n", nfRec.getSize());

		System.out.format("\tminutia count: %d%n", nfRec.getMinutiae().size());

		EnumSet<NFMinutiaFormat> minutiaFormat = nfRec.getMinutiaFormat();

		int index = 1;
		for (NFMinutia minutia : nfRec.getMinutiae()) {
			System.out.format("\t\tminutia %d of %d%n", index, nfRec.getMinutiae().size());
			System.out.format("\t\tx: %d%n", minutia.x);
			System.out.format("\t\ty: %d%n", minutia.y);
			System.out.format("\t\tangle: %d%n", rotationToDegrees(minutia.angle & 0xFF));
			if (minutiaFormat.contains(NFMinutiaFormat.HAS_QUALITY)) {
				System.out.format("\t\tquality: %d%n", minutia.quality & 0xFF);
			}
			if (minutiaFormat.contains(NFMinutiaFormat.HAS_G)) {
				System.out.format("\t\tg: %d%n", minutia.g);
			}
			if (minutiaFormat.contains(NFMinutiaFormat.HAS_CURVATURE)) {
				System.out.format("\t\tcurvature: %d%n", minutia.curvature);
			}

			System.out.println();
			index++;
		}

		index = 1;
		for (NFDelta delta : nfRec.getDeltas()) {
			System.out.format("\t\tdelta %d of %d%n", index, nfRec.getDeltas().size());
			System.out.format("\t\tx: %d%n", delta.x);
			System.out.format("\t\ty: %d%n", delta.y);
			System.out.format("\t\tangle1: %d%n", rotationToDegrees(delta.angle1));
			System.out.format("\t\tangle2: %d%n", rotationToDegrees(delta.angle2));
			System.out.format("\t\tangle3: %d%n", rotationToDegrees(delta.angle3));

			System.out.println();
			index++;
		}

		index = 1;
		for (NFCore core : nfRec.getCores()) {
			System.out.format("\t\tcore %d of %d%n", index, nfRec.getCores().size());
			System.out.format("\t\tx: %d%n", core.x);
			System.out.format("\t\ty: %d%n", core.y);
			System.out.format("\t\tangle: %d%n", rotationToDegrees(core.angle));

			System.out.println();
			index++;
		}

		index = 1;
		for (NFDoubleCore doubleCore : nfRec.getDoubleCores()) {
			System.out.format("\t\tdouble core %d of %d%n", index, nfRec.getDoubleCores().size());
			System.out.format("\t\tx: %d%n", doubleCore.x);
			System.out.format("\t\ty: %d%n", doubleCore.y);

			System.out.println();
			index++;
		}
	}

	private static void printNLRecord(NLRecord nlRec) {
		System.out.format("\tquality: %d%n", nlRec.getQuality());
		System.out.format("\tsize: %d%n", nlRec.getSize());
	}

	private static void printNERecord(NERecord neRec) {
		System.out.format("\tposition: %s%n", neRec.getPosition());
		System.out.format("\tsize: %d%n", neRec.getSize());
	}

	private static void printNSRecord(NSRecord nsRec) {
		System.out.format("\tphrase id: %d%n", nsRec.getPhraseId());
		System.out.format("\tsize: %d%n", nsRec.getSize());
	}

	private static int rotationToDegrees(int rotation) {
		return (2 * rotation * 360 + 256) / (2 * 256);
	}
}
