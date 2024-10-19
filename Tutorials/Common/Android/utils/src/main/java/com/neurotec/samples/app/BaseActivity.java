package com.neurotec.samples.app;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.ParcelFileDescriptor;
import androidx.documentfile.provider.DocumentFile;
import android.util.Log;

import com.neurotec.samples.util.ExceptionUtils;
import com.neurotec.samples.util.ToastManager;
import com.neurotec.samples.view.ErrorDialogFragment;
import com.neurotec.samples.view.InfoDialogFragment;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public abstract class BaseActivity extends Activity {

	protected interface OnSelectionListener {
		void onFileSelected(Uri path);
	}

	protected interface OnDirectorySelectionListener {
		void onDirectorySelected(List<Uri> uriList);
	}

	// ===========================================================
	// Private fields
	// ===========================================================

	private ProgressDialog mProgressDialog;
	private Map<Integer, OnSelectionListener> mFileSelectionListeners = new HashMap<>();
	private OnDirectorySelectionListener mDirectorySelectionListener = null;

	// ===========================================================
	// Protected fields
	// ===========================================================

	protected static final int REQUEST_TO_SAVE_FILE_ID = 9999;
	protected static final int REQUEST_DIRECTORY_PATH = 9998;
	protected static final int REQUEST_TO_SAVE_TEMPLATE_ID = 9997;

	// ===========================================================
	// Private methods
	// ===========================================================

	private static String getExtension(String fileName) {
		String[] tokens = fileName.split("\\.(?=[^\\.]+$)");
		if (tokens.length > 1) {
			return tokens[1];
		} else {
			throw new IllegalArgumentException("Filename does not contain extension");
		}
	}

	// ===========================================================
	// Protected methods
	// ===========================================================

	protected static void saveDataToUri(Context context, Uri uri, byte[] data) throws IOException {
		try (ParcelFileDescriptor pfd = context.getContentResolver().openFileDescriptor(uri, "w");
			 FileOutputStream fos = new FileOutputStream(pfd.getFileDescriptor())) {
			fos.write(data);
		}
	}

	protected void requestToSaveFile(String filename, OnSelectionListener listener) {
		requestToSaveFile(filename, REQUEST_TO_SAVE_FILE_ID, listener);
	}

	protected void requestToSaveFile(String filename, int requestCode, OnSelectionListener listener) {
		mFileSelectionListeners.put(requestCode, listener);
		Intent intent = new Intent(Intent.ACTION_CREATE_DOCUMENT);
		StringBuilder mime = new StringBuilder();
		mime.append("application/");
		mime.append(getExtension(filename));
		intent.setType(mime.toString());
		intent.putExtra(Intent.EXTRA_TITLE, filename);
		startActivityForResult(intent, requestCode);
	}

	protected void requestDirectory(OnDirectorySelectionListener listener) {
		this.mDirectorySelectionListener = listener;
		Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT_TREE);
		intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
		startActivityForResult(intent, REQUEST_DIRECTORY_PATH);
	}

	protected void showProgress(int messageId) {
		showProgress(getString(messageId));
	}

	protected void showProgress(final String message) {
		hideProgress();
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mProgressDialog = ProgressDialog.show(BaseActivity.this, "", message);
			}
		});
	}

	protected void hideProgress() {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (mProgressDialog != null && mProgressDialog.isShowing()) {
					mProgressDialog.dismiss();
				}
			}
		});
	}

	protected void showToast(int messageId) {
		showToast(getString(messageId));
	}

	protected void showToast(final String message) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				ToastManager.show(BaseActivity.this, message);
			}
		});
	}

	protected void showError(String message, boolean close) {
		ErrorDialogFragment.newInstance(message, close).show(getFragmentManager(), "error");
	}

	protected void showError(int messageId) {
		showError(getString(messageId));
	}

	protected void showError(String message) {
		showError(message, false);
	}

	protected void showError(Throwable th) {
		Log.e(getClass().getSimpleName(), "Exception", th);
		showError(ExceptionUtils.getMessage(th), false);
	}

	protected void showInfo(int messageId) {
		showInfo(getString(messageId));
	}

	protected void showInfo(String message) {
		InfoDialogFragment.newInstance(message).show(getFragmentManager(), "info");
	}

	@Override
	protected void onStop() {
		super.onStop();
		hideProgress();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent resultData) {
		if (requestCode == REQUEST_TO_SAVE_FILE_ID || requestCode == REQUEST_TO_SAVE_TEMPLATE_ID) {
			if (resultCode == Activity.RESULT_OK) {
				OnSelectionListener listener = mFileSelectionListeners.get(requestCode);
				if (resultData != null && listener != null) {
					listener.onFileSelected(resultData.getData());
					mFileSelectionListeners.remove(requestCode);
				}
			}
		} else if (requestCode == REQUEST_DIRECTORY_PATH) {
			if (resultCode == Activity.RESULT_OK) {
				if (resultData != null) {
					DocumentFile df = DocumentFile.fromTreeUri(BaseActivity.this, resultData.getData());
					if (df.isDirectory()) {
						List<Uri> uriList = new ArrayList<Uri>();
						for(DocumentFile doc : df.listFiles()){
							uriList.add(doc.getUri());
						}
						mDirectorySelectionListener.onDirectorySelected(uriList);
						mDirectorySelectionListener = null;
					} else {
						mDirectorySelectionListener = null;
						throw new IllegalArgumentException("Not a directory");
					}
				}
			}
		}
	}
}
