package com.neurotec.tutorials;

import com.neurotec.geometry.NInterpolationMode;
import com.neurotec.images.NImage;
import com.neurotec.images.NPixelFormat;
import com.neurotec.images.processing.NGIP;
import com.neurotec.lang.NThrowable;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ScaleGrayscaleImage {

	private static final String DESCRIPTION = "Demonstrates grayscale image scaling";
	private static final String NAME = "scale-grayscale-image";
	private static final String VERSION = "13.1.0.0";

	static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [image] [width] [height] [output image] [interpolation mode]%n", NAME);
		System.out.println("\t[image] - image to scale");
		System.out.println("\t[width] - scaled image width");
		System.out.println("\t[height] - scaled image height");
		System.out.println("\t[output image] - scaled image");
		System.out.println("\t[interpolation mode] - (optional) interpolation mode to use: 0 - nearest neighbour, 1 - bilinear");
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
			int dstWidth = Integer.parseInt(args[1]);
			int dstHeight = Integer.parseInt(args[2]);
			NInterpolationMode interpolationMode = NInterpolationMode.NEAREST_NEIGHBOR;
			if (args.length >= 5 && args[4] == "1") interpolationMode = NInterpolationMode.BILINEAR;

			// Open image
			image = NImage.fromFile(args[0]);

			// Convert image to grayscale
			grayscaleImage = NImage.fromImage(NPixelFormat.GRAYSCALE_8U, 0, image);

			// Scale image
			result = NGIP.scale(grayscaleImage, dstWidth, dstHeight, interpolationMode);
			result.save(args[3]);
			System.out.format("Scaled image saved to \"%s\"", args[3]);
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
