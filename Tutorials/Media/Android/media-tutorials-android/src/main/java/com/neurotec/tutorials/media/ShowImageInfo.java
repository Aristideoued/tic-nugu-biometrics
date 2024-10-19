package com.neurotec.tutorials.media;

import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.List;

import com.neurotec.images.JPEG2KInfo;
import com.neurotec.images.JPEGInfo;
import com.neurotec.images.NImage;
import com.neurotec.images.NImageFormat;
import com.neurotec.images.PNGInfo;
import com.neurotec.images.WSQInfo;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.NImageUtils;

public final class ShowImageInfo extends BaseActivity {

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final String TAG = ShowImageInfo.class.getSimpleName();
	private static final int REQUEST_CODE_GET_FILE = 1;

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor"};

	//=========================================================================

	// ===========================================================
	// Private fields
	// ===========================================================

	private Button mButton;
	private TextView mResult;
	private Uri mSelectedFile;

	// ===========================================================
	// Private Methods
	// ===========================================================

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private void getImage() {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, MediaTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, REQUEST_CODE_GET_FILE);
	}

	private void convertImage() {
		// Create NImage from file
		// Get image format

		try (NImage image = NImageUtils.fromUri(this, mSelectedFile);
			 NImageFormat format = image.getInfo().getFormat()) {

			// Print format specific info
			if (NImageFormat.getJPEG2K().equals(format)) {
				JPEG2KInfo info = (JPEG2KInfo) image.getInfo();
				showMessage("Profile: " + info.getProfile());
				showMessage("Compression ratio: " + info.getRatio());
			} else if (NImageFormat.getJPEG().equals(format)) {
				JPEGInfo info = (JPEGInfo) image.getInfo();
				showMessage("Lossless: " + info.isLossless());
				showMessage("Quality: " + info.getQuality());
			} else if (NImageFormat.getPNG().equals(format)) {
				PNGInfo info = (PNGInfo) image.getInfo();
				showMessage("Compression level: " + info.getCompressionLevel());
			} else if (NImageFormat.getWSQ().equals(format)) {
				WSQInfo info = (WSQInfo) image.getInfo();
				showMessage("Bit rate: " + info.getBitRate());
				showMessage("Implementation number: " + info.getImplementationNumber());
			}
		} catch (Exception e) {
			Log.e(TAG, "", e);
			showMessage("Exception: " + e.getMessage());
		}
	}

	// ===========================================================
	// Protected Methods
	// ===========================================================

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_show_image_info);
		mButton = (Button) findViewById(R.id.tutorials_button_1);
		mButton.setText(getString(R.string.get_info));
		mButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mResult.setText("");
				getImage();
			}
		});
		mResult = (TextView) findViewById(R.id.tutorials_results);
		enableControls(false);
		new InitializationTask().execute();
	}

	private void enableControls(final boolean enable) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mButton.setEnabled(enable);
			}
		});
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		hideProgress();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == REQUEST_CODE_GET_FILE) {
			if (resultCode == RESULT_OK) {
				mSelectedFile = data.getData();
				mResult.setText("");
				convertImage();
			}
		}
	}

	// ===========================================================
	// Public Methods
	// ===========================================================

	final class InitializationTask extends AsyncTask<Object, Boolean, Boolean> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			showProgress(R.string.msg_obtaining_licenses);
		}

		@Override
		protected Boolean doInBackground(Object... params) {
			try {
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(ShowImageInfo.this, LICENSES);
				if (obtainedLicenses.size() == LICENSES.length) {
					showToast(R.string.msg_licenses_obtained);
					showProgress(R.string.msg_initialising);
				} else {
					showToast(R.string.msg_licenses_partially_obtained);
				}
				enableControls(true);
			} catch (Exception e) {
				showError(e.getMessage(), false);
			}
			return true;
		}

		@Override
		protected void onPostExecute(Boolean result) {
			super.onPostExecute(result);
			hideProgress();
		}
	}

}
