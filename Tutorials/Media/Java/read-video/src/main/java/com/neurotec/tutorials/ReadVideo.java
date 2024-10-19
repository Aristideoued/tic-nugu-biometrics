package com.neurotec.tutorials;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.images.NImage;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.media.NAudioFormat;
import com.neurotec.media.NMediaFormat;
import com.neurotec.media.NMediaReader;
import com.neurotec.media.NMediaSource;
import com.neurotec.media.NMediaType;
import com.neurotec.media.NVideoFormat;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class ReadVideo {

	private static final String DESCRIPTION = "Demonstrates reading frames from specified filename or url";
	private static final String NAME = "read-video";
	private static final String VERSION = "13.1.0.0";

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s [source] [frameCount] <optional: is url>%n", NAME);
		System.out.println();
		System.out.println("\tsource - filename or url frames should be captured from.");
		System.out.println("\tframeCount - number of frames to capture from specified filename or url.");
		System.out.println("\tis url - specifies that passed source parameter is url (value: 1) or filename (value: 0).");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 2) {
			usage();
			System.exit(-1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "FaceExtractor";
		//final String license = "FaceClient";
		//final String license = "FaceFastExtractor";
		//final String license = "SentiVeillance";
		//final String license = "SentiMask";

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

		NMediaSource mediaSource = null;
		NMediaReader mediaReader = null;
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			String uri = args[0];
			boolean isUrl = false;
			int frameCount = Integer.parseInt(args[1]);
			if (frameCount <= 0) {
				System.err.println("No frames will be captured as frame count is not specified");
			}

			if (args.length > 2) {
				isUrl = args[2] == "1";
			}

			// Create media source
			mediaSource = (isUrl) ? NMediaSource.fromUrl(uri) : NMediaSource.fromFile(uri);
			System.out.format("Display name: %s\n", mediaSource.getDisplayName());

			mediaReader = new NMediaReader(mediaSource, EnumSet.of(NMediaType.VIDEO), true);
			readFrames(mediaReader, frameCount);
			System.out.println("Done");
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (mediaSource != null) mediaSource.dispose();
			if (mediaReader != null) mediaReader.dispose();
		}
	}

	private static void readFrames(NMediaReader mediaReader, int frameCount) throws Exception {
		NMediaSource mediaSource = mediaReader.getSource();
		System.out.format("Media length: %s\n", mediaReader.getLength());
		NMediaFormat[] mediaFormats = mediaSource.getFormats(NMediaType.VIDEO);
		if (mediaFormats == null) {
			System.out.println("Formats are not yet available (should be available after media reader is started");
		} else {
			System.out.format("Format count: %s\n", mediaFormats.length);
			for (int i = 0; i < mediaFormats.length; i++) {
				System.out.format("[%s] ", i);
				dumpMediaFormat(mediaFormats[i]);
			}
		}

		NMediaFormat currentMediaFormat = mediaSource.getCurrentFormat(NMediaType.VIDEO);
		if (currentMediaFormat != null) {
			System.out.println("Current media format:");
			dumpMediaFormat(currentMediaFormat);

			if (mediaFormats != null) {
				System.out.println("Set the last supported format (optional) ... ");
				mediaSource.setCurrentFormat(NMediaType.VIDEO, mediaFormats[mediaFormats.length - 1]);
			}
		} else
			System.out.println("Current media format is not yet available (will be available after media reader start)");

		System.out.print("Starting capture ... ");
		mediaReader.start();
		System.out.println("Capture started");

		try {
			currentMediaFormat = mediaSource.getCurrentFormat(NMediaType.VIDEO);
			if (currentMediaFormat == null) throw new Exception("Current media format is not set even after media reader start!");
			System.out.println("Capturing with format: ");
			dumpMediaFormat(currentMediaFormat);

			for (int i = 0; i < frameCount; i++) {

				NMediaReader.ReadResult result = mediaReader.readVideoSample();
				NImage image = result.getImage();
				if (result.getImage() == null) return; // end of stream

				String filename = String.format("{%d4}.jpg", i);
				image.save(filename);

				System.out.format("[%s %s] %s\n", result.getTimeStamp(), result.getDuration(), filename);
			}
		} finally {
			mediaReader.stop();
		}
	}

	private static void dumpMediaFormat(NMediaFormat mediaFormat) {
		if (mediaFormat == null) throw new NullPointerException("mediaFormat");
		switch (mediaFormat.getMediaType()) {
		case VIDEO:
			NVideoFormat videoFormat = (NVideoFormat) mediaFormat;
			System.out.format("Video format .. %sx%s @ %s/%s (interlace: %s, aspect ratio: %s/%s)\n", videoFormat.getWidth(), videoFormat.getHeight(), videoFormat.getFrameRate().numerator, videoFormat.getFrameRate().denominator, videoFormat.getInterlaceMode(), videoFormat.getPixelAspectRatio().numerator, videoFormat.getPixelAspectRatio().denominator);
			break;
		case AUDIO:
			NAudioFormat audioFormat = (NAudioFormat) mediaFormat;
			System.out.format("Audio format .. channels: %s, samples/second: %s, bits/channel: %s\n", audioFormat.getChannelCount(), audioFormat.getSampleRate(), audioFormat.getBitsPerChannel());
			break;
		default:
			throw new IllegalArgumentException("Unknown media type specified in format!");
		}
	}
}
