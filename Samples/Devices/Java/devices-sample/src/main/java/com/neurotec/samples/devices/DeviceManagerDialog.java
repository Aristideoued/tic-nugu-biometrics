package com.neurotec.samples.devices;

import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;

import com.neurotec.devices.NDeviceManager;
import com.neurotec.devices.NDeviceType;

public final class DeviceManagerDialog extends JDialog implements ActionListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================

	private List<JCheckBox> listTypeCheckBoxes = new ArrayList<JCheckBox>();
	private NDeviceManager result;

	// =============================================
	// Private GUI controls
	// =============================================

	private JCheckBox chkAny;
	private JCheckBox chkCaptureDevice;
	private JCheckBox chkCamera;
	private JCheckBox chkMicrophone;
	private JCheckBox chkBiometricDevice;
	private JCheckBox chkFScanner;
	private JCheckBox chkFingerScanner;
	private JCheckBox chkPalmScanner;
	private JCheckBox chkIrisScanner;
	private JCheckBox chkSignatureScanner;
	private JCheckBox chkAutoPlug;

	private JButton buttonOK;
	private JButton buttonCancel;

	// ==============================================
	// Public constructor
	// ==============================================

	public DeviceManagerDialog(JFrame owner) {
		super(owner, true);
		initGUI();
		setDeviceType(NDeviceType.ANY);
	}

	// =============================================
	// Private methods
	// =============================================

	private void initGUI() {
		this.setTitle("New Device Manager");
		this.setIconImage(new BufferedImage(1, 1, BufferedImage.TYPE_INT_ARGB));
		this.setPreferredSize(new Dimension(290, 350));
		this.setResizable(false);

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		mainPanel.setBorder(BorderFactory.createEmptyBorder(2, 2, 2, 2));

		GridBagLayout deviceTypeLayout = new GridBagLayout();
		deviceTypeLayout.columnWidths = new int[] { 20, 20, 20, 200 };
		GridBagConstraints c = new GridBagConstraints();
		JPanel deviceTypesPanel = new JPanel(deviceTypeLayout);

		chkAny = new JCheckBox("Any");
		chkAny.putClientProperty("type", NDeviceType.ANY);
		chkAny.addActionListener(this);
		listTypeCheckBoxes.add(chkAny);

		chkCaptureDevice = new JCheckBox("Capture Device");
		chkCaptureDevice.putClientProperty("type", NDeviceType.CAPTURE_DEVICE);
		chkCaptureDevice.addActionListener(this);
		listTypeCheckBoxes.add(chkCaptureDevice);

		chkCamera = new JCheckBox("Camera");
		chkCamera.putClientProperty("type", NDeviceType.CAMERA);
		chkCamera.addActionListener(this);
		listTypeCheckBoxes.add(chkCamera);

		chkMicrophone = new JCheckBox("Microphone");
		chkMicrophone.putClientProperty("type", NDeviceType.MICROPHONE);
		chkMicrophone.addActionListener(this);
		listTypeCheckBoxes.add(chkMicrophone);

		chkBiometricDevice = new JCheckBox("Biometric device");
		chkBiometricDevice.putClientProperty("type", NDeviceType.BIOMETRIC_DEVICE);
		chkBiometricDevice.addActionListener(this);
		listTypeCheckBoxes.add(chkBiometricDevice);

		chkFScanner = new JCheckBox("F scanner");
		chkFScanner.putClientProperty("type", NDeviceType.FSCANNER);
		chkFScanner.addActionListener(this);
		listTypeCheckBoxes.add(chkFScanner);

		chkFingerScanner = new JCheckBox("Finger scanner");
		chkFingerScanner.putClientProperty("type", NDeviceType.FINGER_SCANNER);
		chkFingerScanner.addActionListener(this);
		listTypeCheckBoxes.add(chkFingerScanner);

		chkPalmScanner = new JCheckBox("Palm scanner");
		chkPalmScanner.putClientProperty("type", NDeviceType.PALM_SCANNER);
		chkPalmScanner.addActionListener(this);
		listTypeCheckBoxes.add(chkPalmScanner);

		chkIrisScanner = new JCheckBox("Iris sanner");
		chkIrisScanner.putClientProperty("type", NDeviceType.IRIS_SCANNER);
		chkIrisScanner.addActionListener(this);
		listTypeCheckBoxes.add(chkIrisScanner);

		chkSignatureScanner = new JCheckBox("Signature sanner");
		chkSignatureScanner.putClientProperty("type", NDeviceType.SIGNATURE_SCANNER);
		chkSignatureScanner.addActionListener(this);
		listTypeCheckBoxes.add(chkSignatureScanner);

		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridwidth = GridBagConstraints.REMAINDER;
		c.gridx = 0;
		c.gridy = 0;
		deviceTypesPanel.add(chkAny, c);

		c.gridx = 1;
		c.gridy = 1;
		deviceTypesPanel.add(chkCaptureDevice, c);

		c.gridx = 2;
		c.gridy = 2;
		deviceTypesPanel.add(chkCamera, c);

		c.gridx = 2;
		c.gridy = 3;
		deviceTypesPanel.add(chkMicrophone, c);

		c.gridx = 1;
		c.gridy = 4;
		deviceTypesPanel.add(chkBiometricDevice, c);

		c.gridx = 2;
		c.gridy = 5;
		deviceTypesPanel.add(chkFScanner, c);

		c.gridx = 3;
		c.gridy = 6;
		deviceTypesPanel.add(chkFingerScanner, c);

		c.gridx = 3;
		c.gridy = 7;
		deviceTypesPanel.add(chkPalmScanner, c);

		c.gridx = 2;
		c.gridy = 8;
		deviceTypesPanel.add(chkIrisScanner, c);
		
		c.gridx = 2;
		c.gridy = 9;
		deviceTypesPanel.add(chkSignatureScanner, c);

		deviceTypesPanel.setBorder(BorderFactory.createTitledBorder("Device types"));

		chkAutoPlug = new JCheckBox("Auto plug");
		Box autoPlugBox = Box.createHorizontalBox();
		autoPlugBox.add(chkAutoPlug);
		autoPlugBox.add(Box.createGlue());

		buttonOK = new JButton("OK");
		buttonOK.addActionListener(this);
		buttonCancel = new JButton("Cancel");
		buttonCancel.addActionListener(this);

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
		buttonPanel.add(Box.createGlue());
		buttonPanel.add(buttonOK);
		buttonPanel.add(Box.createHorizontalStrut(3));
		buttonPanel.add(buttonCancel);

		mainPanel.add(deviceTypesPanel);
		mainPanel.add(autoPlugBox);
		mainPanel.add(buttonPanel);
		this.getContentPane().add(mainPanel);
		this.pack();

	}

	// =============================================
	// Public methods
	// =============================================

	public EnumSet<NDeviceType> getDeviceTypes() {
		List<NDeviceType> types = new ArrayList<NDeviceType>();
		for (JCheckBox checkBox : listTypeCheckBoxes) {
			if (checkBox.isSelected()) {
				types.add((NDeviceType) checkBox.getClientProperty("type"));
			}
		}
		EnumSet<NDeviceType> deviceTypes = EnumSet.noneOf(NDeviceType.class);
		deviceTypes.addAll(types);
		return deviceTypes;
	}

	public NDeviceType getDeviceType() {
		NDeviceType value = NDeviceType.ANY;
		for (JCheckBox checkBox : listTypeCheckBoxes) {
			if (checkBox.isSelected()) {
				value = (NDeviceType) checkBox.getClientProperty("type");
			}
		}
		return value;
	}

	public void setDeviceType(NDeviceType deviceType) {
		for (JCheckBox checkBox : listTypeCheckBoxes) {
			checkBox.setSelected(deviceType == (NDeviceType) checkBox.getClientProperty("type"));
		}
	}

	public boolean isAutoPlug() {
		return chkAutoPlug.isSelected();
	}

	public void setAutoPlug(boolean autoPlug) {
		chkAutoPlug.setSelected(autoPlug);
	}

	public NDeviceManager showDialog() {
		setVisible(true);
		return result;
	}

	// =============================================
	// Event handling
	// =============================================

	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		if (source == buttonOK) {
			result = new NDeviceManager();
			result.setAutoPlug(isAutoPlug());
			result.setDeviceTypes(getDeviceTypes());
			setVisible(false);
			//TODO settings
			//			settings.DeviceTypes = form.DeviceTypes;
			//			settings.AutoPlug = form.AutoPlug;
			//			settings.AutoUpdate = form.AutoUpdate;
			//			settings.Save();
			this.dispose();
		} else if (source == buttonCancel) {
			this.dispose();
		}

	}

}
