package com.neurotec.samples.devices;

import com.neurotec.licensing.NLicenseManager;
import com.neurotec.samples.util.LibraryManager;
import com.neurotec.samples.util.LicenseManager;
import com.neurotec.samples.util.Utils;

import java.awt.Dimension;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.ProgressMonitor;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;

public final class DevicesSample implements PropertyChangeListener {

	// ===========================================================
	// Private static final fields
	// ===========================================================

	private static final Set<String> LICENSES;

	// ===========================================================
	// Static constructor
	// ===========================================================

	static {
		LICENSES = new HashSet<String>(6);
		LICENSES.add("Biometrics.FingerDetection");
		LICENSES.add("Biometrics.PalmDetection");
		LICENSES.add("Devices.FingerScanners");
		LICENSES.add("Devices.PalmScanners");
		LICENSES.add("Biometrics.IrisDetection");
		LICENSES.add("Devices.IrisScanners");
	}

	// =============================================
	// Public static methods
	// =============================================

	public static void main(String[] args) {
		Utils.setupLookAndFeel();
		LibraryManager.initLibraryPath();
		DevicesSample application = new DevicesSample();

		//=========================================================================
		// TRIAL MODE
		//=========================================================================
		// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
		// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
		// Also you can just set TRUE to "TrialMode" property in code.
		//=========================================================================

		try {
			boolean trialMode = Utils.getTrialModeFlag();
			NLicenseManager.setTrialMode(trialMode);
			System.out.println("\tTrial mode: " + trialMode);
		} catch (IOException e) {
			e.printStackTrace();
		}

		LicenseManager.getInstance().addPropertyChangeListener(application);
		try {
			LicenseManager.getInstance().obtainComponents(LICENSES);
		} catch (Exception e) {
			SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(null, e.toString()); });
			return;
		}

		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				try {
					JFrame frame = new MainFrame();
					Dimension d = new Dimension(880, 770);
					frame.setSize(d);
					frame.setMinimumSize(d);
					frame.setPreferredSize(d);
					frame.setResizable(true);
					frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
					frame.setTitle("Devices Sample");
					frame.setLocationRelativeTo(null);
					frame.setVisible(true);
				} catch (Throwable e) {
					SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(null, e.toString()); });
				}
			}
		});
	}

	// =============================================
	// Private fields
	// =============================================

	private final ProgressMonitor progressMonitor;

	// =============================================
	// Private constructor
	// =============================================

	private DevicesSample() {
		progressMonitor = new ProgressMonitor(null, "", "", 0, LICENSES.size());
		UIManager.put("ProgressMonitor.progressText", "Obtaining licenses...");
	}

	// =============================================
	// Public methods
	// =============================================

	public void propertyChange(PropertyChangeEvent evt) {
		if (LicenseManager.PROGRESS_CHANGED_PROPERTY.equals(evt.getPropertyName())) {
			int progress = (Integer) evt.getNewValue();
			progressMonitor.setProgress(progress);
			String message = String.format("# of analyzed licenses: %d\n", progress);
			progressMonitor.setNote(message);
		}
	}

}
