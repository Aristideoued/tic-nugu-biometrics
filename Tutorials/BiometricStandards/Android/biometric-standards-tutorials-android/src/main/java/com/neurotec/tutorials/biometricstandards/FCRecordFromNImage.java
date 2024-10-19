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

import com.neurotec.biometrics.standards.BDIFStandard;
import com.neurotec.biometrics.standards.FCRFaceImageType;
import com.neurotec.biometrics.standards.FCRecord;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;

public final class FCRecordFromNImage extends BaseActivity {

	private static final String TAG = FCRecordFromNImage.class.getSimpleName();
	private static final int REQUEST_CODE_GET_IMAGE = 1;

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FaceClient"};
	//private static final String[] LICENSES = {"FaceFastExtractor"};

	//=========================================================================

	private Button mButton;
	private EditText mFieldNumber;
	private TextView mResult;
	private int mImagesNumber;
	private List<Uri> mImages = new ArrayList<Uri>();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_fcrecord_from_nimage);
		mFieldNumber = (EditText) findViewById(R.id.tutorials_field_1);
		mFieldNumber.setHint(R.string.hint_open_images_number);
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

	private void convert(List<Uri> images) {
		FCRecord fc = null;
		try {
			for (Uri uri : images) {
				// Get image buffer from Uri
				try (NBuffer buffer = new NBuffer(IOUtils.toByteBuffer(this, uri))) {
					// Add grayscale image to FCRecord
					if (fc == null) {
						// Specify standard and version to be used
						fc = new FCRecord(BDIFStandard.ISO, FCRecord.VERSION_ISO_30, FCRFaceImageType.BASIC, buffer);
					} else {
						fc.getFaceImages().add(FCRFaceImageType.BASIC, buffer);
					}
				}
			}

			if (fc != null) {
				// Save converted template to file
				byte[] data;
				try (NBuffer templateBuffer = fc.save()) {
					data = templateBuffer.toByteArray();
				}
				requestToSaveFile("fcrecord-from-nimage.dat", new OnSelectionListener() {
					@Override
					public void onFileSelected(Uri path) {
						try {
							saveDataToUri(FCRecordFromNImage.this, path, data);
							showMessage(getString(R.string.format_converted_template_saved_to));
						} catch (IOException e) {
							showError(e);
						}
					}
				});
			} else {
				showMessage("Failed to create template");
			}
		} catch (Exception e) {
			showMessage(e.toString());
		} finally {
			if (fc != null) fc.dispose();
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(FCRecordFromNImage.this, LICENSES);
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
