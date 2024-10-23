package com.neurotec.samples.swing;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutionException;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;
import javax.swing.border.TitledBorder;

import com.neurotec.biometrics.NBiometricType;
import com.neurotec.biometrics.NFImpressionType;
import com.neurotec.biometrics.NFPosition;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.swing.NFingerView;
import com.neurotec.devices.NDevice;
import com.neurotec.devices.NFScanner;
import com.neurotec.event.ChangeEvent;
import com.neurotec.event.ChangeListener;
import com.neurotec.lang.NCore;
import com.neurotec.licensing.NLicense;
import com.neurotec.samples.Utilities;
import com.neurotec.samples.enrollment.DataProcessor;
import com.neurotec.samples.enrollment.EnrollmentDataModel;
import com.neurotec.samples.enrollment.EnrollmentSettings;
import com.neurotec.samples.enrollment.fingers.HandSegmentSelector;
import com.neurotec.samples.enrollment.fingers.Scenario;
import com.neurotec.samples.events.FingersPanelPropertyChangedListner;
import com.neurotec.samples.events.LongTaskListener;
import com.neurotec.samples.swing.controls.*;
import com.neurotec.samples.util.LicenseManager;
import com.neurotec.samples.util.Utils;
import com.neurotec.swing.AboutBox;
import com.neurotec.util.NPropertyBag;
import com.neurotec.util.event.NCollectionChangeEvent;
import com.neurotec.util.event.NCollectionChangeListener;

public final class MainFrame extends JFrame implements ActionListener {

	// ==============================================
	// Private classes
	// ==============================================

	private class FingersCollectionChangeListener implements NCollectionChangeListener {

		@Override
		public void collectionChanged(NCollectionChangeEvent e) {
			NFingerView view;
			switch (e.getAction()) {
			case ADD:
				List<?> newItems = e.getNewItems();
				for (Object finger : newItems) {
					view = getView((NFinger) finger);
					view.setFinger((NFinger) finger);
					((JPanel) view.getParent()).putClientProperty("TAG", view.getFinger());
				}
				break;
			case REMOVE:
				List<?> oldItems = e.getOldItems();
				for (Object finger : oldItems) {
					view = getView((NFinger) finger);
					view.setFinger(null);
					((JPanel) view.getParent()).putClientProperty("TAG", null);
				}
				break;
			case RESET:
				for (NFPosition position : slaps) {
					view = getView(position, false);
					view.setFinger(null);
					((JPanel) view.getParent()).putClientProperty("TAG", null);
				}
				for (NFPosition position : fingers) {
					view = getView(position, false);
					view.setFinger(null);
					view = getView(position, true);
					view.setFinger(null);
					((JPanel) view.getParent()).putClientProperty("TAG", null);
				}
				break;
			case MOVE:
			case REPLACE:
			default:
				break;
			}
			zoomViews();
		}

	}

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private GUI controls
	// ==============================================

	private JMenuItem menuItemNew;
	private JMenuItem menuItemSaveAll;
	private JMenuItem menuItemSaveTemplate;
	private JMenuItem menuItemSaveImages;
	private JMenuItem menuItemExit;

	private JMenu optionsMenu;

	private JMenuItem menuItemChangeScanner;
	private JMenuItem menuItemExtractionOptions;
	private JMenuItem menuItemEditRequiredInfo;

	private JMenuItem menuItemAbout;

	private JCheckBox chkPlainFingers;
	private JCheckBox chkSlaps;
	private JCheckBox chkRolledFingers;

	private JButton btnSartCapturing;

	private HandSegmentSelector fingerSelector;
	private FingersViewToolBar toolBar;

	private SlapsPanel slapsPanel;
	private FingersPanel normalFingersPanel;
	private FingersPanel rolledFingersPanel;
	private InfoPanel infoPanel;
	private SignaturePanel signaturePanel;

	// ==============================================
	// Private fields
	// ==============================================

	private boolean canCaptureSlaps;
	private boolean canCaptureRolled;
	private FingerCaptureFrame fingerCaptureFrame;
	private JPanel fingerSelectorPanel;
	private boolean newSubject = true;

	private EnrollmentDataModel model = EnrollmentDataModel.getInstance();

