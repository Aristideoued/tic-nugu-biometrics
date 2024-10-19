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
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.neurotec.biometrics.standards.CBEFFRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;

public class UnpackComplexCbeffRecord extends BaseActivity {

	private static final String TAG = "UnpackComplexCbeff";
	private static final int REQUEST_CODE_GET_RECORD = 1;

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient", "PalmClient", "FaceClient", "IrisClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor", "PalmClient", "FaceFastExtractor", "IrisFastExtractor"};

	//=========================================================================

	private static final Map<Integer, BdbFormat> lookup = new HashMap<Integer, BdbFormat>();

	static {
		for (BdbFormat v : BdbFormat.values()) {
			lookup.put(v.value, v);
		}
	}

	private enum BdbFormat {
		AN_TEMPLATE(0x001B8019),
		FC_RECORD_ANSI(0x001B0501),
		FC_RECORD_ISO(0x01010008),
		FI_RECORD_ANSI(0x001B0401),
		FI_RECORD_ISO(0x01010007),
		FM_RECORD_ANSI(0x001B0202),
		FM_RECORD_ISO(0x01010002),
		II_RECORD_ANSI_POLAR(0x001B0602),
		II_RECORD_ISO_POLAR(0x0101000B),
		II_RECORD_ANSI_RECTILINEAR(0x001B0601),
		II_RECORD_ISO_RECTILINEAR(0x01010009);


		private int value;

		private BdbFormat(int value) {
			this.value = value;
		}

	}

	private TextView mResult;
	private EditText mPatronFormat;
	private Button mLoadCBEFFRecord;
	private int mIndex = 0;

	private void enableControls(final boolean enable) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mPatronFormat.setEnabled(enable);
				mLoadCBEFFRecord.setEnabled(enable);
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
			return false;
		}
		return true;
	}

	private void getRecord() {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, BiometricStandardsTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, REQUEST_CODE_GET_RECORD);
	}

	private void unpack(Uri recordUri) throws IOException {
		try {
			// Get CBEFFRecord patron format
			// all supported patron formats can be found in CBEFFRecord class documentation
			int patronFormat = Integer.parseInt(mPatronFormat.getText().toString(), 16);

			// Read CBEFFRecord buffer
			// Creating CBEFFRecord object from NBuffer object
			try (NBuffer packedCBEFFRecord = NBuffer.fromByteBuffer(IOUtils.toByteBuffer(this, recordUri));
				 CBEFFRecord cbeffRecord = new CBEFFRecord(packedCBEFFRecord, patronFormat)) {
				unpackRecords(cbeffRecord);
			}
		} catch (Exception e) {
			showMessage(e.toString());
			Log.e(TAG, "Exception", e);
		}
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_unpack_complex_cbeff_record);
		mPatronFormat = (EditText) findViewById(R.id.tutorials_field_1);
		mPatronFormat.setHint(getString(R.string.hint_patron_format));
		mLoadCBEFFRecord = (Button) findViewById(R.id.tutorials_button_1);
		mLoadCBEFFRecord.setText(R.string.msg_select_complex_cbeffrecord);
		mLoadCBEFFRecord.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				if (validateInput()) {
					getRecord();
				} else {
					showMessage(getString(R.string.format_patron_format_not_valid, mPatronFormat.getText().toString()));
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
					showMessage(getString(R.string.msg_unpacking));
					mIndex = 0;
					unpack(data.getData());
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

	private void unpackRecords(CBEFFRecord cbeffRecord) {
		for (CBEFFRecord record : cbeffRecord.getRecords()) {
			if (record.getRecords().size() == 0) {
				recordToFile(record);
			} else {
				unpackRecords(record);
			}
		}
	}

	private void recordToFile(CBEFFRecord record) {
		String fileName;
		try {
			fileName = String.format("Record_%s_%d.dat", lookup.get(record.getBdbFormat()), ++mIndex);
		} catch (Exception ex) {
			fileName = String.format("Record_%d.dat", ++mIndex);
		}
		byte[] data;
		try (NBuffer templateBuffer = record.getBdbBuffer()) {
			data = templateBuffer.toByteArray();
		}
		requestToSaveFile(fileName, new OnSelectionListener() {
			@Override
			public void onFileSelected(Uri path) {
				try {
					saveDataToUri(UnpackComplexCbeffRecord.this, path, data);
					showMessage(getString(R.string.format_record_saved_to));
				} catch (IOException e) {
					showError(e);
				}
			}
		});
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(UnpackComplexCbeffRecord.this, LICENSES);
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
