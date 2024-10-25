package com.neurotec.samples;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

import javax.swing.JOptionPane;
import javax.swing.ProgressMonitor;
import javax.swing.SwingUtilities;

import com.neurotec.licensing.NLicenseManager;
import com.neurotec.plugins.NDataFileManager;
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

	private static final Set<String> LICENSES = new HashSet<>();

	static {
		LICENSES.add("Biometrics.FingerExtraction");
		LICENSES.add("Biometrics.FingerSegmentation");
		LICENSES.add("Biometrics.Tools.NFIQ"); // Optionnel
	}

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
		LicenseManager.getInstance().addPropertyChangeListener(context.getBean(EnrollmentSample.class));

		// Gestion des fichiers de données
		NDataFileManager.getInstance().addFile("Fingers.ndf");

		// Activer le mode essai pour les licences
		boolean trialMode = true;
		NLicenseManager.setTrialMode(trialMode);
		System.out.println("\tTrial mode: " + trialMode);
	}

	@Override
	public void run(String... args) throws Exception {
		initiDataService.create();

		try {
			LicenseManager.getInstance().obtainComponents(LICENSES);
		} catch (IOException e) {
			e.printStackTrace();
			SwingUtilities.invokeLater(() -> JOptionPane.showMessageDialog(null, e.toString()));
		}

		System.out.println("Licences obtenues avec succès.");
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