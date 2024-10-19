package com.neurotec.samples.devices;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Toolkit;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.EventObject;
import java.util.List;
import java.util.NoSuchElementException;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.SwingUtilities;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellRenderer;

import com.neurotec.biometrics.NBiometricEngineTypes;
import com.neurotec.biometrics.NBiometricType;
import com.neurotec.biometrics.NBiometricTypes;
import com.neurotec.biometrics.NEPosition;
import com.neurotec.biometrics.NFImpressionType;
import com.neurotec.biometrics.NFPosition;
import com.neurotec.devices.NBiometricDevice;
import com.neurotec.devices.NCamera;
import com.neurotec.devices.NCaptureDevice;
import com.neurotec.devices.NDevice;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NFScanner;
import com.neurotec.devices.NIrisScanner;
import com.neurotec.devices.NMicrophone;
import com.neurotec.devices.NSignatureScanner;
import com.neurotec.lang.NCore;
import com.neurotec.media.NAudioFormat;
import com.neurotec.media.NMediaFormat;
import com.neurotec.media.NVideoFormat;
import com.neurotec.plugins.NPlugin;
import com.neurotec.samples.devices.events.CustomizeFormatListener;
import com.neurotec.samples.util.LicenseManager;
import com.neurotec.samples.util.Utils;
import com.neurotec.swing.AboutBox;
import com.neurotec.swing.NPropertyGrid;
import com.neurotec.swing.PluginManagerBox;
import com.neurotec.util.event.NCollectionChangeEvent;
import com.neurotec.util.event.NCollectionChangeListener;

