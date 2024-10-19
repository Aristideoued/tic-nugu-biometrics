package com.neurotec.tutorials.biometricstandards;

import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType16Record;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;
import com.neurotec.samples.util.IOUtils;

public final class ANTemplateType16FromNImage extends BaseActivity {

	private static final String TAG = ANTemplateType16FromNImage.class.getSimpleName();
	private static final int REQUEST_CODE_GET_IMAGE = 1;

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient", "PalmClient", "FaceClient", "IrisClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor", "PalmClient", "FaceFastExtractor", "IrisFastExtractor"};

	//=========================================================================

	private Map<BDIFEncodingType, String> mANTemplateFileNames = new HashMap<BDIFEncodingType, String>() {{
		put(BDIFEncodingType.TRADITIONAL, "antemplate-type-16.dat");
		put(BDIFEncodingType.XML, "antemplate-type-16.xml");
	}};

	private EditText mFieldTot;
	private EditText mFieldDai;
	private EditText mFieldOri;
	private EditText mFieldTcn;
	private EditText mFieldSrc;
	private EditText mFieldUdi;
	private Spinner mSpinnerEncoding;
	private Button mButton;
	private TextView mResult;
	private String mTot;
	private String mDai;
	private String mOri;
	private String mTcn;
	private String mSrc;
	private String mUdi;
	private BDIFEncodingType mEncoding;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_antemplate_type_16_from_nimage);
		mFieldTot = (EditText) findViewById(R.id.tutorials_field_1);
		mFieldTot.setHint(R.string.hint_tot);
		mFieldDai = (EditText) findViewById(R.id.tutorials_field_2);
		mFieldDai.setHint(R.string.hint_dai);
		mFieldOri = (EditText) findViewById(R.id.tutorials_field_3);
		mFieldOri.setHint(R.string.hint_ori);
		mFieldTcn = (EditText) findViewById(R.id.tutorials_field_4);
		mFieldTcn.setHint(R.string.hint_tcn);
		mFieldSrc = (EditText) findViewById(R.id.tutorials_field_5);
		mFieldSrc.setHint(R.string.hint_src);
		mFieldUdi = (EditText) findViewById(R.id.tutorials_field_6);
		mFieldUdi.setHint(R.string.hint_udi);
		mSpinnerEncoding = (Spinner) findViewById(R.id.tutorials_spinner_1);
		mSpinnerEncoding.setAdapter(new ArrayAdapter<BDIFEncodingType>(ANTemplateType16FromNImage.this, android.R.layout.simple_spinner_item, BDIFEncodingType.values()));
		mButton = (Button) findViewById(R.id.tutorials_button_1);
		mButton.setText(R.string.msg_select_image);
		mButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mTot = mFieldTot.getText().toString();
				mDai = mFieldDai.getText().toString();
				mOri = mFieldOri.getText().toString();
				mTcn = mFieldTcn.getText().toString();
				mSrc = mFieldSrc.getText().toString();
				mUdi = mFieldUdi.getText().toString();
				mEncoding = (BDIFEncodingType) mSpinnerEncoding.getSelectedItem();
				if (validateInput()) {
					getImage();
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

	private void getImage() {
		Intent intent = new Intent(this, DirectoryViewer.class);
		intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, BiometricStandardsTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
		startActivityForResult(intent, REQUEST_CODE_GET_IMAGE);
	}

	private boolean validateInput() {
		if (TextUtils.isEmpty(mDai) || TextUtils.isEmpty(mOri) || TextUtils.isEmpty(mTcn) || TextUtils.isEmpty(mSrc) || TextUtils.isEmpty(mUdi)) {
			showMessage(getString(R.string.msg_one_or_more_fields_empty));
			return false;
		}
		if ((mTot.length() > 4) || (mTot.length() < 3)) {
			showMessage(getString(R.string.msg_tot_length));
			return false;
		}
		return true;
	}

	private void convert(Uri imageUri) throws IOException {
		// Create an empty ANTemplate object with only type 1 record in it
		// Create Type 16 record and add record to ANTemplate

		try (ANTemplate template = new ANTemplate(ANTemplate.VERSION_CURRENT, mTot, mDai, mOri, mTcn, 0);
			 NBuffer imgBuffer = new NBuffer(IOUtils.toByteBuffer(this, imageUri));
			 ANType16Record ignored = template.getRecords().addType16(mUdi, mSrc, imgBuffer)) {

			// Save template to file
			byte[] data;
			try (NBuffer templateBuffer = template.save(mEncoding)) {
				data = templateBuffer.toByteArray();
			}
			requestToSaveFile(mANTemplateFileNames.get(mEncoding), new OnSelectionListener() {
				@Override
				public void onFileSelected(Uri path) {
					try {
						saveDataToUri(ANTemplateType16FromNImage.this, path, data);
						showMessage(getString(R.string.format_antemplate_saved_to, 16));
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(ANTemplateType16FromNImage.this, LICENSES);
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