	private final NFPosition[] slaps = new NFPosition[] {NFPosition.PLAIN_LEFT_FOUR_FINGERS, NFPosition.PLAIN_RIGHT_FOUR_FINGERS, NFPosition.PLAIN_THUMBS};
	private final NFPosition[] leftFourFingers = new NFPosition[] {NFPosition.LEFT_LITTLE_FINGER, NFPosition.LEFT_RING_FINGER, NFPosition.LEFT_MIDDLE_FINGER, NFPosition.LEFT_INDEX_FINGER};
	private final NFPosition[] rightFourFingers = new NFPosition[] {NFPosition.RIGHT_INDEX_FINGER, NFPosition.RIGHT_MIDDLE_FINGER, NFPosition.RIGHT_RING_FINGER, NFPosition.RIGHT_LITTLE_FINGER};
	private final NFPosition[] thumbs = new NFPosition[] {NFPosition.LEFT_THUMB, NFPosition.RIGHT_THUMB};
	private final NFPosition[] fingers = new NFPosition[] {NFPosition.LEFT_LITTLE_FINGER, NFPosition.LEFT_RING_FINGER, NFPosition.LEFT_MIDDLE_FINGER, NFPosition.LEFT_INDEX_FINGER, NFPosition.LEFT_THUMB, NFPosition.RIGHT_THUMB, NFPosition.RIGHT_INDEX_FINGER, NFPosition.RIGHT_MIDDLE_FINGER, NFPosition.RIGHT_RING_FINGER, NFPosition.RIGHT_LITTLE_FINGER};

	// ==============================================
	// Public constructor
	// ==============================================

	public MainFrame() {
		super();

		addWindowListener(new WindowAdapter() {

			@Override
			public void windowOpened(WindowEvent e) {
				mainFormLoad();
			}

			@Override
			public void windowClosed(WindowEvent e) {
				EnrollmentSettings.getInstance().save();
			}

			@Override
			public void windowClosing(WindowEvent e) {
				mainFormFormClosing();
			}
		});

		addComponentListener(new ComponentAdapter() {

			@Override
			public void componentResized(ComponentEvent e) {
				zoomViews();
			}
		});

		setIconImage(Utils.createIconImage("images/Logo16x16.png"));
		initializeComponents();

	}

	// ==============================================
	// Private methods
	// ==============================================

	private void initializeComponents() {
		createMenuBar();

		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		JTabbedPane tabbedPane = new JTabbedPane();

		toolBar = new FingersViewToolBar();

		slapsPanel = new SlapsPanel();
		normalFingersPanel = new FingersPanel(toolBar);
		normalFingersPanel.addFingersPanelPropertyChangedListner(new FingersPanelPropertyChangedListner() {

			@Override
			public void checkboxPropertyChanged() {
				rolledFingersPanel.setShowOriginal(EnrollmentSettings.getInstance().isShowOriginal());
			}
		});
		rolledFingersPanel = new FingersPanel(toolBar);
		rolledFingersPanel.addFingersPanelPropertyChangedListner(new FingersPanelPropertyChangedListner() {

			@Override
			public void checkboxPropertyChanged() {
				normalFingersPanel.setShowOriginal(EnrollmentSettings.getInstance().isShowOriginal());
			}

		});
		infoPanel = new InfoPanel(this);
		signaturePanel = new SignaturePanel(this);

		tabbedPane.addTab("Informations", infoPanel);
		tabbedPane.addTab("Mains", slapsPanel);
		tabbedPane.addTab("Doigts", normalFingersPanel);
		tabbedPane.addTab("Doigts enrollés", rolledFingersPanel);
		tabbedPane.addTab("Signature", signaturePanel);
		

		contentPane.add(createTopPanel(), BorderLayout.BEFORE_FIRST_LINE);
		contentPane.add(tabbedPane, BorderLayout.CENTER);
		pack();
	}

	public void  setBtnStart(boolean st){
		btnSartCapturing.setEnabled(st);
	}
	private void createMenuBar() {
		JMenuBar menuBar = new JMenuBar();

		menuItemAbout = new JMenuItem("A propos");
		menuItemAbout.addActionListener(this);

		JMenu helpMenu = new JMenu("Aide");
		helpMenu.add(menuItemAbout);

		menuBar.add(createFileMenu());
		menuBar.add(createOptionsMenu());
		menuBar.add(helpMenu);

		setJMenuBar(menuBar);
	}

