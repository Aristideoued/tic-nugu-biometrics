package com.neurotec.tutorials.media;

import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.text.method.DigitsKeyListener;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.EnumSet;
import java.util.List;

import com.neurotec.images.NImage;
import com.neurotec.media.NMediaFormat;
import com.neurotec.media.NMediaReader;
import com.neurotec.media.NMediaSource;
import com.neurotec.media.NMediaType;
import com.neurotec.samples.app.BaseActivity;
import com.neurotec.samples.app.DirectoryViewer;
import com.neurotec.samples.licensing.LicensingManager;

public final class ReadVideo extends BaseActivity {

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final String TAG = ReadVideo.class.getSimpleName();

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	private static final String[] LICENSES = new String[]{"FaceExtractor"};
	//private static final String[] LICENSES = new String[]{"FaceClient"};
	//private static final String[] LICENSES = new String[]{"FaceFastExtractor"};

	//=========================================================================

	private static final int REQUEST_CODE_GET_VIDEO = 123;
	private static final String ANDROID_ASSET_DESCRIPTOR = "file:///android_asset/";

	// ===========================================================
	// Private fields
	// ===========================================================

	private enum Source {
		VIDEO_FILE,
		URL;
	}

	private Button mFromUrlButton;
	private Button mFromVideoFileButton;
	private TextView mResult;
	private EditText mTextVideoUrl;
	private EditText mTextFrameCount;
	private Uri mSelectedFile;

	// ===========================================================
	// Private Methods
	// ===========================================================

	private void getVideo(Source source) {
		if (source == Source.VIDEO_FILE) {
			Intent intent = new Intent(getApplicationContext(), DirectoryViewer.class);
			intent.putExtra(DirectoryViewer.ASSET_DIRECTORY_LOCATION, MediaTutorialsApp.TUTORIALS_ASSET_DIRECTORY);
			startActivityForResult(intent, REQUEST_CODE_GET_VIDEO);
		} else {
			readVideo(source);
		}
	}

	private void showMessage(String message) {
		mResult.append(message + "\n");
	}

	private void readVideoFrames(NMediaReader mediaReader, int frameCount) throws Exception {
		NMediaSource mediaSource = mediaReader.getSource();
		showMessage(String.format("Media length: %s\n", mediaReader.getLength()));
		NMediaFormat[] mediaFormats = mediaSource.getFormats(NMediaType.VIDEO);
		if (mediaFormats == null) {
			showMessage("Formats are not yet available (should be available after media reader is started");
		} else {
			showMessage(String.format("Format count: %s\n", mediaFormats.length));
			for (int i = 0; i < mediaFormats.length; i++) {
				showMessage(String.format("[%s] ", i));
				MediaTutorialsApp.dumpMediaFormat(mediaFormats[i]);
			}
		}

		NMediaFormat currentMediaFormat = mediaSource.getCurrentFormat(NMediaType.VIDEO);
		if (currentMediaFormat != null) {
			showMessage("Current media format:");
			MediaTutorialsApp.dumpMediaFormat(currentMediaFormat);

			if (mediaFormats != null) {
				showMessage("Set the last supported format (optional) ... ");
				mediaSource.setCurrentFormat(NMediaType.VIDEO, mediaFormats[mediaFormats.length - 1]);
			}
		} else {
			showMessage("Current media format is not yet available (will be available after media reader start)");
		}

		showMessage("Starting capture ... ");
		mediaReader.start();
		showMessage("Capture started");

		try {
			currentMediaFormat = mediaSource.getCurrentFormat(NMediaType.VIDEO);
			if (currentMediaFormat == null) {
				throw new Exception("Current media format is not set even after media reader start!");
			}
			showMessage("Capturing with format: ");
			MediaTutorialsApp.dumpMediaFormat(currentMediaFormat);

			for (int i = 0; i < frameCount; i++) {
				NMediaReader.ReadResult result = mediaReader.readVideoSample();
				NImage image = result.getImage();
				if (result.getImage() == null) {
					return; // end of stream
				}
				String filename = String.format("{%d4}.jpg", i);
				image.save(filename);
				showMessage(String.format("[%s %s] %s\n", result.getTimeStamp(), result.getDuration(), filename));
			}
		} finally {
			mediaReader.stop();
		}
	}

	private void readVideo(Source source) {
		NMediaSource mediaSource = null;
		NMediaReader mediaReader = null;

		try {
			int bufferCount = 0;
			try {
				bufferCount = Integer.parseInt(mTextFrameCount.getText().toString());
			} catch (NumberFormatException exc) {
				showMessage("Invalid frame count");
			}
			if (bufferCount <= 0) {
				showMessage("No frames will be captured as frame count is not specified");
				return;
			}

			// Create media source
			switch (source) {
				case URL:
					if (!mTextVideoUrl.getText().toString().isEmpty()) {
						mediaSource = NMediaSource.fromUrl(mTextVideoUrl.getText().toString());
					} else {
						showMessage("Video URL is mandatory for RTSP");
						return;
					}
					break;
				case VIDEO_FILE:
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

			mediaReader = new NMediaReader(mediaSource, EnumSet.of(NMediaType.VIDEO), true);
			readVideoFrames(mediaReader, bufferCount);
			showMessage("Done");
		} catch (Exception e) {
			Log.e(TAG, "", e);
			showMessage(e.getMessage());
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
		setContentView(R.layout.tutorial_read_video);
		mFromUrlButton = (Button) findViewById(R.id.tutorials_button_1);
		mFromUrlButton.setText(getString(R.string.msg_rtsp_camera));
		mFromUrlButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mResult.setText("");
				getVideo(Source.URL);
			}

		});
		mFromVideoFileButton = (Button) findViewById(R.id.tutorials_button_2);
		mFromVideoFileButton.setText(getString(R.string.msg_video_file));
		mFromVideoFileButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mResult.setText("");
				getVideo(Source.VIDEO_FILE);
			}

		});
		mResult = (TextView) findViewById(R.id.tutorials_results);
		mTextFrameCount = (EditText) findViewById(R.id.tutorials_field_1);
		mTextFrameCount.setKeyListener(DigitsKeyListener.getInstance("0123456789."));
		mTextFrameCount.setHint("Frame Count");
		mTextVideoUrl = (EditText) findViewById(R.id.tutorials_field_2);
		mTextVideoUrl.setHint("Video URL");
		enableControls(false);
		new InitializationTask().execute();
	}

	private void enableControls(final boolean enable) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mFromUrlButton.setEnabled(enable);
				mFromVideoFileButton.setEnabled(enable);
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
		if (requestCode == REQUEST_CODE_GET_VIDEO) {
			if (resultCode == RESULT_OK) {
				mSelectedFile = data.getData();
				readVideo(Source.VIDEO_FILE);
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
				List<String> obtainedLicenses = LicensingManager.getInstance().obtainLicenses(ReadVideo.this, LICENSES);
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
