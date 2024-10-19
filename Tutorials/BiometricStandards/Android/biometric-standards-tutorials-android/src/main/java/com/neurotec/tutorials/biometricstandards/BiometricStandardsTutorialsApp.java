package com.neurotec.tutorials.biometricstandards;

import android.app.Application;
import android.util.Log;

import com.neurotec.licensing.NLicenseManager;
import com.neurotec.licensing.gui.LicensingPreferencesFragment;
import com.neurotec.samples.util.EnvironmentUtils;

public final class BiometricStandardsTutorialsApp extends Application {

	private static final String TAG = BiometricStandardsTutorialsApp.class.getSimpleName();
	private static final String OUTPUT_DIR_NAME = "output";

	public static final String APP_NAME = "biometric-standards-tutorials";
	public static final String TUTORIALS_OUTPUT_DATA_DIR = EnvironmentUtils.getDataDirectory(EnvironmentUtils.SAMPLE_DATA_DIR_NAME, APP_NAME, OUTPUT_DIR_NAME).getAbsolutePath();

	public static final String TUTORIALS_ASSET_DIRECTORY = "input";

	@Override
	public void onCreate() {
		super.onCreate();

		try {
			NLicenseManager.setTrialMode(LicensingPreferencesFragment.isUseTrial(this));
			System.setProperty("jna.nounpack", "true");
			System.setProperty("java.io.tmpdir", getCacheDir().getAbsolutePath());
		} catch (Exception e) {
			Log.e(TAG, "Exception", e);
		}
	}

}
