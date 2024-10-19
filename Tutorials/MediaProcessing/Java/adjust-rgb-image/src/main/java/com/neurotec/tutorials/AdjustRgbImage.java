package com.neurotec.tutorials;

import com.neurotec.images.NImage;
import com.neurotec.images.NPixelFormat;
import com.neurotec.images.processing.NRGBIP;
import com.neurotec.lang.NThrowable;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class AdjustRgbImage {

	private static final String DESCRIPTION = "Demonstrates how to adjust brightness and contrast of rgb image";
	private static final String NAME = "adjust-rgb-image";
	private static final String VERSION = "13.1.0.0";

	static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [image] [output image] [red brightness] [red contrast] [green brightness] [green contrast] [blue brightness] [blue contrast]%n", NAME);
		System.out.format("\texample: %s c:\\input.bmp c:\\result.bmp 0.5 0.5 0.2 0.3 1 0.9%n", NAME);
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME,VERSION, args);

		if (args.length < 8) {
			usage();
			System.exit(-1);
		}

		NImage image = null;
		NImage rgbImage = null;
		NImage result = null;
		try {
			double redBrightness = Double.parseDouble(args[2]);
			double redContrast = Double.parseDouble(args[3]);
			double greenBrightness = Double.parseDouble(args[4]);
			double greenContrast = Double.parseDouble(args[5]);
			double blueBrightness = Double.parseDouble(args[6]);
			double blueContrast = Double.parseDouble(args[7]);

			// Open image
			image = NImage.fromFile(args[0]);

			// Convert to rgb
			rgbImage = NImage.fromImage(NPixelFormat.RGB_8U, 0, image);

			// Adjust brightness and contrast
			result = NRGBIP.adjustBrightnessContrast(rgbImage, redBrightness, redContrast, greenBrightness, greenContrast, blueBrightness, blueContrast);
			result.save(args[1]);
			System.out.format("Result image saved to \"%s\"", args[1]);
		} catch (Throwable th) {
			th.printStackTrace();

			int errorCode = -1;

			if (th instanceof NThrowable) {
				errorCode = ((NThrowable)th).getCode();
			}

			System.exit(errorCode);
		} finally {
			if (image != null) image.dispose();
			if (rgbImage != null) rgbImage.dispose();
			if (result != null) result.dispose();
		}
	}
}
