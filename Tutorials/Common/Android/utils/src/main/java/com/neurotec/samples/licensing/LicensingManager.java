package com.neurotec.samples.licensing;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.neurotec.licensing.NLicense;
import com.neurotec.licensing.gui.LicensingPreferencesFragment;

public final class LicensingManager {

	// ===========================================================
	// Public nested class
	// ===========================================================

	public interface LicensingStateCallback {
		void onLicensingStateChanged(LicensingStateResult stateResult);
	}

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final String TAG = LicensingManager.class.getSimpleName();

	private static LicensingManager sInstance;

	// ===========================================================
	// Public static method
	// ===========================================================

	public static synchronized LicensingManager getInstance() {
		if (sInstance == null) {
			sInstance = new LicensingManager();
		}
		return sInstance;
	}

	// ===========================================================
	// Private constructor
	// ===========================================================

	private LicensingManager() {
	}

	// ===========================================================
	// Public methods
	// ===========================================================

	public void obtain(Context context, LicensingStateCallback callback, String[] licenses) {
		if (context == null) throw new NullPointerException("context");
		obtain(callback, licenses, LicensingPreferencesFragment.getServerAddress(context), LicensingPreferencesFragment.getServerPort(context));
	}

	public void obtain(final LicensingStateCallback callback, final String[] licenses, final String address, final int port) {
		if (callback == null) throw new NullPointerException("callback");
		new AsyncTask<Boolean, Boolean, LicensingStateResult>() {
			@Override
			protected void onPreExecute() {
				super.onPreExecute();
				callback.onLicensingStateChanged(new LicensingStateResult(LicensingState.OBTAINING));
			}
			@Override
			protected LicensingStateResult doInBackground(Boolean... params) {
				boolean obtained = false;
				Exception ex = null;
				try {
					obtained = obtain(licenses, address, port);
				} catch (Exception e) {
					ex = e;
				}
				return new LicensingStateResult(obtained ? LicensingState.OBTAINED : LicensingState.NOT_OBTAINED, ex);
			}
			@Override
			protected void onPostExecute(LicensingStateResult result) {
				super.onPostExecute(result);
				callback.onLicensingStateChanged(result);
			}
		}.execute();
	}

	public boolean obtain(Context context, String[] licenses) throws IOException {
		if (context == null) throw new NullPointerException("context");
		return obtain(licenses, LicensingPreferencesFragment.getServerAddress(context), LicensingPreferencesFragment.getServerPort(context));
	}

	public boolean obtain(String[] licenses, String address, int port) throws IOException {
		if (licenses == null) throw new NullPointerException("licenses");

		Log.i(TAG, String.format("Obtaining licenses from server %s:%s", address, port));

		boolean result = false;
		for (String license : licenses) {
			boolean available = NLicense.obtain(address, port, license);
			result |= available;
			Log.i(TAG, String.format("Obtaining '%s' license %s.", license, available ? "succeeded" : "failed"));
		}
		return result;
	}

	public List<String> obtainLicenses(Context context, String[] licenses) throws IOException {
		if (context == null) throw new NullPointerException("context");
		return obtainLicenses(LicensingPreferencesFragment.getServerAddress(context), LicensingPreferencesFragment.getServerPort(context), licenses);
	}

	public List<String> obtainLicenses(String address, int port, String[] licenses) throws IOException {
		if (licenses == null) throw new NullPointerException("licenses");
		List<String> obtainedLicenses = new ArrayList<String>();

		Log.i(TAG, String.format("Obtaining licenses from server %s:%s", address, port));

		boolean result = false;
		for (String license : licenses) {
			boolean available = NLicense.obtain(address, port, license);
			if (available) {
				obtainedLicenses.add(license);
			}
			Log.i(TAG, String.format("Obtaining '%s' license %s.", license, available ? "succeeded" : "failed"));
		}
		return obtainedLicenses;
	}

}