public final class MainFrame extends JFrame implements ActionListener, NCollectionChangeListener, TreeSelectionListener, CustomizeFormatListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;
	private static final String APP_NAME = "Device Manager";

	// ==============================================
	// Private static methods
	// ==============================================

	private int getIndexOfJComboBoxItem(JComboBox cmbBox, Object item) {
		for (int i = 0; i < cmbBox.getItemCount(); i++) {
			if (cmbBox.getItemAt(i).equals(item)) {
				return i;
			}
		}
		return -1;
	}

	// ==============================================
	// Private fields
	// ==============================================

	private NDeviceManager deviceManager;
	private List<CaptureFrame> captureFrames = new ArrayList<CaptureFrame>();
	private List<NFPosition> biometricDevicePositionList = new ArrayList<NFPosition>();
	private String logText = "";

	// ==============================================
	// Private GUI controls
	// ==============================================

	private JTextArea logTextPane;
	private JTree devicesTree;
	private DefaultMutableTreeNode devicesTreeRoot;

	private JComboBox cmbBiometricDeviceImpressionType;
	private JComboBox cmbBiometricDevicePosition;

	private JCheckBox chkLL;
	private JCheckBox chkLR;
	private JCheckBox chkLM;
	private JCheckBox chkLI;
	private JCheckBox chkLT;
	private JCheckBox chkRL;
	private JCheckBox chkRR;
	private JCheckBox chkRM;
	private JCheckBox chkRI;
	private JCheckBox chkRT;

	private JTextField txtMiliSec;
	private JComboBox cmbFormats;
	private JCheckBox chkGatherImages;
	private JCheckBox chkAutomatic;
	private JCheckBox chkUseTimeout;
	private JLabel lblMiliSec;
	private JButton buttonDeviceCapture;
	private JButton buttonCustomizeFormat;
	private JButton buttonStartSequence;
	private JButton buttonEndSequence;
	private JMenuItem menuItemAbout;
	private JMenuItem menuItemConnect;
	private JMenuItem menuItemDisconnect;
	private JMenuItem menuItemShowPlugin;
	private JMenuItem menuItemExit;
	private JMenuItem menuItemClose;
	private JMenuItem menuItemNew;
	private NPropertyGrid devicesPropertyGrid;

	// ==============================================
	// Public constructor
	// ==============================================

	public MainFrame() {
		initGUI();
		onDeviceManagerChanged();
	}

	// ==============================================
	// Private methods
	// ==============================================

	private void initGUI() {
		setIconImage(Utils.createIconImage("images/Logo16x16.png"));
		this.addComponentListener(new ComponentAdapter() {
			@Override
			public void componentShown(ComponentEvent e) {
				newDeviceManager();
			}
		});
		this.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosed(WindowEvent e) {
				CaptureFrame[] captureFramesCopy = captureFrames.toArray(new CaptureFrame[captureFrames.size()]);
				for (CaptureFrame frame : captureFramesCopy) {
					frame.dispose();
				}
				closeDeviceManager();
			}
		});
		createMenuBar();

		devicesTreeRoot = new DefaultMutableTreeNode();
		devicesTree = new JTree(devicesTreeRoot);
		DefaultTreeCellRenderer renderer = new DefaultTreeCellRenderer();
		renderer.setClosedIcon(null);
		renderer.setOpenIcon(null);
		devicesTree.setCellRenderer(renderer);
		devicesTree.addTreeSelectionListener(this);

		JScrollPane devicesTreeScrollPane = new JScrollPane(devicesTree, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

		JPanel propertiesPanel = new JPanel(new BorderLayout());
		propertiesPanel.setMinimumSize(new Dimension(0, 0));
		devicesPropertyGrid = new NPropertyGrid();
		propertiesPanel.add(devicesPropertyGrid, BorderLayout.CENTER);

		logTextPane = new JTextArea();
		logTextPane.setMinimumSize(new Dimension(0, 0));
		logTextPane.setLineWrap(true);
		logTextPane.setWrapStyleWord(true);
		logTextPane.setEditable(false);
		JScrollPane logScrollPane = new JScrollPane(logTextPane, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

		JSplitPane mainSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
		JSplitPane topSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		topSplitPane.setDividerLocation(260);
		topSplitPane.setDividerSize(1);
		topSplitPane.setLeftComponent(devicesTreeScrollPane);
		topSplitPane.setRightComponent(createTopRightPanel());

		JSplitPane bottomSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		bottomSplitPane.setDividerLocation(260);
		bottomSplitPane.setDividerSize(1);
		bottomSplitPane.setLeftComponent(propertiesPanel);
		bottomSplitPane.setRightComponent(logScrollPane);

		mainSplitPane.setDividerLocation(400);
		mainSplitPane.setDividerSize(1);
		mainSplitPane.setLeftComponent(topSplitPane);
		mainSplitPane.setRightComponent(bottomSplitPane);
		this.getContentPane().add(mainSplitPane);
		this.pack();
	}

	private void createMenuBar() {
		JMenuBar menuBar = new JMenuBar();

		JMenu menuDeviceManager = new JMenu("Device manager");

		menuItemNew = new JMenuItem("New");
		menuItemNew.addActionListener(this);
		menuDeviceManager.add(menuItemNew);

		menuItemClose = new JMenuItem("Close");
		menuItemClose.addActionListener(this);
		menuDeviceManager.add(menuItemClose);

		menuDeviceManager.addSeparator();

		menuItemExit = new JMenuItem("Exit");
		menuItemExit.addActionListener(this);
		menuDeviceManager.add(menuItemExit);

		JMenu menuDevice = new JMenu("Device");
		menuItemConnect = new JMenuItem("Connect...");
		menuItemConnect.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				connectToDevice();
			}
		});
		menuDevice.add(menuItemConnect);
		menuItemDisconnect = new JMenuItem("Disconnect");
		menuItemDisconnect.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				disconnectFromDevice();
			}
		});
		menuDevice.add(menuItemDisconnect);

		menuDevice.addSeparator();

		menuItemShowPlugin = new JMenuItem("Show plugin");
		menuItemShowPlugin.addActionListener(this);
		menuDevice.add(menuItemShowPlugin);

		JMenu menuHelp = new JMenu("Help");
		menuItemAbout = new JMenuItem(AboutBox.getName());
		menuItemAbout.addActionListener(this);
		menuHelp.add(menuItemAbout);
		menuBar.add(menuDeviceManager);
		menuBar.add(menuDevice);
		menuBar.add(menuHelp);
		this.setJMenuBar(menuBar);
	}

	private JPanel createTopRightPanel() {
		JPanel topRightPanel = new JPanel();
		topRightPanel.setMinimumSize(new Dimension(0, 0));
		topRightPanel.setBorder(BorderFactory.createEmptyBorder(3, 3, 3, 3));
		cmbBiometricDeviceImpressionType = new JComboBox();
		cmbBiometricDeviceImpressionType.addActionListener(this);
		cmbBiometricDevicePosition = new JComboBox();

		chkAutomatic = new JCheckBox("Automatic");
		chkAutomatic.setSelected(true);
		chkUseTimeout = new JCheckBox("Use timeout");
		chkUseTimeout.addActionListener(this);

		chkGatherImages = new JCheckBox("Gather images");

		txtMiliSec = new JTextField("0");
		txtMiliSec.setPreferredSize(new Dimension(65, 20));
		txtMiliSec.setHorizontalAlignment(JTextField.TRAILING);
		txtMiliSec.setEnabled(false);
		lblMiliSec = new JLabel("ms");

		cmbFormats = new JComboBox();
		buttonCustomizeFormat = new JButton("Custom...");
		buttonCustomizeFormat.addActionListener(this);

		buttonDeviceCapture = new JButton("Capture");
		buttonDeviceCapture.addActionListener(this);

		buttonStartSequence = new JButton("Start sequence");
		buttonStartSequence.addActionListener(this);

		buttonEndSequence = new JButton("End sequence");
		buttonEndSequence.addActionListener(this);

		GridBagConstraints c = new GridBagConstraints();
		GridBagLayout topRightLayout = new GridBagLayout();
		topRightLayout.columnWidths = new int[] { 120, 35, 50, 50, 71, 87, 92, 25 };
		topRightLayout.rowHeights = new int[] { 25, 25, 20, 20, 20, 20, 20, 180 };
		topRightPanel.setBorder(BorderFactory.createEmptyBorder(3, 3, 3, 3));
		topRightPanel.setLayout(topRightLayout);
		c.fill = GridBagConstraints.HORIZONTAL;
		c.anchor = GridBagConstraints.SOUTH;

		c.gridx = 0;
		c.gridy = 0;
		c.gridwidth = 4;
		topRightPanel.add(cmbBiometricDeviceImpressionType, c);

		c.gridx = 0;
		c.gridy = 1;
		c.gridwidth = 4;
		topRightPanel.add(cmbBiometricDevicePosition, c);

		c.gridx = 4;
		c.gridy = 0;
		c.gridwidth = 3;
		c.gridheight = 3;
		topRightPanel.add(createFingerPositionsPanel(), c);

		c.gridwidth = 1;
		c.gridheight = 1;
		c.gridx = 6;
		c.gridy = 0;
		topRightPanel.add(new JLabel(), c);

		c.gridx = 0;
		c.gridy = 2;
		topRightPanel.add(chkAutomatic, c);

		c.gridx = 0;
		c.gridy = 3;
		topRightPanel.add(chkUseTimeout, c);

		c.gridx = 1;
		c.gridy = 3;
		c.gridwidth = 2;
		topRightPanel.add(txtMiliSec, c);

		c.gridx = 3;
		c.gridy = 3;
		c.gridwidth = 1;
		topRightPanel.add(lblMiliSec, c);

		c.gridx = 0;
		c.gridy = 4;
		topRightPanel.add(chkGatherImages, c);

		c.gridx = 0;
		c.gridy = 5;
		c.gridwidth = 5;
		topRightPanel.add(cmbFormats, c);

		c.gridx = 5;
		c.gridy = 5;
		c.gridwidth = 1;
		topRightPanel.add(buttonCustomizeFormat, c);

		c.gridx = 0;
		c.gridy = 6;
		topRightPanel.add(buttonDeviceCapture, c);

		c.gridx = 2;
		c.gridy = 6;
		c.gridwidth = 2;
		topRightPanel.add(buttonStartSequence, c);

		c.gridx = 4;
		c.gridy = 6;
		c.gridwidth = 1;
		topRightPanel.add(buttonEndSequence, c);

		return topRightPanel;
	}

	private JPanel createFingerPositionsPanel() {
		chkLL = new JCheckBox("LL");
		chkLR = new JCheckBox("LR");
		chkLM = new JCheckBox("LM");
		chkLI = new JCheckBox("LI");
		chkLT = new JCheckBox("LT");

		chkRL = new JCheckBox("RL");
		chkRR = new JCheckBox("RR");
		chkRM = new JCheckBox("RM");
		chkRI = new JCheckBox("RI");
		chkRT = new JCheckBox("RT");

		JPanel leftPositionsPanel = new JPanel();
		leftPositionsPanel.setPreferredSize(new Dimension(130, 70));
		GridBagLayout leftPositionsGridBagLayout = new GridBagLayout();
		leftPositionsGridBagLayout.rowWeights = new double[] { 0.2, 0.2, 0.2, 0.2, 0.2 };
		leftPositionsGridBagLayout.columnWidths = new int[] { 20, 20, 25, 20, 40 };
		leftPositionsPanel.setLayout(leftPositionsGridBagLayout);

		JPanel rightPositionsPanel = new JPanel();
		rightPositionsPanel.setPreferredSize(new Dimension(130, 70));
		GridBagLayout rightPositionsGridBagLayout = new GridBagLayout();
		rightPositionsGridBagLayout.rowWeights = new double[] { 0.2, 0.2, 0.2, 0.2, 0.2 };
		rightPositionsGridBagLayout.columnWidths = new int[] { 20, 20, 25, 20, 40 };
		rightPositionsPanel.setLayout(rightPositionsGridBagLayout);

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridwidth = GridBagConstraints.RELATIVE;
		c.gridx = 2;
		c.gridy = 0;
		leftPositionsPanel.add(chkLM, c);

		c.gridx = 2;
		c.gridy = 0;
		rightPositionsPanel.add(chkRM, c);

		c.gridx = 1;
		c.gridy = 1;
		leftPositionsPanel.add(chkLR, c);

		c.gridx = 3;
		c.gridy = 2;
		leftPositionsPanel.add(chkLI, c);

		c.gridx = 1;
		c.gridy = 2;
		rightPositionsPanel.add(chkRI, c);

		c.gridx = 3;
		c.gridy = 1;
		rightPositionsPanel.add(chkRR, c);

		c.gridx = 0;
		c.gridy = 3;
		leftPositionsPanel.add(chkLL, c);

		c.gridx = 4;
		c.gridy = 3;
		rightPositionsPanel.add(chkRL, c);

		c.gridx = 4;
		c.gridy = 4;
		leftPositionsPanel.add(chkLT, c);

		c.gridx = 0;
		c.gridy = 4;
		rightPositionsPanel.add(chkRT, c);

		JPanel positionsPanel = new JPanel(new FlowLayout());
		positionsPanel.add(leftPositionsPanel);
		positionsPanel.add(rightPositionsPanel);
		return positionsPanel;
	}

	private void log(String str) {
		StringBuilder logTextBuilder = new StringBuilder();
		logTextBuilder.append(logText);
		logTextBuilder.append(str);
		logTextBuilder.append("\n");
		logText = logTextBuilder.toString();
		logTextPane.setText(logText);
	}

	private void log(String format, Object... args) {
		log(String.format(format, args));
	}

	private void updateDeviceList() {
		devicesTree.setSelectionPath(null);
		devicesTreeRoot.removeAllChildren();
		devicesTree.setRootVisible(true);
		if (deviceManager != null) {
			for (NPlugin plugin : (NPlugin[])NDeviceManager.getPluginManager().getPlugins().toArray()) {
				System.out.println(String.format("Plugin => %s. Error => %s", plugin.getFileName(), plugin.getError()));
			}
			for (NDevice device : (NDevice[])deviceManager.getDevices().toArray()) {
				if (device.getParent() == null) {
					foundDevice(devicesTreeRoot, device);
				}
			}
		}
		devicesTree.expandRow(0);
		devicesTree.setRootVisible(false);
		devicesTree.setShowsRootHandles(true);
		if (devicesTreeRoot.getChildCount() != 0) {
			devicesTree.setSelectionRow(0);
		} else {
			try {
				onSelectedDeviceChanged();
			} catch (Exception e) {
				SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, e.toString()); });
			}
		}
		devicesTree.updateUI();
		/*
		 * SwingUtilities.invokeLater(new Runnable() {
		 *
		 * public void run() {
		 * devicesTree.updateUI();
		 * }
		 * });
		 */
	}

	private void onDeviceManagerChanged() {
		updateDeviceList();
		if (deviceManager != null) {
			deviceManager.getDevices().addCollectionChangeListener(this);
		}

		menuItemClose.setEnabled(deviceManager != null);
		if (deviceManager == null) {
			this.setTitle(APP_NAME);
		} else {
			this.setTitle(String.format("%s (Device types: %s)", APP_NAME, deviceManager.getDeviceTypes()));
			devicesTree.setSelectionRow(0);
		}
	}

	private DefaultMutableTreeNode getDeviceNode(NDevice device, Enumeration<DefaultMutableTreeNode> nodes) {
		while (nodes.hasMoreElements()) {
			DefaultMutableTreeNode node = nodes.nextElement();
			if (node.getUserObject().equals(device)) {
				return node;
			}
			@SuppressWarnings("unchecked")
			DefaultMutableTreeNode subNode = getDeviceNode(device, (Enumeration<DefaultMutableTreeNode>)(Object)node.children());
			if (subNode != null) {
				return subNode;
			}
		}
		return null;
	}

	@SuppressWarnings("unchecked")
	private DefaultMutableTreeNode getDeviceNode(NDevice device) {
		return getDeviceNode(device, (Enumeration<DefaultMutableTreeNode>)(Object)devicesTreeRoot.children());
	}

	private DefaultMutableTreeNode createDeviceNode(NDevice device) {
		DefaultMutableTreeNode deviceTreeNode = new DefaultMutableTreeNode(device);
		return deviceTreeNode;
	}

	private void foundDevice(DefaultMutableTreeNode root, NDevice device) {
		log("Found device: %s", device.getId());
		DefaultMutableTreeNode deviceTreeNode = createDeviceNode(device);
		root.add(deviceTreeNode);
		for (NDevice child : device.getChildren()) {
			foundDevice(deviceTreeNode, child);
		}
	}

	private void addDevice(NDevice device) {
		log("Added device: %s", device.getId());
		DefaultMutableTreeNode deviceTreeNode = createDeviceNode(device);
		if (devicesTree.getRowCount() == 0) {
			devicesTree.setRootVisible(true);
		}
		if (device.getParent() == null) {
			devicesTreeRoot.add(deviceTreeNode);
		} else {
			DefaultMutableTreeNode parentTreeNode = getDeviceNode(device.getParent());
			if (parentTreeNode != null) {
				parentTreeNode.add(deviceTreeNode);

			}
		}
		if (devicesTree.isRootVisible()) {
			devicesTree.expandRow(0);
			devicesTree.setRootVisible(false);
		}
		devicesTree.updateUI();
		devicesTree.setSelectionRow(devicesTree.getRowCount() - 1);
		for (NDevice child : device.getChildren()) {
			DefaultMutableTreeNode childTreeNode = getDeviceNode(child);
			if (childTreeNode != null) {
				DefaultMutableTreeNode parent;
				if (childTreeNode.getParent() == null) {
					parent = devicesTreeRoot;
				} else {
					parent = (DefaultMutableTreeNode) childTreeNode.getParent();
				}
				parent.remove(childTreeNode);
				deviceTreeNode.add(childTreeNode);
			}
		}
	}

	private void removeDevice(NDevice device) {
		for (CaptureFrame cf : captureFrames) {
			if (cf.getDevice().equals(device)) {
				cf.waitForCaptureToFinish();
			}
		}
		log("Removed device: %s", device.getId());
		DefaultMutableTreeNode deviceTreeNode = getDeviceNode(device);
		DefaultMutableTreeNode selectedNode = (DefaultMutableTreeNode) devicesTree.getSelectionPath().getLastPathComponent();
		int selectedRow = -1;
		if (devicesTree.getSelectionRows().length > 0) {
			selectedRow = devicesTree.getSelectionRows()[0];
		}
		boolean isSelected = selectedNode == deviceTreeNode;
		DefaultMutableTreeNode[] childTreeNodes = new DefaultMutableTreeNode[deviceTreeNode.getChildCount()];
		for (int i = deviceTreeNode.getChildCount() - 1; i >= 0; i--) {
			childTreeNodes[i] = (DefaultMutableTreeNode) deviceTreeNode.getChildAt(i);
		}
		deviceTreeNode.removeAllChildren();
		for (DefaultMutableTreeNode child : childTreeNodes) {
			devicesTreeRoot.add(child);
		}

		if (isSelected) {
			if (devicesTree.getRowCount() == 1) {
				devicesTree.clearSelection();
			} else if (devicesTree.getRowCount() > selectedRow + 1) {
				devicesTree.setSelectionRow(selectedRow + 1);
			} else if (selectedRow != 0) {
				devicesTree.setSelectionRow(0);
			}
		}

		DefaultMutableTreeNode parent = (DefaultMutableTreeNode) deviceTreeNode.getParent();
		parent.remove(deviceTreeNode);

		devicesTree.updateUI();
		devicesPropertyGrid.updateUI();
	}

	private NDevice getSelectedDevice() {
		if (devicesTree.getSelectionPath() != null) {
			return (NDevice) ((DefaultMutableTreeNode) devicesTree.getSelectionPath().getLastPathComponent()).getUserObject();
		}
		return null;
	}

	private void onSelectedDeviceChanged() {
		devicesPropertyGrid.setVisible(false);
		NDevice device = getSelectedDevice();
		if (device != null && (device.isDisposed() || !device.isAvailable())) {
			device = null;
		}
		NCaptureDevice captureDevice = null;
		if (device instanceof NCaptureDevice) {
			captureDevice = (NCaptureDevice) device;
		}
		NCamera camera = null;
		if (device instanceof NCamera) {
			camera = (NCamera) device;
		}
		NMicrophone microphone = null;
		if (device instanceof NMicrophone) {
			microphone = (NMicrophone) device;
		}
		NBiometricDevice biometricDevice = null;
		if (device instanceof NBiometricDevice) {
			biometricDevice = (NBiometricDevice) device;
		}
		NFScanner fScanner = null;
		if (device instanceof NFScanner) {
			fScanner = (NFScanner) device;
		}
		NIrisScanner irisScanner = null;
		if (device instanceof NIrisScanner) {
			irisScanner = (NIrisScanner) device;
		}
		NSignatureScanner signatureScanner = null;
		if (device instanceof NSignatureScanner) {
			signatureScanner = (NSignatureScanner) device;
		}
		boolean isCaptureDevice = camera != null || microphone != null || fScanner != null || irisScanner != null || signatureScanner != null;

		menuItemShowPlugin.setEnabled(device != null);
		menuItemDisconnect.setEnabled(device != null && device.isDisconnectable());
		if (device != null && device.isAvailable()) {
			devicesPropertyGrid.setVisible(true);
			devicesPropertyGrid.setSource(device);
		} else {
			devicesPropertyGrid.setVisible(false);
		}

		boolean isFScannerNotNull = fScanner != null;
		chkLL.setVisible(isFScannerNotNull);
		chkLR.setVisible(isFScannerNotNull);
		chkLM.setVisible(isFScannerNotNull);
		chkLI.setVisible(isFScannerNotNull);
		chkLT.setVisible(isFScannerNotNull);
		chkRL.setVisible(isFScannerNotNull);
		chkRR.setVisible(isFScannerNotNull);
		chkRM.setVisible(isFScannerNotNull);
		chkRI.setVisible(isFScannerNotNull);
		chkRT.setVisible(isFScannerNotNull);

		boolean isCaptureDeviceOrBiometricDeviceNotNull = isCaptureDevice && biometricDevice != null;
		txtMiliSec.setVisible(isCaptureDeviceOrBiometricDeviceNotNull);
		chkUseTimeout.setVisible(isCaptureDeviceOrBiometricDeviceNotNull);
		chkAutomatic.setVisible(fScanner != null || irisScanner != null);
		lblMiliSec.setVisible(isCaptureDeviceOrBiometricDeviceNotNull);

		chkGatherImages.setVisible(isCaptureDevice);
		buttonDeviceCapture.setVisible(isCaptureDevice);
		cmbFormats.setVisible(false);
		buttonCustomizeFormat.setVisible(false);
		buttonStartSequence.setVisible(biometricDevice != null);
		buttonEndSequence.setVisible(biometricDevice != null);

		if (fScanner != null) {
			cmbBiometricDeviceImpressionType.removeAllItems();
			cmbBiometricDevicePosition.removeAllItems();
			biometricDevicePositionList.clear();

			try {
				if (fScanner.isAvailable()) {
					for (NFImpressionType impressionType : fScanner.getSupportedImpressionTypes()) {
						cmbBiometricDeviceImpressionType.addItem(impressionType);
					}
					if (cmbBiometricDeviceImpressionType.getItemCount() != 0) {
						cmbBiometricDeviceImpressionType.setSelectedIndex(0);
					}
					for (NFPosition position : fScanner.getSupportedPositions()) {
						biometricDevicePositionList.add(position);
					}
					reformDevicePositionComboBox();
				}
			} finally {
				SwingUtilities.invokeLater(new Runnable() {
					public void run() {
						cmbBiometricDeviceImpressionType.updateUI();
						cmbBiometricDevicePosition.updateUI();
					}
				});
			}
		} else if (irisScanner != null) {
			cmbBiometricDevicePosition.removeAllItems();
			try {
				if (irisScanner.isAvailable()) {
					for (NEPosition position : irisScanner.getSupportedPositions()) {
						cmbBiometricDevicePosition.addItem(position);
					}
					if (cmbBiometricDevicePosition.getItemCount() != 0) {
						cmbBiometricDevicePosition.setSelectedIndex(0);
					}
				}
			} finally {
				SwingUtilities.invokeLater(new Runnable() {
					public void run() {
						cmbBiometricDevicePosition.updateUI();
					}
				});
			}
		}
		cmbBiometricDeviceImpressionType.setVisible(fScanner != null);
		cmbBiometricDevicePosition.setVisible(fScanner != null || irisScanner != null);
		if (captureDevice != null) {
			try {
				cmbFormats.removeAllItems();
				if (captureDevice.isAvailable()) {
					for (NMediaFormat format : captureDevice.getFormats()) {
						cmbFormats.addItem(format);
					}
					NMediaFormat currentFormat = captureDevice.getCurrentFormat();
					if (currentFormat != null) {
						int formatIndex = getIndexOfJComboBoxItem(cmbFormats, currentFormat);
						if (formatIndex == -1) {
							cmbFormats.addItem(currentFormat);
							cmbFormats.setSelectedIndex(cmbFormats.getItemCount() - 1);
						} else {
							cmbFormats.setSelectedIndex(formatIndex);
						}
					}
				}
			} finally {
				SwingUtilities.invokeLater(new Runnable() {
					public void run() {
						cmbFormats.updateUI();
					}
				});
			}
			cmbFormats.setVisible(true);
			buttonCustomizeFormat.setVisible(true);
		}
	}

	private void closeDeviceManager() {
		setDeviceManager(null);
	}

	private void newDeviceManager() {
		DeviceManagerDialog dialog = new DeviceManagerDialog(this);
		// TODO Implement settings framework
		dialog.setDeviceType(NDeviceType.ANY);
		dialog.setAutoPlug(true);
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		dialog.setLocation(screenSize.width / 2 - dialog.getPreferredSize().width / 2, screenSize.height / 2 - dialog.getPreferredSize().height / 2);
		NDeviceManager deviceManager = dialog.showDialog();
		if (deviceManager != null) {
			deviceManager.initialize();
			setDeviceManager(deviceManager);
		}
	}

	private void customizeFormat(NMediaFormat selectedFormat) {
		JDialog customizedDialog = new JDialog(this, true);
		customizedDialog.setPreferredSize(new Dimension(300, 300));
		customizedDialog.setTitle("Customize Format");
		CustomizeFormatDialog customPanel = new CustomizeFormatDialog(this, customizedDialog);
		customizedDialog.getContentPane().add(customPanel);
		customizedDialog.pack();
		customPanel.customizeFormat(selectedFormat);

		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		customizedDialog.setLocation(screenSize.width / 2 - customizedDialog.getPreferredSize().width / 2, screenSize.height / 2 - customizedDialog.getPreferredSize().height / 2);
		customizedDialog.setVisible(true);
	}

	private void connectToDevice() {
		ConnectToDeviceDialog dialog = new ConnectToDeviceDialog(this);
		if (dialog.showDialog()) {
			deviceManager.connectToDevice(dialog.getSelectedPlugin(), dialog.getParameters());
		}
	}

	private void disconnectFromDevice() {
		NDevice device = getSelectedDevice();
		if (device != null) {
			try {
				deviceManager.disconnectFromDevice(device);
			} catch (Exception e) {
				SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, e.toString(), "Disconnect from Device Error", JOptionPane.ERROR_MESSAGE); });
			}
		}
	}

	private void reformDevicePositionComboBox()
	{
		NFImpressionType selectedImpression = (NFImpressionType)cmbBiometricDeviceImpressionType.getSelectedItem();		
		cmbBiometricDevicePosition.removeAllItems();
		if (selectedImpression == null) {
			selectedImpression = NFImpressionType.LIVE_SCAN_PLAIN;
		}
		for (NFPosition position : biometricDevicePositionList) {
			if (position.isCompatibleWith(selectedImpression)) {
				cmbBiometricDevicePosition.addItem(position);
			}
		}
		if (cmbBiometricDevicePosition.getItemCount() != 0) {
			cmbBiometricDevicePosition.setSelectedIndex(0);
		}
	}

	// ==============================================
	// Public methods
	// ==============================================

	public void setDeviceManager(NDeviceManager value) {
		if (value == deviceManager) return;
		if (deviceManager != null) {
			deviceManager.getDevices().removeCollectionChangeListener(this);
			deviceManager.dispose();
			deviceManager = null;
		}
		deviceManager = value;
		onDeviceManagerChanged();
	}

	public void selectNewCustomFormat(NMediaFormat customFormat) {
		if (customFormat != null) {
			int index = getIndexOfJComboBoxItem(cmbFormats, customFormat);
			if (index == -1) {
				cmbFormats.addItem(customFormat);
			}
			cmbFormats.setSelectedItem(customFormat);
		}
	}

	// ==============================================
	// Event handling NChangeListener
	// ==============================================

	public void changed(EventObject arg0) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				devicesTree.updateUI();
			}
		});
	}

	public void changing(EventObject arg0) {
	}

	// ==============================================
	// Event handling NCollectionChangeListener
	// ==============================================

	public void collectionChanged(final NCollectionChangeEvent event) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				switch (event.getAction()) {
				case ADD:
					addDevice((NDevice) event.getNewItems().get(0));
					if (devicesTree.getSelectionPath() == null) {
						devicesTree.setSelectionRow(0);
					}
					devicesTree.updateUI();
					break;
				case REMOVE:
					removeDevice((NDevice) event.getOldItems().get(0));
					break;
				case RESET:
					log("Refreshing device list...");
					updateDeviceList();
					break;

				default:
					break;
				}
			}
		});
	}

	// ==============================================
	// Event handling ActionListener
	// ==============================================

	@Override
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		if (source == menuItemAbout) {
			AboutBox.show();
		} else if (source == menuItemShowPlugin) {
			PluginManagerBox.show(this, NDeviceManager.getPluginManager(), getSelectedDevice().getPlugin());
		} else if (source == buttonDeviceCapture) {
			NDevice device = getSelectedDevice();
			NCaptureDevice captureDevice = null;
			if (device instanceof NCaptureDevice) {
				captureDevice = (NCaptureDevice) device;
			}
			NCamera camera = null;
			if (device instanceof NCamera) {
				camera = (NCamera) device;
			}
			NMicrophone microphone = null;
			if (device instanceof NMicrophone) {
				microphone = (NMicrophone) device;
			}
			NBiometricDevice biometricDevice = null;
			if (device instanceof NBiometricDevice) {
				biometricDevice = (NBiometricDevice) device;
			}
			final CaptureFrame form;
			if (captureDevice != null) {
				if (cmbFormats.getSelectedItem() != null) {
					captureDevice.setCurrentFormat((NMediaFormat) cmbFormats.getSelectedItem());
				}
			}
			if (camera != null) {
				CameraFrame cameraForm = new CameraFrame(this);
				form = cameraForm;
			} else if (microphone != null) {
				MicrophoneFrame microphoneForm = new MicrophoneFrame(this);
				form = microphoneForm;
			} else if (biometricDevice != null) {
				NFScanner fScanner = null;
				if (biometricDevice instanceof NFScanner) {
					fScanner = (NFScanner) biometricDevice;
				}
				NIrisScanner irisScanner = null;
				if (biometricDevice instanceof NIrisScanner) {
					irisScanner = (NIrisScanner) biometricDevice;
				}
				NSignatureScanner signatureScanner = null;
				if (biometricDevice instanceof NSignatureScanner) {
					signatureScanner = (NSignatureScanner) biometricDevice;
				}
				BiometricDeviceFrame biometricDeviceForm;
				if (fScanner != null) {
					FScannerFrame fScannerForm = new FScannerFrame(this);
					fScannerForm.setImpressionType((NFImpressionType) cmbBiometricDeviceImpressionType.getSelectedItem());
					fScannerForm.setPosition((NFPosition) cmbBiometricDevicePosition.getSelectedItem());
					List<NFPosition> missingPositions = new ArrayList<NFPosition>();
					if (chkLL.isSelected()) {
						missingPositions.add(NFPosition.LEFT_LITTLE_FINGER);
					}
					if (chkLR.isSelected()) {
						missingPositions.add(NFPosition.LEFT_RING_FINGER);
					}
					if (chkLM.isSelected()) {
						missingPositions.add(NFPosition.LEFT_MIDDLE_FINGER);
					}
					if (chkLI.isSelected()) {
						missingPositions.add(NFPosition.LEFT_INDEX_FINGER);
					}
					if (chkLT.isSelected()) {
						missingPositions.add(NFPosition.LEFT_THUMB);
					}
					if (chkRT.isSelected()) {
						missingPositions.add(NFPosition.RIGHT_THUMB);
					}
					if (chkRI.isSelected()) {
						missingPositions.add(NFPosition.RIGHT_INDEX_FINGER);
					}
					if (chkRM.isSelected()) {
						missingPositions.add(NFPosition.RIGHT_MIDDLE_FINGER);
					}
					if (chkRR.isSelected()) {
						missingPositions.add(NFPosition.RIGHT_RING_FINGER);
					}
					if (chkRL.isSelected()) {
						missingPositions.add(NFPosition.RIGHT_LITTLE_FINGER);
					}
					fScannerForm.setMissingPositions(missingPositions.toArray(new NFPosition[missingPositions.size()]));
					biometricDeviceForm = fScannerForm;
				} else if (irisScanner != null) {
					IrisScannerFrame irisScannerForm = new IrisScannerFrame(this);
					// TODO iris scanner frame methods
					irisScannerForm.setPosition((NEPosition) cmbBiometricDevicePosition.getSelectedItem());
					// irisScannerForm.Position =
					// (NEPosition)biometricDevicePositionComboBox.SelectedItem;
					biometricDeviceForm = irisScannerForm;
				} else if (signatureScanner != null) {
					SignatureScannerFrame signatureScannerForm = new SignatureScannerFrame(this);
					biometricDeviceForm = signatureScannerForm;
				} else {
					throw new UnsupportedOperationException("Unknown device: " + device);
				}
				biometricDeviceForm.setAutomatic(chkAutomatic.isSelected());
				if (chkUseTimeout.isSelected()) {
					biometricDeviceForm.setTimeout(Integer.parseInt(txtMiliSec.getText()));
				} else {
					biometricDeviceForm.setTimeout(-1);
				}
				form = biometricDeviceForm;
			} else {
				throw new UnsupportedOperationException("Unknown device: " + device);
			}
			form.setGatherImages(chkGatherImages.isSelected());
			form.setDevice(device);
			captureFrames.add(form);
			form.addWindowListener(new WindowAdapter() {

				@Override
				public void windowClosed(WindowEvent e) {
					captureFrames.remove(form);
				}

			});
			Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
			form.setLocation(screenSize.width / 2 - form.getPreferredSize().width / 2, screenSize.height / 2 - form.getPreferredSize().height / 2);
			form.setVisible(true);
		} else if (source == menuItemExit) {
			this.dispose();
		} else if (source == menuItemClose) {
			closeDeviceManager();
		} else if (source == menuItemNew) {
			newDeviceManager();
		} else if (source == chkUseTimeout) {
			txtMiliSec.setEnabled(chkUseTimeout.isSelected());
		} else if (source == buttonCustomizeFormat) {
			NMediaFormat selectedFormat = (NMediaFormat) cmbFormats.getSelectedItem();
			if (selectedFormat == null) {
				NDevice device = getSelectedDevice();
				if ((device.getDeviceType().equals(NDeviceType.CAMERA))) {
					selectedFormat = new NVideoFormat();
				} else if ((device.getDeviceType().equals(NDeviceType.MICROPHONE))) {
					selectedFormat = new NAudioFormat();
				} else {
					throw new NoSuchElementException();
				}
			}
			customizeFormat(selectedFormat);
		} else if (source == buttonStartSequence) {
			NBiometricDevice biometricDevice = (NBiometricDevice) getSelectedDevice();
			if (biometricDevice != null) {
				try {
					biometricDevice.startSequence();
				} catch (Exception ex) {
					SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, ex.toString(), "error", JOptionPane.ERROR_MESSAGE); });
				}
			}
		} else if (source == buttonEndSequence) {
			NBiometricDevice biometricDevice = (NBiometricDevice) getSelectedDevice();
			if (biometricDevice != null) {
				try {
					biometricDevice.endSequence();
				} catch (Exception ex) {
					SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, ex.toString(), "error", JOptionPane.ERROR_MESSAGE); });
				}
			}
		} else if (source == cmbBiometricDeviceImpressionType) {
			reformDevicePositionComboBox();
		}
	}

	// ==============================================
	// Event handling TreeSelectionListener
	// ==============================================

	public void valueChanged(TreeSelectionEvent e) {
		try {
			onSelectedDeviceChanged();
		} catch (Exception ex) {
			SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, ex.toString()); });
		}
	}

}
