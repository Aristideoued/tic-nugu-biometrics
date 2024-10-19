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

import com.neurotec.biometrics.NTemplate;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FMRFingerView;
import com.neurotec.biometrics.standards.FMRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;

public final class FMRecordToNTemplate extends BaseActivity {

	private static final String TAG = FMRecordToNTemplate.class.getSimpleName();
	private static final int REQUEST_CODE_GET_RECORD = 1;

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
	private Button mButton;
	private TextView mResult;
	private BDIFStandard mStandard;
	private int mFlag;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_fmrecord_to_ntemplate);
		mFieldStandard = (EditText) findViewById(R.id.tutorials_field_1);
		mFieldStandard.setHint(R.string.hint_standard_iso_ansi);
		mFieldFlag = (EditText) findViewById(R.id.tutorials_field_2);
		mFieldFlag.setHint(R.string.hint_flag_use_neurotec_fields);
		mButton = (Button) findViewById(R.id.tutorials_button_1);
		mButton.setText(R.string.msg_select_fmrecord);
		mButton.setOnClickListener(new View.OnClickListener() {
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

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private void getRecord() {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, BiometricStandardsTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, REQUEST_CODE_GET_RECORD);
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

		return true;
	}

	private void convert(Uri recordUri) throws IOException {

		// Create FMRecord object from FMRecord stored in memory
		// Convert FMRecord object to NTemplate object

		try (FMRecord fmRecord = (mFlag == 1)
				? new FMRecord(NBuffer.fromByteBuffer(IOUtils.toByteBuffer(this, recordUri)), FMRFingerView.FLAG_USE_NEUROTEC_FIELDS, mStandard)
				: new FMRecord(IOUtils.toByteBuffer(this, recordUri), mStandard);
			 NTemplate nTemplate = fmRecord.toNTemplate()) {

			// Save converted template to file
			byte[] data;
			try (NBuffer templateBuffer = nTemplate.save()) {
				data = templateBuffer.toByteArray();
			}
			requestToSaveFile("ntemplate-from-fmrecord.dat", new OnSelectionListener() {
				@Override
				public void onFileSelected(Uri path) {
					try {
						saveDataToUri(FMRecordToNTemplate.this, path, data);
						showMessage(getString(R.string.format_converted_template_saved_to));
					} catch (IOException e) {
						showError(e);
					}
				}
			});
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(FMRecordToNTemplate.this, LICENSES);
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
