package com.neurotec.samples;

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

import com.neurotec.jna.HNObject;
import com.neurotec.licensing.NLicenseManager;
import com.neurotec.plugins.NDataFileBuilder;
import com.neurotec.plugins.NDataFileManager;
import com.neurotec.samples.swing.Exemple;
import com.neurotec.samples.swing.MainFrame;
import com.neurotec.samples.util.LibraryManager;
import com.neurotec.samples.util.LicenseManager;
import com.neurotec.samples.util.Utils;

public final class EnrollmentSample implements PropertyChangeListener {

	// ===========================================================
	// Private static final fields
	// ===========================================================

	private static final Set<String> LICENSES;

	// ===========================================================
	// Static constructor
	// ===========================================================

	static {
		LICENSES = new HashSet<String>(1);
		LICENSES.add("Biometrics.FingerExtraction");
		LICENSES.add("Biometrics.FingerSegmentation");
		LICENSES.add("Biometrics.Tools.NFIQ"); // Optional.

	}

	// ===========================================================
	// Public static methods
	// ===========================================================

	public static void main(String[] args) {
		Utils.setupLookAndFeel();
		LibraryManager.initLibraryPath();
		EnrollmentSample sample = new EnrollmentSample();
		//NDataFileManager nDataFileManager = new NDataFileManager();
		NDataFileManager manager = NDataFileManager.getInstance();


		manager.addFile("Fingers.ndf");

		//=========================================================================
		// TRIAL MODE
		//=========================================================================
		// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
		// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
		// Also you can just set TRUE to "TrialMode" property in code.
		//=========================================================================

		//boolean trialMode = Utils.getTrialModeFlag();
		boolean trialMode=true;
		NLicenseManager.setTrialMode(trialMode);
		System.out.println("\tTrial mode: " + trialMode);

		LicenseManager.getInstance().addPropertyChangeListener(sample);
		try {
			LicenseManager.getInstance().obtainComponents(LICENSES);

		} catch (IOException e) {
			e.printStackTrace();
			SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(null, e.toString()); });
			return;
		}

		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				try {
					JFrame frame = new Exemple();
				/*	Dimension d = new Dimension(1015, 625);

					frame.setSize(d);
					frame.setMinimumSize(new Dimension(800, 600));
					frame.setPreferredSize(d);

					frame.setResizable(true);
					frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
					frame.setTitle("Tic-nugu");
					frame.setLocationRelativeTo(null);*/
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
					SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(null, e.toString()); });
				}
			}
		});
	}

	// ===========================================================
	// Private fields
	// ===========================================================

	private final ProgressMonitor progressMonitor;

	// ===========================================================
	// Private methods
	// ===========================================================

	private EnrollmentSample() {
		progressMonitor = new ProgressMonitor(null, "License obtain", "", 0, LICENSES.size());
	}

	// ===========================================================
	// Event handling
	// ===========================================================

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		if (LicenseManager.PROGRESS_CHANGED_PROPERTY.equals(evt.getPropertyName())) {
			int progress = (Integer) evt.getNewValue();
			progressMonitor.setProgress(progress);
			String message = String.format("# of analyzed licenses: %d\n", progress);
			progressMonitor.setNote(message);
		}
	}
}
