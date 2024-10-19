package com.neurotec.tutorials;

import com.neurotec.images.NImage;
import com.neurotec.images.NPixelFormat;
import com.neurotec.images.processing.NGIP;
import com.neurotec.lang.NThrowable;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class InvertGrayscaleImage {

	private static final String DESCRIPTION = "Demonstrates grayscale image invertion";
	private static final String NAME = "invert-grayscale-image";
	private static final String VERSION = "13.1.0.0";

	static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [image] [output image]%n", NAME);
		System.out.println("\t[image] - image to invert");
		System.out.println("\t[output image] - inverted image");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();
		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 2) {
			usage();
			System.exit(-1);
		}

		NImage image = null;
		NImage grayscaleImage = null;
		NImage result = null;
		try {
			// Open image
			image = NImage.fromFile(args[0]);

			// Convert to grayscale image
			grayscaleImage = NImage.fromImage(NPixelFormat.GRAYSCALE_8U, 0, image);

			// Invert image
			result = NGIP.invert(grayscaleImage);
			result.save(args[1]);
			System.out.format("Inverted image saved to \"%s\"", args[1]);
		} catch (Throwable th) {
			th.printStackTrace();

			int errorCode = -1;

			if (th instanceof NThrowable) {
				errorCode = ((NThrowable)th).getCode();
			}

			System.exit(errorCode);
		} finally {
			if (image != null) image.dispose();
			if (grayscaleImage != null) grayscaleImage.dispose();
			if (result != null) result.dispose();
		}
	}
}
