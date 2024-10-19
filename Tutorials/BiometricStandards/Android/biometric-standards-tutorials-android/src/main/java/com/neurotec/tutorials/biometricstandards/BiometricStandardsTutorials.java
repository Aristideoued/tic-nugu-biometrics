package com.neurotec.tutorials.biometricstandards;

import android.Manifest;
import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import java.text.Collator;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.neurotec.lang.NCore;
import com.neurotec.licensing.gui.ActivationActivity;

public final class BiometricStandardsTutorials extends ListActivity implements ActivityCompat.OnRequestPermissionsResultCallback {

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final Comparator<Map<String, Object>> DISPLAY_NAME_COMPARATOR = new Comparator<Map<String, Object>>() {
		private final Collator collator = Collator.getInstance();

		@Override
		public int compare(Map<String, Object> map1, Map<String, Object> map2) {
			return collator.compare(map1.get(KEY_TITLE), map2.get(KEY_TITLE));
		}
	};
	private static final String KEY_TITLE = "title";
	private static final String KEY_INTENT = "intent";
	private static final int REQUEST_ID_MULTIPLE_PERMISSIONS = 1;
	private static final String WARNING_PROCEED_WITH_NOT_GRANTED_PERMISSIONS = "Do you wish to proceed without granting all permissions?";
	private static final String WARNING_NOT_ALL_GRANTED = "Some permissions are not granted.";
	private static final String MESSAGE_ALL_PERMISSIONS_GRANTED = "All permissions granted";
	private static final String TAG = BiometricStandardsTutorials.class.getSimpleName();

	// ===========================================================
	// Public static fields
	// ===========================================================

	public static final String CATEGORY_NEUROTEC_TUTORIAL = BiometricStandardsTutorials.class.getPackage().getName() + ".CATEGORY_NEUROTEC_TUTORIAL";

	// ===========================================================
	// Private methods
	// ===========================================================

	private List<Map<String, Object>> getData() {
		List<Map<String, Object>> myData = new ArrayList<Map<String, Object>>();

		Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);
		mainIntent.addCategory(CATEGORY_NEUROTEC_TUTORIAL);

		PackageManager pm = getPackageManager();
		List<ResolveInfo> list = pm.queryIntentActivities(mainIntent, 0);

		if (null == list) {
			return myData;
		}

		int len = list.size();

		for (int i = 0; i < len; i++) {
			ResolveInfo info = list.get(i);
			CharSequence labelSeq = info.loadLabel(pm);
			String label;
			if (labelSeq == null) {
				label = info.activityInfo.name;
			} else {
				label = labelSeq.toString();
			}
			addItem(myData, label, activityIntent(info.activityInfo.applicationInfo.packageName, info.activityInfo.name));
		}

		Collections.sort(myData, DISPLAY_NAME_COMPARATOR);

		return myData;
	}

	private Intent activityIntent(String pkg, String componentName) {
		Intent result = new Intent();
		result.setClassName(pkg, componentName);
		return result;
	}

	private void addItem(List<Map<String, Object>> data, String name, Intent intent) {
		Map<String, Object> temp = new HashMap<String, Object>();
		temp.put(KEY_TITLE, name);
		temp.put(KEY_INTENT, intent);
		data.add(temp);
	}

	private void showDialogOK(String message, DialogInterface.OnClickListener okListener) {
		new AlertDialog.Builder(this)
				.setMessage(message)
				.setPositiveButton("OK", okListener)
				.setNegativeButton("Cancel", okListener)
				.create()
				.show();
	}

	private static List<String> getRequiredPermissions() {
		List<String> permissions = new ArrayList<String>();
		permissions.add(Manifest.permission.INTERNET);
		permissions.add(Manifest.permission.ACCESS_NETWORK_STATE);
		permissions.add(Manifest.permission.READ_EXTERNAL_STORAGE);
		permissions.add(Manifest.permission.WRITE_EXTERNAL_STORAGE);

		if (android.os.Build.VERSION.SDK_INT < 23) {
			permissions.add(Manifest.permission.WRITE_SETTINGS);
		}
		return permissions;
	}

	private String[] getNotGrantedPermissions() {
		List<String> neededPermissions = new ArrayList<String>();

		for (String permission : getRequiredPermissions()) {
			if (ContextCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED) {
				neededPermissions.add(permission);
			}
		}
		return neededPermissions.toArray(new String[neededPermissions.size()]);
	}

	private void requestPermissions(String[] permissions) {
		ActivityCompat.requestPermissions(this, permissions, REQUEST_ID_MULTIPLE_PERMISSIONS);
	}

	private boolean ifAllPermissionsGranted(int[] results) {
		boolean finalResult = true;
		for (int permissionResult : results) {
			finalResult &= (permissionResult == PackageManager.PERMISSION_GRANTED);
			if (!finalResult) break;
		}
		return finalResult;
	}

	// ==============================================
	// Public methods
	// ==============================================

	public void onRequestPermissionsResult(int requestCode, final String permissions[], final int[] grantResults) {
		switch (requestCode) {
			case REQUEST_ID_MULTIPLE_PERMISSIONS: {
				if (grantResults.length > 0) {

					// Check if all permissions granted
					if (!ifAllPermissionsGranted(grantResults)) {
						showDialogOK(WARNING_PROCEED_WITH_NOT_GRANTED_PERMISSIONS,
								new DialogInterface.OnClickListener() {
									@Override
									public void onClick(DialogInterface dialog, int which) {
										switch (which) {
											case DialogInterface.BUTTON_POSITIVE:
												Log.w(TAG, WARNING_NOT_ALL_GRANTED);
												for(int i = 0; i < permissions.length;i++) {
													if (grantResults[i] != PackageManager.PERMISSION_GRANTED) {
														Log.w(TAG, permissions[i] + ": PERMISSION_DENIED");
													}
												}
												break;
											case DialogInterface.BUTTON_NEGATIVE:
												requestPermissions(permissions);
												break;
											default:
												throw new AssertionError("Unrecognised permission dialog parameter value");
										}
									}
								});
					} else {
						Log.i(TAG, MESSAGE_ALL_PERMISSIONS_GRANTED);
					}
				}
			}
		}
	}

	// ===========================================================
	// Activity events
	// ===========================================================

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		NCore.setContext(this);
		setListAdapter(new SimpleAdapter(this, getData(), android.R.layout.simple_list_item_1, new String[]{KEY_TITLE}, new int[]{android.R.id.text1}));
		getListView().setTextFilterEnabled(true);

		String[] neededPermissions = getNotGrantedPermissions();
		if (neededPermissions.length != 0) {
			requestPermissions(neededPermissions);
		}
	}

	// ===========================================================
	// List events
	// ===========================================================

	@SuppressWarnings("unchecked")
	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		Map<String, Object> map = (Map<String, Object>) l.getItemAtPosition(position);
		Intent intent = (Intent) map.get(KEY_INTENT);
		startActivity(intent);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.options_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
			case R.id.action_activation: {
				startActivity(new Intent(this, ActivationActivity.class));
				break;
			}
		}
		return true;
	}
}
