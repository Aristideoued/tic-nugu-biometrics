package com.neurotec.tutorials.media;

import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.text.method.DigitsKeyListener;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.EnumSet;
import java.util.List;

import com.neurotec.media.NMediaFormat;
import com.neurotec.media.NMediaReader;
import com.neurotec.media.NMediaSource;
import com.neurotec.media.NMediaType;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;

public final class ReadAudio extends BaseActivity {

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final String TAG = ReadAudio.class.getSimpleName();

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = new String[]{"VoiceExtractor"};
	//private static final String[] LICENSES = new String[]{"VoiceClient"};
	//private static final String[] LICENSES = new String[]{"VoiceFastExtractor"};

	//=========================================================================

	private static final int REQUEST_CODE_GET_AUDIO = 124;
	private static final String ANDROID_ASSET_DESCRIPTOR = "file:///android_asset/";

	// ===========================================================
	// Private fields
	// ===========================================================

	private enum Source {
		AUDIO_FILE,
		URL;
	}

	private Button mFromAudioFileButton;
	private Button mFromUrlButton;
	private TextView mResult;
	private EditText mTextAudioUrl;
	private EditText mTextBufferLength;
	private Uri mSelectedFile;

	// ===========================================================
	// Private Methods
	// ===========================================================

	private void getAudio(Source source) {
		if (source == Source.AUDIO_FILE) {
			Intent intent = new Intent(getApplicationContext(), DirectoryViewer.class);
			intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, MediaTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
			startActivityForResult(intent, REQUEST_CODE_GET_AUDIO);
		} else {
			readAudio(source);
		}
	}

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private void readSoundBuffers(NMediaReader mediaReader, int bufferCount) throws Exception {
		NMediaSource mediaSource = mediaReader.getSource();

		showMessage(String.format("Media length: %s\n", mediaReader.getLength()));

		NMediaFormat[] mediaFormats = mediaSource.getFormats(NMediaType.AUDIO);
		if (mediaFormats == null) {
			showMessage("Formats are not yet available (should be available after media reader is started");
		} else {
			showMessage(String.format("Format count: %s\n", mediaFormats.length));
			for (int i = 0; i < mediaFormats.length; i++) {
				System.out.format("[%s] ", i);
				showMessage(MediaTutorialsApp.dumpMediaFormat(mediaFormats[i]));
			}
		}

		NMediaFormat currentMediaFormat = mediaSource.getCurrentFormat(NMediaType.AUDIO);
		if (currentMediaFormat != null) {
			showMessage("Current media format:");
			showMessage(MediaTutorialsApp.dumpMediaFormat(currentMediaFormat));

			if (mediaFormats != null) {
				showMessage("Set the last supported format (optional) ... ");
				mediaSource.setCurrentFormat(NMediaType.AUDIO, mediaFormats[mediaFormats.length - 1]);
			}
		} else {
			showMessage("Current media format is not yet available (will be available after media reader start)");
		}

		showMessage("Starting capture ... ");
		mediaReader.start();
		showMessage("Capture started");

		try {
			currentMediaFormat = mediaSource.getCurrentFormat(NMediaType.AUDIO);
			if (currentMediaFormat == null) {
				throw new Exception("Current media format is not set even after media reader start!");
			}
			showMessage("Capturing with format: ");
			showMessage(MediaTutorialsApp.dumpMediaFormat(currentMediaFormat));

			for (int i = 0; i < bufferCount; i++) {
				NMediaReader.ReadResult result = mediaReader.readAudioSample();
				if (result.getSoundBuffer() == null) {
					return; // end of stream
				}

				showMessage(String.format("[%s %s] sample rate: %s, sample length: %s\n", result.getTimeStamp(), result.getDuration(), result.getSoundBuffer()
						.getSampleRate(), result.getSoundBuffer().getLength()));
			}
		} finally {
			mediaReader.stop();
		}
	}

	private void readAudio(Source source) {
		NMediaSource mediaSource = null;
		NMediaReader mediaReader = null;

		try {
			int bufferCount = 0;
			try {
				bufferCount = Integer.parseInt(mTextBufferLength.getText().toString());
			} catch (NumberFormatException exc) {
				showMessage("Invalid buffer length");
			}
			if (bufferCount <= 0) {
				showMessage("No sound buffers will be captured as sound buffer count is not specified");
				return;
			}

			// Create media source
			switch (source) {
				case URL:
					if (!mTextAudioUrl.getText().toString().isEmpty()) {
						mediaSource = NMediaSource.fromUrl(mTextAudioUrl.getText().toString());
					} else {
						showMessage("Invalid Audio URL");
						return;
					}
					break;
				case AUDIO_FILE:
					String path;
					if (mSelectedFile.toString().contains(ANDROID_ASSET_DESCRIPTOR)) {
						path = mSelectedFile.toString().replace(ANDROID_ASSET_DESCRIPTOR, "");
					} else {
						path = mSelectedFile.getPath();
					}
					mediaSource = NMediaSource.fromFile(path);
					break;

				default:
					throw new AssertionError("Unknown source type");
			}
			if (mediaSource != null) {
				showMessage(String.format("Display name: %s\n", mediaSource.getDisplayName()));
			}

			mediaReader = new NMediaReader(mediaSource, EnumSet.of(NMediaType.AUDIO), true);
			readSoundBuffers(mediaReader, bufferCount);
			showMessage("Done");
		} catch (Exception e) {
			e.printStackTrace();
			showMessage(e.toString());
		} finally {
			if (mediaSource != null) {
				mediaSource.dispose();
			}
			if (mediaReader != null) {
				mediaReader.dispose();
			}
		}
	}

	// ===========================================================
	// Protected Methods
	// ===========================================================

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tutorial_read_audio);
		mFromUrlButton = (Button) findViewById(R.id.tutorials_button_1);
		mFromUrlButton.setText(getString(R.string.msg_audio_url));
		mFromUrlButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mResult.setText("");
				getAudio(Source.URL);
			}
		});
		mFromAudioFileButton = (Button) findViewById(R.id.tutorials_button_2);
		mFromAudioFileButton.setText(getString(R.string.msg_audio_file));
		mFromAudioFileButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mResult.setText("");
				getAudio(Source.AUDIO_FILE);
			}
		});
		mResult = (TextView) findViewById(R.id.tutorials_results);

		mTextBufferLength = (EditText) findViewById(R.id.tutorials_field_1);
		mTextBufferLength.setKeyListener(DigitsKeyListener.getInstance("0123456789."));
		mTextBufferLength.setHint("Buffer Length");
		mTextAudioUrl = (EditText) findViewById(R.id.tutorials_field_2);
		mTextAudioUrl.setHint("Audio URL");
		enableControls(false);
		new InitializationTask().execute();
	}

	private void enableControls(final boolean enable) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mFromAudioFileButton.setEnabled(enable);
				mFromUrlButton.setEnabled(enable);
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
		if (requestCode == REQUEST_CODE_GET_AUDIO) {
			if (resultCode == RESULT_OK) {
				mSelectedFile = data.getData();
				readAudio(Source.AUDIO_FILE);
			} else {
				showMessage("Failed to load file");
			}
		}
	}

	// ===========================================================
	// Public Methods
	// ===========================================================

	final class InitializationTask extends AsyncTask<Object, Boolean, Boolean> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			showProgress(R.string.msg_obtaining_licenses);
		}

		@Override
		protected Boolean doInBackground(Object... params) {
			try {
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(ReadAudio.this, LICENSES);
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