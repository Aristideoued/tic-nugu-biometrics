package com.neurotec.tutorials.biometricstandards;

import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import com.neurotec.biometrics.standards.ANField;
import com.neurotec.biometrics.standards.ANImageType;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType10Record;
import com.neurotec.biometrics.standards.ANType14Record;
import com.neurotec.biometrics.standards.ANType17Record;
import com.neurotec.biometrics.standards.ANType2Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class ANTemplateMultiModal extends BaseActivity {

	private static final String TAG = ANTemplateMultiModal.class.getSimpleName();
	private static final int REQUEST_CODE_GET_FINGER_IMAGE = 1;
	private static final int REQUEST_CODE_GET_FACE_IMAGE = 2;
	private static final int REQUEST_CODE_GET_IRIS_IMAGE = 3;

	private Map<BDIFEncodingType, String> mANTemplateFileNames = new HashMap<BDIFEncodingType, String>() {{
		put(BDIFEncodingType.TRADITIONAL, "antemplate-multi-modal.dat");
		put(BDIFEncodingType.XML, "antemplate-multi-modal.xml");
	}};

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient", "FaceClient", "IrisClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor", "FaceFastExtractor", "IrisFastExtractor"};

	//=========================================================================

	private Spinner mSpinnerEncoding;
	private TextView mResult;
	private Uri mFingerImage;
	private Uri mFaceImage;
	private Uri mIrisImage;
	private BDIFEncodingType mEncoding;

	private Button mButtonCreateANTemplate = null;
	private Button mButtonSelectFaceImage = null;
	private Button mButtonSelectFingerImage = null;
	private Button mButtonSelectIrisImage = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_antemplate_multi_modal);

		mSpinnerEncoding = (Spinner) findViewById(R.id.tutorials_spinner_1);
		mSpinnerEncoding.setAdapter(new ArrayAdapter<BDIFEncodingType>(ANTemplateMultiModal.this, android.R.layout.simple_spinner_item, BDIFEncodingType.values()));

		mButtonSelectFingerImage = (Button) findViewById(R.id.tutorials_button_1);
		mButtonSelectFingerImage.setText(R.string.msg_select_finger_image);
		mButtonSelectFingerImage.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				getImage(REQUEST_CODE_GET_FINGER_IMAGE);
			}
		});

		mButtonSelectFaceImage = (Button) findViewById(R.id.tutorials_button_2);
		mButtonSelectFaceImage.setText(R.string.msg_select_face_image);
		mButtonSelectFaceImage.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				getImage(REQUEST_CODE_GET_FACE_IMAGE);
			}
		});

		mButtonSelectIrisImage = (Button) findViewById(R.id.tutorials_button_3);
		mButtonSelectIrisImage.setText(R.string.msg_select_iris_image);
		mButtonSelectIrisImage.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				getImage(REQUEST_CODE_GET_IRIS_IMAGE);
			}
		});

		mButtonCreateANTemplate = (Button) findViewById(R.id.tutorials_button_4);
		mButtonCreateANTemplate.setText(R.string.msg_create_template);
		mButtonCreateANTemplate.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mEncoding = (BDIFEncodingType) mSpinnerEncoding.getSelectedItem();
				if (validateInput()) {
					create();
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
				mButtonCreateANTemplate.setEnabled(enable);
				mButtonSelectFaceImage.setEnabled(enable);
				mButtonSelectFingerImage.setEnabled(enable);
				mButtonSelectIrisImage.setEnabled(enable);
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
		if (resultCode == RESULT_OK) {
			try {
				switch (requestCode) {
					case REQUEST_CODE_GET_FINGER_IMAGE:
						mFingerImage = data.getData();
						showMessage(getString(R.string.msg_finger_image_selected));
						break;
					case REQUEST_CODE_GET_FACE_IMAGE:
						mFaceImage = data.getData();
						showMessage(getString(R.string.msg_face_image_selected));
						break;
					case REQUEST_CODE_GET_IRIS_IMAGE:
						mIrisImage = data.getData();
						showMessage(getString(R.string.msg_iris_image_selected));
						break;
				}
			} catch (Exception e) {
				showMessage(e.toString());
				Log.e(TAG, "Exception", e);
			}
		}
	}

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private void getImage(int code) {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, BiometricStandardsTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, code);
	}

	private boolean validateInput() {
		if (mFingerImage != null) {
			return true;
		}
		showMessage(getString(R.string.msg_finger_image_not_selected));
		return false;
	}

	private ANType2Record addType2Record(ANTemplate antemplate, BDIFEncodingType encoding) {
		int nameFieldNumber = 18;
		int placeOfBirthFieldNumber = 20;
		int dateOfBirthFieldNumber = 22;
		int genderFieldNumber = 24;

		ANType2Record record = antemplate.getRecords().addType2();
		// Adds fields for "traditional" binary encoding
		if (encoding == BDIFEncodingType.TRADITIONAL) {
			try (ANField _1 = record.getFields().add(nameFieldNumber, "name, surname");
				 ANField _2 = record.getFields().add(placeOfBirthFieldNumber, "UK");
				 ANField _3 = record.getFields().add(dateOfBirthFieldNumber, "19700131");
				 ANField _4 = record.getFields().add(genderFieldNumber, "M");) {}
		} else { // Adds fields for NIEM-conformant XML encoding
			try (ANField _1 = record.getFields().add(nameFieldNumber, "PersonName", "name, surname");
				 ANField _2 = record.getFields().add(placeOfBirthFieldNumber, "PersonBirthPlaceCode", "UK");
				 ANField _3 = record.getFields().add(dateOfBirthFieldNumber, "PersonBirthDate", "19700131");
				 ANField _4 = record.getFields().add(genderFieldNumber, "PersonSexCode", "M");) {}
		}
		return record;
	}

	private ANType10Record addType10Record(ANTemplate antemplate, String src, Uri imageUri) throws Exception {
		ANImageType imt = ANImageType.FACE;
		try (NBuffer imgBuffer = new NBuffer(IOUtils.toByteBuffer(this, imageUri))) {
			/*
			 * Image must be compressed using valid compression algorithm for Type-10 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			 */
			return antemplate.getRecords().addType10(imt, src, imgBuffer);
		}
	}

	private ANType14Record addType14Record(ANTemplate antemplate, String src, Uri imageUri) throws Exception {
		try (NBuffer imgBuffer = new NBuffer(IOUtils.toByteBuffer(this, imageUri))) {
			/*
			 * Finger image must be compressed using valid compression algorithm for Type-14 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			 */
			return antemplate.getRecords().addType14(src, imgBuffer);
		}
	}

	private ANType17Record addType17Record(ANTemplate antemplate, String src, Uri imageUri) throws Exception {
		try (NBuffer imgBuffer = new NBuffer(IOUtils.toByteBuffer(this, imageUri))) {
			/*
			 * Finger image must be compressed using valid compression algorithm for Type-14 record.
			 * How to convert image to required compression algorithm please see "Media" tutorials, like "CreateWsq".
			 */
			return antemplate.getRecords().addType17(src, imgBuffer);
		}
	}

	private void create() {
		String tot = "TransactionType";
		String dai = "DestinationAgencyId";
		String ori = "OriginatingAgencyId";
		String tcn = "Transaction1";
		String src = "SourceAgencyName";

		try (ANTemplate antemplate = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, 0)) {
			addType2Record(antemplate, mEncoding);

			if (mFingerImage != null) {
				addType14Record(antemplate, src, mFingerImage);
			}
			if (mFaceImage != null) {
				addType10Record(antemplate, src, mFaceImage);
			}
			if (mIrisImage != null) {
				addType17Record(antemplate, src, mIrisImage);
			}

			byte[] data;
			try (NBuffer templateBuffer = antemplate.save(mEncoding)) {
				data = templateBuffer.toByteArray();
			}
			requestToSaveFile(mANTemplateFileNames.get(mEncoding), new OnSelectionListener() {
				@Override
				public void onFileSelected(Uri path) {
					try {
						saveDataToUri(ANTemplateMultiModal.this, path, data);
						showMessage(getString(R.string.format_antemplate_multimodal_saved_to));
					} catch (IOException e) {
						showError(e);
					}
				}
			});
		} catch (Exception e) {
			showMessage(e.toString());
			Log.e(TAG, "Exception", e);
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(ANTemplateMultiModal.this, LICENSES);
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