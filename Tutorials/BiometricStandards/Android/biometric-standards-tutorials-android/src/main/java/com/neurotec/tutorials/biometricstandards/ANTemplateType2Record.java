package com.neurotec.tutorials.biometricstandards;

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
import android.widget.Toast;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.neurotec.biometrics.standards.ANField;
import com.neurotec.biometrics.standards.ANTemplate;
import com.neurotec.biometrics.standards.ANType2Record;
import com.neurotec.biometrics.standards.BDIFEncodingType;
import com.neurotec.io.NBuffer;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.licensing.LicensingManager;

public final class ANTemplateType2Record extends BaseActivity {

	private static final String TAG = ANTemplateType2Record.class.getSimpleName();

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = {"FingerClient", "PalmClient", "FaceClient", "IrisClient"};
	//private static final String[] LICENSES = {"FingerFastExtractor", "PalmClient", "FaceFastExtractor", "IrisFastExtractor"};

	//=========================================================================

	private Map<BDIFEncodingType, String> mANTemplateFileNames = new HashMap<BDIFEncodingType, String>() {{
		put(BDIFEncodingType.TRADITIONAL, "antemplate-type-2.dat");
		put(BDIFEncodingType.XML, "antemplate-type-2.xml");
	}};

	private EditText mFieldTot;
	private EditText mFieldDai;
	private EditText mFieldOri;
	private EditText mFieldTcn;
	private Spinner mSpinnerEncoding;
	private Button mButton;
	private TextView mResult;
	private String mTot;
	private String mDai;
	private String mOri;
	private String mTcn;
	private BDIFEncodingType mEncoding;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_antemplate_type_2_record);
		mFieldTot = (EditText) findViewById(R.id.tutorials_field_1);
		mFieldTot.setHint(R.string.hint_tot);
		mFieldDai = (EditText) findViewById(R.id.tutorials_field_2);
		mFieldDai.setHint(R.string.hint_dai);
		mFieldOri = (EditText) findViewById(R.id.tutorials_field_3);
		mFieldOri.setHint(R.string.hint_ori);
		mFieldTcn = (EditText) findViewById(R.id.tutorials_field_4);
		mFieldTcn.setHint(R.string.hint_tcn);
		mSpinnerEncoding = (Spinner) findViewById(R.id.tutorials_spinner_1);
		mSpinnerEncoding.setAdapter(new ArrayAdapter<BDIFEncodingType>(ANTemplateType2Record.this, android.R.layout.simple_spinner_item, BDIFEncodingType.values()));
		mButton = (Button) findViewById(R.id.tutorials_button_1);
		mButton.setText(R.string.msg_create_template);
		mButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mTot = mFieldTot.getText().toString();
				mDai = mFieldDai.getText().toString();
				mOri = mFieldOri.getText().toString();
				mTcn = mFieldTcn.getText().toString();
				mEncoding = (BDIFEncodingType) mSpinnerEncoding.getSelectedItem();
				if (validateInput(mTot, mDai, mOri, mTcn)) {
					try {
						createRecord(mTot, mDai, mOri, mTcn, mEncoding);
					} catch (IOException e) {
						Log.e(TAG, e.getMessage(), e);
						Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_SHORT).show();
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

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private boolean validateInput(String tot, String dai, String ori, String tcn) {
		if (TextUtils.isEmpty(tot) || TextUtils.isEmpty(dai) || TextUtils.isEmpty(ori) || TextUtils.isEmpty(tcn)) {
			showMessage(getString(R.string.msg_one_or_more_fields_empty));
			return false;
		}
		if ((tot.length() > 4) || (tot.length() < 3)) {
			showMessage(getString(R.string.msg_tot_length));
			return false;
		}
		return true;
	}

	private void createRecord(String tot, String dai, String ori, String tcn, BDIFEncodingType encoding) throws IOException {
		try (ANTemplate template = new ANTemplate(ANTemplate.VERSION_CURRENT, tot, dai, ori, tcn, 0);
			 ANType2Record record = template.getRecords().addType2()) {

			int nameFieldNumber = 18;// exemplary field number for subject's name and surname
			String nameFieldValue = "name, surname"; // exemplary subject's name and surname
			int placeOfBirthFieldNumber = 20;// exemplary field number for subject's place of birth
			String placeOfBirthFieldValue = "UK"; // exemplary subject's place of birth
			int dateOfBirthFieldNumber = 22;// exemplary field number for subject's date of birth
			String dateOfBirthFieldValue = "19700131"; // exemplary subject's date of birth
			int genderFieldNumber = 24;// exemplary field number for subject's gender
			String genderFieldValue = "M";// exemplary subject's gender

			// Create an empty ANTemplate object with currect version and only type 1 record in it

			// Add fields for "traditional" binary encoding
			if (encoding == BDIFEncodingType.TRADITIONAL) {
				try (ANField _1 = record.getFields().add(nameFieldNumber, nameFieldValue);
					 ANField _2 = record.getFields().add(placeOfBirthFieldNumber, placeOfBirthFieldValue);
					 ANField _3 = record.getFields().add(dateOfBirthFieldNumber, dateOfBirthFieldValue);
					 ANField _4 = record.getFields().add(genderFieldNumber, genderFieldValue);) {}
			} else { // Add fields for NIEM-conformant XML encoding
				try (ANField _1 = record.getFields().add(nameFieldNumber, "PersonName", nameFieldValue);
					 ANField _2 = record.getFields().add(placeOfBirthFieldNumber, "PersonBirthPlaceCode", placeOfBirthFieldValue);
					 ANField _3 = record.getFields().add(dateOfBirthFieldNumber, "PersonBirthDate", dateOfBirthFieldValue);
					 ANField _4 = record.getFields().add(genderFieldNumber, "PersonSexCode", genderFieldValue);) {}
			}

			// Save template to file
			byte[] data;
			try (NBuffer templateBuffer = template.save(encoding)) {
				data = templateBuffer.toByteArray();
			}
			requestToSaveFile(mANTemplateFileNames.get(mEncoding), new OnSelectionListener() {
				@Override
				public void onFileSelected(Uri path) {
					try {
						saveDataToUri(ANTemplateType2Record.this, path, data);
						showMessage(getString(R.string.format_antemplate_saved_to, 2));
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(ANTemplateType2Record.this, LICENSES);
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
