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
import java.util.ArrayList;
import java.util.List;

import com.neurotec.biometrics.standards.BDIFFPPosition;
import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FIRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;
import com.neurotec.util.NVersion;

public final class FIRecordFromNImage extends BaseActivity {

	private static final String TAG = FIRecordFromNImage.class.getSimpleName();
	private static final int REQUEST_CODE_GET_IMAGE = 1;

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor"};

	//=========================================================================

	private Button mButton;
	private EditText mFieldNumber;
	private EditText mFieldStandard;
	private EditText mFieldVersion;
	private TextView mResult;
	private int mImagesNumber;
	private List<Uri> mImages = new ArrayList<Uri>();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_firecord_from_nimage);
		mFieldNumber = (EditText) findViewById(R.id.tutorials_field_1);
		mFieldNumber.setHint(R.string.hint_open_images_number);
		mFieldStandard = (EditText) findViewById(R.id.tutorials_field_2);
		mFieldStandard.setHint(R.string.hint_standard_iso_ansi);
		mFieldVersion = (EditText) findViewById(R.id.tutorials_field_3);
		mFieldVersion.setHint(R.string.hint_fi_record_version);
		mButton = (Button) findViewById(R.id.tutorials_button_1);
		mButton.setText(R.string.msg_select_image);
		mButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				if (validateInput()) {
					for (int i = 0; i < mImagesNumber; i++) {
						getImage();
					}
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
		if (requestCode == REQUEST_CODE_GET_IMAGE) {
			if (resultCode == RESULT_OK) {
				try {
					mImages.add(data.getData());
					if (mImages.size() == mImagesNumber) {
						List<Uri> temp = new ArrayList<Uri>(mImages);
						mImages.clear();
						convert(temp);
					}
				} catch (Exception e) {
					showMessage(e.toString());
					Log.e(TAG, "Exception", e);
				}
			} else {
				mImages.clear();
			}
		}
	}

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private void getImage() {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, BiometricStandardsTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, REQUEST_CODE_GET_IMAGE);
	}

	private boolean validateInput() {
		try {
			mImagesNumber = Integer.parseInt(mFieldNumber.getText().toString());
		} catch (NumberFormatException e) {
			showMessage(getString(R.string.format_number_not_valid, mFieldNumber.getText().toString()));
			return false;
		}
		return true;
	}

	private void convert(List<Uri> images) throws IOException {
		FIRecord fi = null;
		BDIFStandard standard;
		String standardField = mFieldStandard.getText().toString();
		if (standardField.equalsIgnoreCase(getString(R.string.standard_iso))) {
			standard = BDIFStandard.ISO;
		} else if (standardField.equalsIgnoreCase(getString(R.string.standard_ansi))) {
			standard = BDIFStandard.ANSI;
		} else {
			showMessage(getString(R.string.format_unknown_standard, mFieldStandard.getText().toString()));
			return;
		}

		NVersion version;
		float versionNumber = Float.parseFloat(mFieldVersion.getText().toString());
		if (versionNumber == 1) {
			version = standard == BDIFStandard.ANSI ? FIRecord.VERSION_ANSI_10 : FIRecord.VERSION_ISO_10;
		} else if (versionNumber == 2) {
			if (standard != BDIFStandard.ISO) {
				throw new IllegalArgumentException("Standard and version is incompatible");
			}
			version = FIRecord.VERSION_ISO_20;
		} else if (versionNumber == 2.5) {
			if (standard != BDIFStandard.ANSI) {
				throw new IllegalArgumentException("Standard and version is incompatible");
			}
			version = FIRecord.VERSION_ANSI_25;
		} else {
			showMessage(getString(R.string.format_version_not_valid, mFieldVersion.getText().toString()));
			return;
		}

		int horzScanResolution = 500;
		int vertScanResolution = 500;
		BDIFFPPosition fPossition = BDIFFPPosition.RIGHT_THUMB;
		try {
			for (Uri uri : images) {
				// Get image buffer from Uri
				try (NBuffer buffer = new NBuffer(IOUtils.toByteBuffer(this, uri))) {
					if (fi == null) {
						fi = new FIRecord(standard, version, (short) 10, fPossition, horzScanResolution, vertScanResolution, buffer);
					} else {
						fi.getFingerViews().add(fPossition, horzScanResolution, vertScanResolution, buffer);
					}
				}
			}

			if (fi != null) {
				// Save converted template to file
				byte[] data;
				try (NBuffer templateBuffer = fi.save()) {
					data = templateBuffer.toByteArray();
				}
				requestToSaveFile("firecord-from-nimage.dat", new OnSelectionListener() {
					@Override
					public void onFileSelected(Uri path) {
						try {
							saveDataToUri(FIRecordFromNImage.this, path, data);
							showMessage(getString(R.string.format_converted_template_saved_to));
						} catch (IOException e) {
							showError(e);
						}
					}
				});
			} else {
				showMessage("Failed to create template");
			}
		} finally {
			if (fi != null) fi.dispose();
		}
	}

	private static boolean isRecordFirstVersion(FIRecord record) {
		return (record.getVersion().equals(FIRecord.VERSION_ANSI_10)) || (record.getVersion().equals(FIRecord.VERSION_ISO_10));
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(FIRecordFromNImage.this, LICENSES);
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
