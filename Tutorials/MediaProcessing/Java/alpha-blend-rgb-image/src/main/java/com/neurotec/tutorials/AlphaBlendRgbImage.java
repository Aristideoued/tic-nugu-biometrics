package com.neurotec.tutorials;

import com.neurotec.images.NImage;
import com.neurotec.images.NPixelFormat;
import com.neurotec.images.processing.NRGBIP;
import com.neurotec.lang.NThrowable;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class AlphaBlendRgbImage {

	private static final String DESCRIPTION = "Demonstrates rgb image alpha blending";
	private static final String NAME = "alpha-blend-rgb-image";
	private static final String VERSION = "13.1.0.0";

	static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [imageA] [imageB] [alpha] [output image]%n", NAME);
		System.out.format("\texample: %s c:\\image1.bmp c:\\image2.bmp 0.5 c:\\result.bmp%n", NAME);
		System.out.println("\tnote: images must be of the same width and height");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 4) {
			usage();
			System.exit(-1);
		}

		NImage imageA = null;
		NImage imageB = null;
		NImage rgbImageA = null;
		NImage rgbImageB = null;
		NImage result = null;
		try {
			double alpha = Double.parseDouble(args[2]);

			// Open images
			imageA = NImage.fromFile(args[0]);
			imageB = NImage.fromFile(args[1]);

			// Convert images to rgb
			rgbImageA = NImage.fromImage(NPixelFormat.RGB_8U, 0, imageA);
			rgbImageB = NImage.fromImage(NPixelFormat.RGB_8U, 0, imageB);

			// Alpha blend
			result = NRGBIP.alphaBlend(rgbImageA, rgbImageB, alpha);
			result.save(args[3]);
			System.out.format("Image saved to \"%s\"", args[3]);
		} catch (Throwable th) {
			th.printStackTrace();

			int errorCode = -1;

			if (th instanceof NThrowable) {
				errorCode = ((NThrowable)th).getCode();
			}

			System.exit(errorCode);
		} finally {
			if (imageA != null) imageA.dispose();
			if (imageB != null) imageB.dispose();
			if (rgbImageA != null) rgbImageA.dispose();
			if (rgbImageB != null) rgbImageB.dispose();
			if (result != null) result.dispose();
		}
	}
}
