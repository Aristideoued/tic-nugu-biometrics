package com.neurotec.tutorials;

import java.io.IOException;
import java.util.EnumSet;

import com.neurotec.devices.NDevice;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NMicrophone;
import com.neurotec.lang.NCore;
import com.neurotec.lang.NThrowable;
import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.sound.NSoundBuffer;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class SoundCapture {

	private static final String DESCRIPTION = "Demonstrates sound sample capturing from microphone";
	private static final String NAME = "sound-capture";
	private static final String VERSION = "13.1.0.0";

	private static void Usage() {
		System.out.println("usage:");
		System.out.format("\t{%s [bufferCount]%n", NAME);
		System.out.println();
		System.out.println("\tbufferCount - number of sound buffers to capture from each microphone");
		System.out.println();
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 1) {
			Usage();
			System.exit(1);
		}

		//=========================================================================
		// CHOOSE LICENCES !!!
		//=========================================================================
		// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		// If you are using a TRIAL version - choose any of them.

		final String license = "VoiceExtractor";
		//final String license = "VoiceClient";
		//final String license = "VoiceFastExtractor";

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

		NDeviceManager deviceManager = null;
		try {
			// Obtain license
			if (!NLicense.obtain("/local", 5000, license)) {
				System.err.format("Could not obtain license: %s%n", license);
				System.exit(-1);
			}

			int bufferCount = Integer.parseInt(args[0]);
			if (bufferCount == 0) {
				System.err.println("No sound buffers will be captured as sound buffer count is not specified");
				System.exit(-1);
			}
			deviceManager = new NDeviceManager();
			deviceManager.setDeviceTypes(EnumSet.of(NDeviceType.MICROPHONE));
			deviceManager.setAutoPlug(true);
			deviceManager.initialize();
			System.out.format("Device manager created. Found microphones: %s%n", deviceManager.getDevices().size());

			for (NDevice device : deviceManager.getDevices()) {
				NMicrophone microphone = (NMicrophone) device;
				System.out.format("Found microphone %s", microphone.getDisplayName());
				microphone.startCapturing();

				if (bufferCount > 0) {
					System.out.println(", capturing");
					for (int i = 0; i < bufferCount; i++) {
						NSoundBuffer soundSample = microphone.getSoundSample();
						System.out.format("Sample buffer received. sample rate: %s, sample length: %s%n", soundSample.getSampleRate(), soundSample.getLength());

						System.out.print(" ... ");
					}
					System.out.print(" Done");
					System.out.println();
				}
				microphone.stopCapturing();
			}
			System.out.println("Done");
		} catch (Throwable th) {
			Utils.handleError(th);
		} finally {
			if (deviceManager != null) deviceManager.dispose();
			NCore.shutdown();
		}
	}
}
