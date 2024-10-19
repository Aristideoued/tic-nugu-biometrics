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
import java.nio.ByteBuffer;
import java.util.List;

import com.neurotec.biometrics.NFTemplate;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FMRFingerView;
import com.neurotec.biometrics.standards.FMRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;
import com.neurotec.util.NVersion;

public final class NTemplateToFMRecord extends BaseActivity {

	private static final String TAG = NTemplateToFMRecord.class.getSimpleName();
	private static final int REQUEST_CODE_GET_TEMPLATE = 1;

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor"};

	//=========================================================================

	private EditText mFieldStandard;
	private EditText mFieldFlag;
	private EditText mFieldVersion;
	private EditText mFieldEncoding;
	private Button mButton;
	private TextView mResult;
	private BDIFStandard mStandard;
	private int mFlag;
	private BDIFEncodingType mEncodingType;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_ntemplate_to_fmrecord);
		mFieldStandard = (EditText) findViewById(R.id.tutorials_field_1);
		mFieldStandard.setHint(R.string.hint_standard_iso_ansi);
		mFieldFlag = (EditText) findViewById(R.id.tutorials_field_2);
		mFieldFlag.setHint(R.string.hint_flag_use_neurotec_fields);
		mFieldVersion = (EditText) findViewById(R.id.tutorials_field_3);
		mFieldVersion.setHint(R.string.hint_fm_record_version);
		mFieldEncoding = (EditText) findViewById(R.id.tutorials_field_4);
		mFieldEncoding.setHint(R.string.hint_fm_record_encoding);
		mButton = (Button) findViewById(R.id.tutorials_button_1);
		mButton.setText(R.string.msg_select_ntemplate);
		mButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				if (validateInput()) {
					getTemplate();
				}
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
		super.onActivityResult(requestCode, resultCode, data);
		if (requestCode == REQUEST_CODE_GET_TEMPLATE) {
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

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private void getTemplate() {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, BiometricStandardsTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, REQUEST_CODE_GET_TEMPLATE);
	}

	private boolean validateInput() {
		String standard = mFieldStandard.getText().toString();
		if (standard.equalsIgnoreCase(getString(R.string.standard_iso))) {
			mStandard = BDIFStandard.ISO;
		} else if (standard.equalsIgnoreCase(getString(R.string.standard_ansi))) {
			mStandard = BDIFStandard.ANSI;
		} else {
			showMessage(getString(R.string.format_unknown_standard, standard));
			return false;
		}

		try {
			mFlag = Integer.parseInt(mFieldFlag.getText().toString());
		} catch (NumberFormatException e) {
			showMessage(getString(R.string.format_flag_not_valid, mFieldFlag.getText().toString()));
			return false;
		}

		try {
			mEncodingType = Integer.parseInt(mFieldEncoding.getText().toString()) == 1 ? BDIFEncodingType.XML : BDIFEncodingType.TRADITIONAL;
		} catch (NumberFormatException e) {
			showMessage(getString(R.string.format_flag_not_valid, mFieldEncoding.getText().toString()));
			return false;
		}

		return true;
	}

	private void convert(Uri ntemplateUri) throws IOException {
		NVersion version;
		ByteBuffer packedNTemplate = IOUtils.toByteBuffer(this, ntemplateUri);

		// Create NTemplate object from packed NTemplate
		// Retrieve NFTemplate object from NTemplate object

		try (NTemplate nTemplate = new NTemplate(packedNTemplate);
			 NFTemplate nfTemplate = nTemplate.getFingers()) {
			float versionNumber = Float.parseFloat(mFieldVersion.getText().toString());
			if (versionNumber == 2) {
				version = (mStandard == BDIFStandard.ANSI) ? FMRecord.VERSION_ANSI_20 : FMRecord.VERSION_ISO_20;
			} else if (versionNumber == 3) {
				if (mStandard != BDIFStandard.ISO) {
					throw new IllegalArgumentException("Standard and version is incompatible");
				}
				version = FMRecord.VERSION_ISO_30;
			} else if (versionNumber == 3.5) {
				if (mStandard != BDIFStandard.ANSI) {
					throw new IllegalArgumentException("Standard and version is incompatible");
				}
				version = FMRecord.VERSION_ANSI_35;
			} else {
				showMessage(getString(R.string.format_version_not_valid, mFieldVersion.getText().toString()));
				return;
			}

			if (nfTemplate != null) {

				// Create FMRecord object from NFTemplate object
				// Store FMRecord object in memory

				byte[] data;
				try (FMRecord fmRecord = new FMRecord(nfTemplate, mStandard, version);
					 NBuffer storedFmRecord = (mFlag == 1)
							 ? fmRecord.save(mEncodingType, FMRFingerView.FLAG_USE_NEUROTEC_FIELDS)
							 : fmRecord.save(mEncodingType)) {

					// Save converted template to file
					data = storedFmRecord.toByteArray();
				}
				requestToSaveFile("fmrecord-from-ntemplate.dat", new OnSelectionListener() {
					@Override
					public void onFileSelected(Uri path) {
						try {
							saveDataToUri(NTemplateToFMRecord.this, path, data);
							showMessage(getString(R.string.format_fmrecord_saved_to));
						} catch (IOException e) {
							showError(e);
						}
					}
				});
			} else {
				showMessage(getString(R.string.msg_no_nfrecords_in_ntemplate));
			}
		}
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(NTemplateToFMRecord.this, LICENSES);
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
