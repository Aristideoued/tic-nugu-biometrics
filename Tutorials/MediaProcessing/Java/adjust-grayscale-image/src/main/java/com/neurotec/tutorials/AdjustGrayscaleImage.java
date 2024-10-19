package com.neurotec.tutorials;

import com.neurotec.images.NImage;
import com.neurotec.images.NPixelFormat;
import com.neurotec.images.processing.NGIP;
import com.neurotec.lang.NThrowable;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class AdjustGrayscaleImage {

	private static final String DESCRIPTION = "Demonstrates how to adjust brightness and contrast of grayscale image";
	private static final String NAME = "adjust-grayscale-image";
	private static final String VERSION = "13.1.0.0";

	static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [image] [brightness] [contrast] [output image]%n", NAME);
		System.out.format("\texample: %s c:\\image.jpg 0.3 0.5 c:\\result.jpg%n", NAME);
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 4) {
			usage();
			System.exit(-1);
		}

		NImage image = null;
		NImage grayscaleImage = null;
		NImage result = null;
		try {
			double brightness = Double.parseDouble(args[1]);
			double contrast = Double.parseDouble(args[2]);

			// Open image
			image = NImage.fromFile(args[0]);

			// Convert to grayscale
			grayscaleImage = NImage.fromImage(NPixelFormat.GRAYSCALE_8U, 0, image);

			// Adjust brightness and contrast
			result = NGIP.adjustBrightnessContrast(grayscaleImage, brightness, contrast);
			result.save(args[3]);
			System.out.format("Result image saved to \"%s\"", args[3]);
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
