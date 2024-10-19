package com.neurotec.samples.view;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;

import com.neurotec.samples.R;

public class InfoDialogFragment extends BaseDialogFragment {

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final String EXTRA_MESSAGE = "message";
	private static final String EXTRA_BUTTON_TEXT = "button-text";

	// ===========================================================
	// Public static methods
	// ===========================================================

	public static InfoDialogFragment newInstance(String message) {
		return newInstance(message, "OK");
	}

	public static InfoDialogFragment newInstance(String message, String buttonText) {
		InfoDialogFragment frag = new InfoDialogFragment();
		Bundle args = new Bundle();
		args.putString(EXTRA_MESSAGE, message);
		args.putString(EXTRA_BUTTON_TEXT, buttonText);
		frag.setArguments(args);
		return frag;
	}

	// ===========================================================
	// Private constructor
	// ===========================================================

	public InfoDialogFragment() {
	}

	// ===========================================================
	// Public methods
	// ===========================================================

	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		String message = getArguments().getString(EXTRA_MESSAGE);
		String buttonText = getArguments().getString(EXTRA_BUTTON_TEXT);
		return new AlertDialog.Builder(getActivity())
			.setMessage(message)
			.setPositiveButton(buttonText, new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int whichButton) {
						dialog.cancel();
				}
		}).create();
	}

}