	private JMenu createFileMenu() {
		JMenu fileMenu = new JMenu("Fichier");

		menuItemNew = new JMenuItem("Nouveau");
		menuItemNew.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, Event.CTRL_MASK));
		menuItemNew.addActionListener(this);

		menuItemSaveAll = new JMenuItem("Enregistrer tout");
		menuItemSaveAll.addActionListener(this);

		menuItemSaveTemplate = new JMenuItem("Enregistrer Template");
		menuItemSaveTemplate.addActionListener(this);

		menuItemSaveImages = new JMenuItem("Enregistrer Images");
		menuItemSaveImages.addActionListener(this);

		menuItemExit = new JMenuItem("Quitter");
		menuItemExit.addActionListener(this);

		fileMenu.add(menuItemNew);
		fileMenu.addSeparator();
		fileMenu.add(menuItemSaveAll);
		fileMenu.add(menuItemSaveTemplate);
		fileMenu.add(menuItemSaveImages);
		fileMenu.addSeparator();
		fileMenu.add(menuItemExit);

		return fileMenu;
	}

	private JMenu createOptionsMenu() {
		optionsMenu = new JMenu("Options");

		menuItemChangeScanner = new JMenuItem("Changer de Scanner");
		menuItemChangeScanner.addActionListener(this);

		menuItemExtractionOptions = new JMenuItem("Options d'xtraction");
		menuItemExtractionOptions.addActionListener(this);

		menuItemEditRequiredInfo = new JMenuItem("Modifier les informations requises");
		menuItemEditRequiredInfo.addActionListener(this);

		optionsMenu.add(menuItemChangeScanner);
		optionsMenu.add(menuItemExtractionOptions);
		optionsMenu.add(menuItemEditRequiredInfo);

		return optionsMenu;
	}

	private JPanel createTopPanel() {
		JPanel topPanel = new JPanel();
		topPanel.setLayout(new BoxLayout(topPanel, BoxLayout.X_AXIS));

		JPanel capturingOptionsPanel = new JPanel();
		capturingOptionsPanel.setPreferredSize(new Dimension(145, 135));
		capturingOptionsPanel.setMaximumSize(new Dimension(145, 135));
		capturingOptionsPanel.setBorder(BorderFactory.createTitledBorder(""));

		GridBagLayout capturingOptionsLayout = new GridBagLayout();
		capturingOptionsLayout.columnWidths = new int[] {30, 90};
		capturingOptionsLayout.rowHeights = new int[] {30, 30, 30, 40};
		capturingOptionsPanel.setLayout(capturingOptionsLayout);

		chkPlainFingers = new JCheckBox("Un doigt");
		chkPlainFingers.addActionListener(this);

		chkSlaps = new JCheckBox("Tous les doigts");
		chkSlaps.addActionListener(this);

		chkRolledFingers = new JCheckBox("Capturer doigts enrollés");
		chkRolledFingers.addActionListener(this);

		btnSartCapturing = new JButton("Prendre empreintes");



		btnSartCapturing.addActionListener(this);

		GridBagUtils gridBagUtils = new GridBagUtils(GridBagConstraints.VERTICAL);
		gridBagUtils.setInsets(new Insets(2, 2, 2, 2));

		gridBagUtils.addToGridBagLayout(0, 0, 2, 1, capturingOptionsPanel, chkPlainFingers);
		gridBagUtils.addToGridBagLayout(1, 1, 1, 1, capturingOptionsPanel, chkSlaps);
		gridBagUtils.addToGridBagLayout(0, 2, 2, 1, capturingOptionsPanel, chkRolledFingers);
		gridBagUtils.addToGridBagLayout(0, 3, capturingOptionsPanel, btnSartCapturing);

		fingerSelectorPanel = new JPanel();
		fingerSelectorPanel.setPreferredSize(new Dimension(246, 135));
		fingerSelectorPanel.setMaximumSize(new Dimension(246, 135));

		fingerSelectorPanel.setBorder(BorderFactory.createTitledBorder("Cliquer sur les doigts manquants"));
		fingerSelectorPanel.setLayout(new BorderLayout());

		fingerSelector = new HandSegmentSelector();
		fingerSelector.setPreferredSize(new Dimension(275, 130));
		fingerSelector.setScenario(Scenario.ALL_PLAIN_FINGERS);
		fingerSelector.clearSelection();

		fingerSelectorPanel.add(fingerSelector, BorderLayout.CENTER);

		topPanel.add(capturingOptionsPanel);
		topPanel.add(Box.createHorizontalStrut(4));
		topPanel.add(fingerSelectorPanel);
		topPanel.add(Box.createGlue());
		return topPanel;
	}

	private void mainFormLoad() {
		toolBar.setVisible(false);
		EnrollmentSettings settings = EnrollmentSettings.getInstance();

		try {
			createBiometricClient();
			if (model.getBiometricClient() != null) {
				model.setBiometricClient(model.getBiometricClient());
				chkRolledFingers.setSelected(settings.isScanRolled());
				chkPlainFingers.setSelected(settings.isScanPlain());
				chkSlaps.setSelected(settings.isScanSlaps());
				normalFingersPanel.setShowOriginal(settings.isShowOriginal());
				rolledFingersPanel.setShowOriginal(settings.isShowOriginal());

				if (model.getBiometricClient().getFingerScanner() == null) {
					DeviceSelectDialog deviceSelectDialog = new DeviceSelectDialog(this);
					deviceSelectDialog.setVisible(true);
					if (!deviceSelectDialog.isDialogResultOk()) {
						mainFormFormClosing();
					} else {
						model.getBiometricClient().setFingerScanner(deviceSelectDialog.getSelectedDevice());
					}
				}
				onSelectedDeviceChanged(model.getBiometricClient().getFingerScanner());
			}
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
	}

	private void createBiometricClient() {
		EnrollmentSettings settings = EnrollmentSettings.getInstance();

		LongTaskListener listener = new LongTaskListener() {

			@Override
			public void processLongTask() {
				initilizingProcessLongTask();
			}
		};
		try {
			LongTaskDialog.runLongTask(this, listener, "Initialisation ...");
		} catch (InterruptedException e1) {
			e1.printStackTrace();
		} catch (ExecutionException e1) {
			e1.printStackTrace();
		}

		if (model.getBiometricClient() != null) {
			String preferedDeviceId = settings.getSelectedFScannerId();

			NDevice device = null;
			if (preferedDeviceId != null && !preferedDeviceId.equals("")) {
				if (model.getBiometricClient().getDeviceManager().getDevices().contains(preferedDeviceId)) {
					device = model.getBiometricClient().getDeviceManager().getDevices().get(preferedDeviceId);
				}
			}
			model.getBiometricClient().setFingerScanner((NFScanner) device);
			model.getBiometricClient().addCurrentBiometricCompletedListener(new ChangeListener() {

				@Override
				public void stateChanged(ChangeEvent e) {
					zoomViews();
				}
			});

		}

	}

	private void startCapturing() {
		if (newSubject) {
			model.setSubject(new NSubject());
			model.getSubject().getFingers().addCollectionChangeListener(new FingersCollectionChangeListener());
			createFingers(model.getSubject());
			if (model.getSubject().getFingers().size() == 0) {
				Utilities.showWarning(this, "Aucun doigt selectionné...");
				return;
			}
			else{
				Missing mss=new Missing();
				int nb=model.getSubject().getMissingFingers().size();
				mss.setMissingSize(nb);

				System.out.println( "Nombre de doigts manquants: "+mss.getMissingSize());

			}
		}
		newSubject = false;
		enableControls(false);
		fingerCaptureFrame = new FingerCaptureFrame(this);
		fingerCaptureFrame.addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent e) {
				enableControls(true);
			}

		});
		fingerCaptureFrame.setVisible(true);
	}

	private void mainFormFormClosing() {
		saveSettings();
		System.exit(0);
	}

	private void changeCapturingOptions(Object source) {
		if (source == chkPlainFingers && !chkPlainFingers.isSelected()) {
			chkSlaps.setSelected(false);
		}
		if (source == chkSlaps && chkSlaps.isSelected()) {
			chkPlainFingers.setSelected(true);
		}
		btnSartCapturing.setEnabled(chkRolledFingers.isSelected() || chkPlainFingers.isSelected());
	}

	private void startNewSubject() {
		model.clearModel();
		model.setSubject(null);
		fingerSelector.clear();

		infoPanel.onModelChanged();
		newSubject = true;
		enableControls(true);

	}

	private void startNewEnrollment() {


		if (!Utilities.showQuestion(this, "Toutes les images et les enregistrements seront effacés. Etes-vous sure ?")) {
			return;
		}
		startNewSubject();
	}

	private void changeScanner() {
		DeviceSelectDialog deviceSelectDialog = new DeviceSelectDialog(this);

		deviceSelectDialog.setVisible(true);
		if (deviceSelectDialog.isDialogResultOk()) {
			if (model.getBiometricClient().getFingerScanner() != deviceSelectDialog.getSelectedDevice()) {
				onSelectedDeviceChanged(deviceSelectDialog.getSelectedDevice());
			}
		}
	}

	private void showOptions() {
		ExtractionOptionsDialog extractionOptionsDialog = new ExtractionOptionsDialog(this);
		extractionOptionsDialog.setVisible(true);
	}

	private void editRequiredInfo() {
		EditInfoDialog editInfoDialog = new EditInfoDialog(this);
		editInfoDialog.setVisible(true);
		if (!editInfoDialog.isDialogResultOk()) {
			return;
		}
		infoPanel.onModelChanged();
	}

	private NFingerView getView(NFPosition position, boolean isRolled) {
		if (position == NFPosition.PLAIN_LEFT_FOUR_FINGERS || position == NFPosition.PLAIN_RIGHT_FOUR_FINGERS || position == NFPosition.PLAIN_THUMBS) {
			return slapsPanel.getView(position);
		} else if (isRolled) {
			return rolledFingersPanel.getView(position);
		} else {
			return normalFingersPanel.getView(position);
		}

	}

	private NFingerView getView(NFinger finger) {
		NFPosition position = finger.getPosition();
		boolean isRolled = finger.getImpressionType().isRolled();
		return getView(position, isRolled);
	}

	public void createFingers(NSubject subject) {
		List<NFPosition> missingFingers = fingerSelector.getMissingPositions();
		for (NFPosition item : missingFingers) {
			subject.getMissingFingers().add(item);
		}

		List<NFPosition> availableFingers = new ArrayList<NFPosition>();
		for (NFPosition item : fingers) {
			if (!missingFingers.contains(item)) {
				availableFingers.add(item);
			}
		}

		if (chkSlaps.isSelected()) {
			Map<NFPosition, NFPosition[]> slapsChildPositions = new HashMap<NFPosition, NFPosition[]>();
			slapsChildPositions.put(NFPosition.PLAIN_LEFT_FOUR_FINGERS, leftFourFingers);
			slapsChildPositions.put(NFPosition.PLAIN_RIGHT_FOUR_FINGERS, rightFourFingers);
			slapsChildPositions.put(NFPosition.PLAIN_THUMBS, thumbs);

			for (NFPosition position : slaps) {
				int childCount = 0;
				int missingChildCount = 0;
				NFPosition[] childPositions = slapsChildPositions.get(position);
				for (NFPosition childPostion : childPositions) {
					childCount++;
					if (missingFingers.contains(childPostion)) {
						missingChildCount++;
					}
				}
				if (childCount > 0 && childCount != missingChildCount) {
					NFinger finger = new NFinger();
					finger.setPosition(position);
					subject.getFingers().add(finger);
				}
			}
		} else if (chkPlainFingers.isSelected()) {
			for (NFPosition position : availableFingers) {
				NFinger finger = new NFinger();
				finger.setPosition(position);
				subject.getFingers().add(finger);
			}
		}

		if (chkRolledFingers.isSelected()) {
			for (NFPosition position : availableFingers) {
				NFinger finger = new NFinger();
				finger.setPosition(position);
				finger.setImpressionType(NFImpressionType.LIVE_SCAN_ROLLED);
				subject.getFingers().add(finger);
			}
		}

	}

	private void onSelectedDeviceChanged(NFScanner newDevice) {
		canCaptureRolled = false;
		canCaptureSlaps = false;
		if (newDevice != null) {
			for (NFPosition item : newDevice.getSupportedPositions()) {
				if (item.isFourFingers()) {
					canCaptureSlaps = true;
					break;
				}
			}
			for (NFImpressionType item : newDevice.getSupportedImpressionTypes()) {
				if (item.isRolled()) {
					canCaptureRolled = true;
					break;
				}
			}
		}

		if (model.getBiometricClient().getFingerScanner() != null && model.getBiometricClient().getFingerScanner() != newDevice) {
			if (Utilities.showQuestion(this, "Le changement de scanner effecera toutes les données actuellement capturées. Continuer?")) {
				startNewSubject();
			} else {
				return;
			}
		}

		model.getBiometricClient().setFingerScanner(newDevice);
		if (!canCaptureSlaps) {
			chkSlaps.setSelected(false);
		}

		if (!canCaptureRolled) {
			chkRolledFingers.setSelected(false);
		}
		enableControls(true);
		saveSettings();
		setFingerSelectorScenario();

	}

	private void setFingerSelectorScenario() {
		EnrollmentSettings settings = EnrollmentSettings.getInstance();
		if (settings.isScanPlain() || settings.isScanSlaps()) {
			fingerSelector.setScenario(Scenario.ALL_PLAIN_FINGERS);
		} else if (settings.isScanRolled()) {
			fingerSelector.setScenario(Scenario.ALL_ROLLED_FINGERS);
		}
		fingerSelector.clearSelection();
	}

	private void saveSettings() {
		if (model.getBiometricClient() != null) {
			EnrollmentSettings settings = EnrollmentSettings.getInstance();
			if (model.getBiometricClient().getFingerScanner() != null) {
				settings.setSelectedFScannerId(model.getBiometricClient().getFingerScanner().getId());
			} else {
				settings.setSelectedFScannerId(null);
			}
			settings.setScanRolled(chkRolledFingers.isSelected());
			settings.setScanSlaps(chkSlaps.isSelected());
			settings.setScanPlain(chkPlainFingers.isSelected());
			settings.setShowOriginal(normalFingersPanel.isShowOriginal());

			NPropertyBag propertyBag = new NPropertyBag();
			model.getBiometricClient().captureProperties(propertyBag);
			settings.setClientProperties(propertyBag.toString());

			settings.save();

		}
	}

	private void enableControls(boolean enable) {
		btnSartCapturing.setEnabled(enable && (chkRolledFingers.isSelected() || chkPlainFingers.isSelected()));
		chkPlainFingers.setEnabled(enable && newSubject);
		chkRolledFingers.setEnabled(canCaptureRolled && enable && newSubject);
		chkSlaps.setEnabled(canCaptureSlaps && enable && newSubject);
		fingerSelector.setEnabled(enable && newSubject);
		fingerSelectorPanel.setEnabled(enable && newSubject);
		TitledBorder title = (TitledBorder) fingerSelectorPanel.getBorder();
		if (enable && newSubject) {
			title.setTitleColor(Color.BLACK);
		} else {
			title.setTitleColor(Color.GRAY);
		}
		menuItemChangeScanner.setEnabled(enable);
		optionsMenu.setEnabled(enable);
		menuItemNew.setEnabled(enable);
		menuItemSaveAll.setEnabled(enable);
		menuItemSaveTemplate.setEnabled(enable);
		menuItemSaveImages.setEnabled(enable);
	}

	private void zoomViews() {
		normalFingersPanel.zoomViews();
		rolledFingersPanel.zoomViews();
	}

	// ==============================================
	// Public methods
	// ==============================================

	@Override
	public void actionPerformed(ActionEvent ev) {
		Object source = ev.getSource();
		if (source == menuItemNew) {
			startNewEnrollment();
		} else if (source == menuItemSaveAll) {
			DataProcessor.getInstance().saveAll(this);
		} else if (source == menuItemSaveTemplate) {
			DataProcessor.getInstance().saveTemplate(this);
		} else if (source == menuItemSaveImages) {
			DataProcessor.getInstance().saveImages(this);
		} else if (source == menuItemExit) {
			mainFormFormClosing();
		} else if (source == menuItemChangeScanner) {
			changeScanner();
		} else if (source == menuItemExtractionOptions) {
			showOptions();
		} else if (source == menuItemEditRequiredInfo) {
			editRequiredInfo();
		} else if (source == menuItemAbout) {
			AboutBox.show();
		} else if (source == btnSartCapturing) {
			startCapturing();
		} else if (source == chkPlainFingers || source == chkSlaps || source == chkRolledFingers) {
			changeCapturingOptions(source);
		}
	}

	public void initilizingProcessLongTask() {
		boolean isFingerQualityAssesmentActivated = false;
		try {
			isFingerQualityAssesmentActivated = NLicense.isComponentActivated("Biometrics.FingerQualityAssessmentBase");
		} catch (IOException e) {
			e.printStackTrace();
		}
		NBiometricClient client = new NBiometricClient();

		String propertiesString = EnrollmentSettings.getInstance().getClientProperties();
		NPropertyBag propertyBag = NPropertyBag.parse(propertiesString);
		propertyBag.applyTo(client);

		client.setBiometricTypes(EnumSet.of(NBiometricType.FINGER, NBiometricType.FACE));
		client.setFingersReturnBinarizedImage(true);
		client.setUseDeviceManager(true);
		client.setFingersCalculateNFIQ(isFingerQualityAssesmentActivated);

		client.initialize();
		model.setBiometricClient(client);
	}

}
