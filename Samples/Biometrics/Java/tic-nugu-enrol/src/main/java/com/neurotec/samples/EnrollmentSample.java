package com.neurotec.samples;

import java.awt.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

import javax.swing.*;

import com.neurotec.licensing.NLicenseManager;
import com.neurotec.plugins.NDataFileManager;

import com.neurotec.samples.swing.LoginFrame;
import com.neurotec.samples.swing.MainFrame;

import com.neurotec.samples.Services.InitiDataService;
import com.neurotec.samples.controller.LoginController;
import com.neurotec.samples.util.LibraryManager;
import com.neurotec.samples.util.LicenseManager;
import com.neurotec.samples.util.Utils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;

@SpringBootApplication(scanBasePackages = "com.neurotec.samples")
@EnableJpaRepositories(basePackages = "com.neurotec.samples.repository")  // Package des repositories
@EntityScan(basePackages = "com.neurotec.samples.model")  // Package des entités
public  class EnrollmentSample implements PropertyChangeListener, CommandLineRunner {

	@Autowired
	private LoginController loginController;

	@Autowired
	private InitiDataService initiDataService;

	private static final Set<String> LICENSES ;

	static {
		LICENSES=new HashSet<String>(1);
		LICENSES.add("Biometrics.FingerExtraction");
		LICENSES.add("Biometrics.FingerSegmentation");
		LICENSES.add("Biometrics.Tools.NFIQ"); // Optionnel
	}


	// ===========================================================
	// Public static methods
	// ===========================================================

	/*public static void main2(String[] args) {
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
					//JFrame frame = new MainFrame();
					JFrame frame = new LoginFrame();

					Dimension d = new Dimension(500, 200); // Ajuste la taille selon ton besoin

					frame.setSize(d);
					frame.setMinimumSize(new Dimension(500, 200));
					frame.setMaximumSize(new Dimension(300, 200));

					frame.setPreferredSize(d);

					frame.setResizable(false);
					frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
					frame.setTitle("Tic-nugu");
					frame.setLocationRelativeTo(null);
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
					SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(null, e.toString()); });
				}
			}
		});
	}
*/
	// ===========================================================
	// Private fields
	// ===========================================================


	private final ProgressMonitor progressMonitor;

	public EnrollmentSample() {
		progressMonitor = new ProgressMonitor(null, "License obtain", "", 0, LICENSES.size());
	}

	public static void main(String[] args) {
		ConfigurableApplicationContext context = new SpringApplicationBuilder(EnrollmentSample.class)
				.headless(false)
				.run(args);

		// Lancer l'interface graphique Swing
		SwingUtilities.invokeLater(() -> {
			LoginController loginController = context.getBean(LoginController.class);
			loginController.init();
		});

		// Initialiser l'interface LookAndFeel et la bibliothèque
		Utils.setupLookAndFeel();
		LibraryManager.initLibraryPath();

		// Ajouter l'écouteur de propriété pour surveiller la progression des licences

		// Gestion des fichiers de données
		NDataFileManager.getInstance().addFile("Fingers.ndf");

		// Activer le mode essai pour les licences

		boolean trialMode = true;
		NLicenseManager.setTrialMode(trialMode);
		System.out.println("\tTrial mode: " + trialMode);
		LicenseManager.getInstance().addPropertyChangeListener(context.getBean(EnrollmentSample.class));
		try {
			LicenseManager.getInstance().obtainComponents(LICENSES);
			System.out.println("Licences obtenues avec succès.");
		} catch (IOException e) {
			e.printStackTrace();
			SwingUtilities.invokeLater(() -> JOptionPane.showMessageDialog(null, e.toString()));
		}


	}

	@Override
	public void run(String... args) throws Exception {
		initiDataService.create();




	}

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