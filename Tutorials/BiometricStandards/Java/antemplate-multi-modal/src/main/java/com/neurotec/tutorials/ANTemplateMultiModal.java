package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.ANImageType;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType10Record;
import com.neurotec.biometrics.standards.ANType14Record;
import com.neurotec.biometrics.standards.ANType17Record;
import com.neurotec.biometrics.standards.ANType2Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateMultiModal {

	private static final String DESCRIPTION = "Demonstrates creation of ANTemplate with type 10 record in it.";
	private static final String NAME = "antemplate-multi-modal";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [ANTemplate] [Encoding] [Finger NImage] [Face NImage] [Iris NImage]%n", NAME);
		System.out.println("");
		System.out.println("\t[ANTemplate] - filename for ANTemplate.");
		System.out.println("\t[Encoding] - specifies ANTemplate encoding type.");
		System.out.println("\t\t0 - Traditional binary encoding.");
		System.out.println("\t\t1 - NIEM-conformant XML encoding.");
		System.out.println("\t[Finger NImage] - filename with finger image file.");
		System.out.println("\t[Face NImage] - filename with face image file (optional).");
		System.out.println("\t[Iris NImage] - filename with iris image file (optional).");
		System.out.println("");
	}

	private static ANType2Record ANTemplateGetRecordType2(ANTemplate template, BDIFEncodingType encoding) throws Exception {
		int nameFieldNumber = 18;
		int placeOfBirthFieldNumber = 20;
		int dateOfBirthFieldNumber = 22;
		int genderFieldNumber = 24;

		ANType2Record record = null;

		try {
			record = template.getRecords().addType2();

			// Adds fields for "traditional" binary encoding
			if (encoding == BDIFEncodingType.TRADITIONAL) {
				record.getFields().add(nameFieldNumber, "name, surname");
				record.getFields().add(placeOfBirthFieldNumber, "UK");
				record.getFields().add(dateOfBirthFieldNumber, "19700131");
				record.getFields().add(genderFieldNumber, "M");
			} else { // Adds fields for NIEM-conformant XML encoding
				record.getFields().add(nameFieldNumber, "PersonName", "name, surname");
				record.getFields().add(placeOfBirthFieldNumber, "PersonBirthPlaceCode", "UK");
				record.getFields().add(dateOfBirthFieldNumber, "PersonBirthDate", "19700131");
				record.getFields().add(genderFieldNumber, "PersonSexCode", "M");
			}
			return record;
		} catch (Exception ex) {
			throw ex;
		}
	}

	private static ANType10Record ANTemplateGetRecordType10(ANTemplate template, String fileNameIn, String src) throws Exception {
		ANImageType imt = ANImageType.FACE;

		NBuffer imageBuffer = null;
		ANType10Record record = null;

		try {
			/*
			 * Image must be compressed using valid compression algorithm for Type-10 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			*/
			imageBuffer = NFile.readAllBytes(fileNameIn);
			record = template.getRecords().addType10(imt, src, imageBuffer);
			return record;

		} catch (Exception ex) {
			throw ex;
		} finally {
			if (imageBuffer != null)
				imageBuffer.dispose();
		}
	}

	private static ANType14Record ANTemplateGetRecordType14(ANTemplate template, String fileNameIn, String src) throws Exception {
		NBuffer imageBuffer = null;
		ANType14Record record = null;

		try {
			/*
			 * Finger image must be compressed using valid compression algorithm for Type-14 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			*/
			imageBuffer = NFile.readAllBytes(fileNameIn);
			record = template.getRecords().addType14(src, imageBuffer);
			return record;
		} catch (Exception ex) {
			throw ex;
		} finally {
			if (imageBuffer != null){
				imageBuffer.dispose();
			}
		}
	}

	private static ANType17Record ANTemplateGetRecordType17(ANTemplate template, String fileNameIn, String src) throws Exception {
		ANType17Record record = null;
		NBuffer imageBuffer = null;
		
		try {
			/*
			 * Image must be compressed using valid compression algorithm for Type-17 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			*/
			imageBuffer = NFile.readAllBytes(fileNameIn);
			record = template.getRecords().addType17(src, imageBuffer);
			return record;
		} catch (Exception ex) {
			throw ex;
		} finally {
			if (imageBuffer != null)
				imageBuffer.dispose();
		}
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 3) {
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String[] licenses = { "FingerClient", "FaceClient", "IrisClient" };
		//final String[] licenses = { "FingerFastExtractor", "FaceFastExtractor", "IrisFastExtractor" };

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

		String fileNameOut = args[0];
		BDIFEncodingType encoding = args[1].equals("1") ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;
		String fingerFileNameIn = args[2];
		String faceFileNameIn = args.length > 3 ? args[3] : null;
		String irisFileNameIn = args.length > 4 ? args[4] : null;

		ANTemplate antemplate = null;
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

			String tot = "TransactionType";
			String dai = "DestinationAgencyId";
			String ori = "OriginatingAgencyId";
			String tcn = "Transaction1";
			String src = "SourceAgencyName";

			antemplate = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, 0);

			ANTemplateGetRecordType2(antemplate, encoding);
			ANTemplateGetRecordType14(antemplate, fingerFileNameIn, src);
			if (faceFileNameIn != null)
				ANTemplateGetRecordType10(antemplate, faceFileNameIn, src);
			if (irisFileNameIn != null)
				ANTemplateGetRecordType17(antemplate, irisFileNameIn, src);
			antemplate.save(fileNameOut, encoding);

		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (antemplate != null)
				antemplate.dispose();
		}

	}
}
