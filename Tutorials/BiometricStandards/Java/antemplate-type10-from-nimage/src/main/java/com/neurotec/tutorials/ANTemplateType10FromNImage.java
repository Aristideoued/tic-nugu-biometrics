package com.neurotec.tutorials;

import java.io.IOException;

import com.neurotec.biometrics.standards.ANDistortion;
import com.neurotec.biometrics.standards.ANDistortionCode;
import com.neurotec.biometrics.standards.ANDistortionMeasurementCode;
import com.neurotec.biometrics.standards.ANDistortionSeverityCode;
import com.neurotec.biometrics.standards.ANImageType;
import com.neurotec.biometrics.standards.ANLightingArtifact;
import com.neurotec.biometrics.standards.ANSubjectPose;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANTieredMarkupCollection;
import com.neurotec.biometrics.standards.ANType10Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.biometrics.standards.BDIFFacePostAcquisitionProcessing;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ANTemplateType10FromNImage {

	private static final String DESCRIPTION = "Demonstrates creation of ANTemplate with type 10 record in it.";
	private static final String NAME = "antemplate-type10-from-nimage";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [Image] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Src] [Encoding]%n", NAME);
		System.out.println("");
		System.out.println("\t[Image]     - filename with Image file.");
		System.out.println("\t[ANTemplate] - filename for ANTemplate.");
		System.out.println("\t[Tot] - specifies type of transaction.");
		System.out.println("\t[Dai] - specifies destination agency identifier.");
		System.out.println("\t[Ori] - specifies originating agency identifier.");
		System.out.println("\t[Tcn] - specifies transaction control number.");
		System.out.println("\t[Src] - specifies source agency number.");
		System.out.println("\t[Encoding] - specifies ANTemplate encoding type.");
		System.out.println("\t\t0 - Traditional binary encoding.");
		System.out.println("\t\t1 - NIEM-conformant XML encoding.");
		System.out.println("");
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length != 8) {
			usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "FaceClient";
		//final String license = "FaceFastExtractor";

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

		ANTemplate template = null;
		ANType10Record record = null;
		NBuffer imgBuffer = null;
		ANImageType imt = ANImageType.FACE;

		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String tot = args[2]; 	// type of transaction
			String dai = args[3]; 	// destination agency identifier
			String ori = args[4]; 	// originating agency identifier
			String tcn = args[5]; 	// transaction control number
			String src = args[6]; 	// source agency number
			String enc = args[7];	// encoding type

			if ((tot.length() < 3) || (tot.length() > 4)) {
				System.out.println("Tot parameter should be 3 or 4 characters length.");
				System.exit(-1);
			}

			BDIFEncodingType encoding = enc.equals("1") ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;
			imgBuffer = NFile.readAllBytes(args[0]);

			/* 
			 * Create empty ANTemplate object with current version and only type 1 record in it.
			 * Finger image must be compressed using valid compression algorithm for Type-10 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			*/
			template = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, 0);

			// Create Type 10 record and add record to ANTemplate
			record = template.getRecords().addType10(imt, src, imgBuffer);
			
			if (imt == ANImageType.FACE) {
				// Sets additional optional fields for face modality
				ANDistortion distortion = new ANDistortion(ANDistortionCode.BARREL, ANDistortionMeasurementCode.ESTIMATED, ANDistortionSeverityCode.MILD);
				record.setDistortion(distortion);
				record.getLightingArtifacts().add(ANLightingArtifact.FACE_SHADOWS);
				record.setSubjectPose(ANSubjectPose.FULL_FACE_FRONTAL);
				record.setTieredMarkupCollection(ANTieredMarkupCollection.EYE_CENTERS);
				record.setImageTransformation(BDIFFacePostAcquisitionProcessing.values()[BDIFFacePostAcquisitionProcessing.POSE_CORRECTED.ordinal()| BDIFFacePostAcquisitionProcessing.CONTRAST_STRETCHED.ordinal()]);
			}

			// Storing ANTemplate object in file
			template.save(args[1], encoding);
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (record != null) record.dispose();
			if (template != null) template.dispose();
			if (imgBuffer != null) imgBuffer.dispose();
		}
	}
}
