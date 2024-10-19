package com.neurotec.tutorials.media;

import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.text.method.DigitsKeyListener;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.File;
import java.util.List;

import com.neurotec.images.NImage;
import com.neurotec.images.NImageFormat;
import com.neurotec.images.WSQInfo;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.NImageUtils;

public final class CreateWSQ extends BaseActivity {

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final String TAG = CreateWSQ.class.getSimpleName();
	private static final int REQUEST_CODE_GET_IMAGE = 345;

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
	private EditText mTextOutputFile;
	private EditText mTextBitRate;
	private Uri mSelectedFile;

	// ===========================================================
	// Private Methods
	// ===========================================================

	private void convertImage() {
		// Create an NImage from file
		// Create WSQInfo to store bit rate

		try (NImage image = NImageUtils.fromUri(this, mSelectedFile);
			 WSQInfo info = (WSQInfo) NImageFormat.getWSQ().createInfo(image)) {

			// Set specified bit rate (or default if bit rate was not specified)
			float bitrate;
			try {
				if (mTextBitRate.getText().toString() != null) {
					bitrate = Float.parseFloat(mTextBitRate.getText().toString());
				} else {
					bitrate = WSQInfo.DEFAULT_BIT_RATE;
				}
			} catch (NumberFormatException e) {
				bitrate = WSQInfo.DEFAULT_BIT_RATE;
			}

			info.setBitRate(bitrate);

			// Save image in WSQ format and bit rate to file
			File outputFile = new File(MediaTutorialsApp.TUTORIALS_OUTPUT_DATA_DIR, mTextOutputFile.getText().toString());

			image.save(outputFile.getAbsolutePath(), info);
			showMessage(String.format("WSQ image with bit rate %s was saved to %s", bitrate, outputFile.getAbsolutePath()));
		} catch (Exception e) {
			Log.e(TAG, "Exception", e);
			showMessage(e.getMessage());
		}
	}

	private void getImage() {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, MediaTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, REQUEST_CODE_GET_IMAGE);
	}

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	// ===========================================================
	// Protected Methods
	// ===========================================================

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_create_wsq);
		mButton = (Button) findViewById(R.id.tutorials_button_1);
		mButton.setText(getString(R.string.convert));
		mButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mResult.setText("");
				getImage();
			}
		});
		mResult = (TextView) findViewById(R.id.tutorials_results);

		mTextOutputFile = (EditText) findViewById(R.id.tutorials_field_1);
		mTextOutputFile.setHint("Output File name");
		mTextBitRate = (EditText) findViewById(R.id.tutorials_field_2);
		mTextBitRate.setHint("BitRate");
		mTextBitRate.setKeyListener(DigitsKeyListener.getInstance("0123456789."));

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
		if (requestCode == REQUEST_CODE_GET_IMAGE) {
			if (resultCode == RESULT_OK) {
				mSelectedFile = data.getData();
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(CreateWSQ.this, LICENSES);
				if (obtainedLicenses.size() == LICENSES.length) {
					showToast(R.string.msg_licenses_obtained);
					showProgress(R.string.msg_initialising);
					enableControls(true);
				} else {
					showToast(R.string.msg_licenses_partially_obtained);
				}
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
