package com.neurotec.tutorials.biometricstandards;

import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.List;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FIRFingerView;
import com.neurotec.biometrics.standards.FIRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;

public final class FIRecordToNTemplate extends BaseActivity {

	private static final String TAG = FIRecordToNTemplate.class.getSimpleName();
	private static final int REQUEST_CODE_GET_RECORD = 1;

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor"};

	//=========================================================================

	private Button mButton;
	private TextView mResult;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_firecord_to_ntemplate);
		mButton = (Button) findViewById(R.id.tutorials_button_1);
		mButton.setText(R.string.msg_select_firecord);
		mButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				getRecord();
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

	private void convert(Uri recordUri) throws IOException {
		ByteBuffer fiRecordData = IOUtils.toByteBuffer(this, recordUri);

		try (FIRecord fiRecord = new FIRecord(fiRecordData, BDIFStandard.ISO);
			 NBiometricClient biometricClient = new NBiometricClient();
			 NSubject subject = new NSubject()) {

			for (FIRFingerView fv : fiRecord.getFingerViews()) {
				NFinger finger = new NFinger();
				finger.setImage(fv.toNImage());
				subject.getFingers().add(finger);
			}

			// Extract template
			NBiometricStatus status = biometricClient.createTemplate(subject);
			if (status == NBiometricStatus.OK) {
				// Save converted template to file
				byte[] data;
				try (NBuffer templateBuffer = subject.getTemplateBuffer()) {
					data = templateBuffer.toByteArray();
				}
				requestToSaveFile("ntemplate-from-firecord.dat", new OnSelectionListener() {
					@Override
					public void onFileSelected(Uri path) {
						try {
							saveDataToUri(FIRecordToNTemplate.this, path, data);
							showMessage(getString(R.string.format_converted_template_saved_to));
						} catch (IOException e) {
							showError(e);
						}
					}
				});
			} else {
				showMessage(getString(R.string.format_template_creation_failed_with_status, status));
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(FIRecordToNTemplate.this, LICENSES);
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
