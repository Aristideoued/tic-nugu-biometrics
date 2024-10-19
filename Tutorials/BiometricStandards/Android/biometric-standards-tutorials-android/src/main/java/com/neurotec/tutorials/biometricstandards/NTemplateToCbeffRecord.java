package com.neurotec.tutorials.biometricstandards;

import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.IOException;
import java.util.List;

import com.neurotec.biometrics.standards.BDIFTypes;
import com.neurotec.biometrics.standards.CBEFFBDBFormatIdentifiers;
import com.neurotec.biometrics.standards.CBEFFBiometricOrganizations;
import com.neurotec.biometrics.standards.CBEFFRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;

public class NTemplateToCbeffRecord extends BaseActivity {

	private static final String TAG = "NTemplateToCbeffRecord";
	private static final int REQUEST_CODE_GET_RECORD = 1;

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient", "PalmClient", "FaceClient", "IrisClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor", "PalmClient", "FaceFastExtractor", "IrisFastExtractor"};

	//=========================================================================

	private TextView mResult;
	private EditText mPatronFormat;
	private Button mLoadNTemplate;

	private void enableControls(final boolean enable) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mPatronFormat.setEnabled(enable);
				mLoadNTemplate.setEnabled(enable);
			}
		});
	}

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private boolean validateInput() {
		try {
			if (mPatronFormat.getText().toString().isEmpty()) {
				return false;
			}
			Integer.parseInt(mPatronFormat.getText().toString(), 16);
		} catch (NumberFormatException ex) {
			showMessage(getString(R.string.format_patron_format_not_valid, mPatronFormat.getText().toString()));
			return false;
		}
		return true;
	}

	private void getRecord() {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, BiometricStandardsTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, REQUEST_CODE_GET_RECORD);
	}

	private void convert(Uri recordUri) throws IOException {
		try {

			// Combine NTemplate BDB format
			int bdbFormat = BDIFTypes.makeFormat(CBEFFBiometricOrganizations.NEUROTECHNOLOGIJA, CBEFFBDBFormatIdentifiers.NEUROTECHNOLOGIJA_NTEMPLATE);

			// Get CBEFFRecord patron format
			// all supported patron formats can be found in CBEFFRecord class documentation
			int patronFormat = Integer.parseInt(mPatronFormat.getText().toString(), 16);

			// Read NTemplate buffer
			// Create CBEFFRecord from NTemplate buffer

			try (NBuffer packedCBEFFRecord = NBuffer.fromByteBuffer(IOUtils.toByteBuffer(this, recordUri));
				 CBEFFRecord cbeffRecord = new CBEFFRecord(bdbFormat, packedCBEFFRecord, patronFormat)) {

				// Save ANTemplate to file
				byte[] data;
				try (NBuffer templateBuffer = cbeffRecord.save()) {
					data = templateBuffer.toByteArray();
				}
				requestToSaveFile("cbeffrecord-from-ntemplate.dat", new OnSelectionListener() {
					@Override
					public void onFileSelected(Uri path) {
						try {
							saveDataToUri(NTemplateToCbeffRecord.this, path, data);
							showMessage(getString(R.string.format_converted_template_saved_to));
						} catch (IOException e) {
							showError(e);
						}
					}
				});
			}
		} catch (Exception e) {
			showMessage(getString(R.string.format_template_conversion_failed, e.toString()));
		}
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_ntemplate_to_cbeff_record);
		mPatronFormat = (EditText) findViewById(R.id.tutorials_field_1);
		mPatronFormat.setHint(getString(R.string.hint_patron_format));
		mLoadNTemplate = (Button) findViewById(R.id.tutorials_button_1);
		mLoadNTemplate.setText(R.string.msg_select_ntemplate);
		mLoadNTemplate.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				if (validateInput()) {
					getRecord();
				}
			}
		});
		mResult = (TextView) findViewById(R.id.tutorials_results);
		enableControls(false);
		new InitializationTask().execute();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (requestCode == REQUEST_CODE_GET_RECORD) {
			if (resultCode == RESULT_OK) {
				try {
					convert(data.getData());
				} catch (Exception e) {
					showMessage(e.toString());
					Log.e(TAG, "Exception", e);
				}
			}
		}
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		hideProgress();
	}

	final class InitializationTask extends AsyncTask<Object, Boolean, Boolean> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			showProgress(R.string.msg_obtaining_licenses);
		}

		@Override
		protected Boolean doInBackground(Object... params) {
			try {
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(NTemplateToCbeffRecord.this, LICENSES);
				if (obtainedLicenses.size() > 0) {
					showToast(R.string.msg_licenses_obtained);
					showProgress(R.string.msg_initialising);
					enableControls(true);
				} else {
					showToast(R.string.msg_no_licenses_obtained);
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
