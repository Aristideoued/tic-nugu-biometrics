package com.neurotec.samples.swing;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.*;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.DefaultListCellRenderer;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.SwingUtilities;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NBiometricTask;
import com.neurotec.biometrics.NFAttributes;
import com.neurotec.biometrics.NFCore;
import com.neurotec.biometrics.NFDelta;
import com.neurotec.biometrics.NFMinutia;
import com.neurotec.biometrics.NFMinutiaNeighbor;
import com.neurotec.biometrics.NFPosition;
import com.neurotec.biometrics.NFRecord;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.swing.NFingerView;
import com.neurotec.biometrics.swing.SegmentManipulationEvent;
import com.neurotec.biometrics.swing.SegmentManipulationListener;
import com.neurotec.biometrics.swing.SegmentManipulationTool;
import com.neurotec.images.NImage;
import com.neurotec.plugins.NDataFileManager;
import com.neurotec.samples.Utilities;
import com.neurotec.samples.enrollment.EnrollmentDataModel;
import com.neurotec.samples.enrollment.EnrollmentSettings;
import com.neurotec.samples.enrollment.fingers.HandSegmentSelector;
import com.neurotec.samples.enrollment.fingers.Scenario;
import com.neurotec.samples.util.Utils;
import com.neurotec.util.concurrent.CompletionHandler;


public final class FingerCaptureFrame extends JDialog implements ActionListener, SegmentManipulationListener {

	// ==============================================
	// Private classes
	// ==============================================

	private enum IndexChangingOrder {
		MOVE_TO_NEXT_INDEX,
		MOVE_TO_PRVIOUS_INDEX,
		MOVE_TO_SELECTED_INDEX;
	}

	private class FingerPropertyChangeListener implements PropertyChangeListener {

		@Override
		public void propertyChange(PropertyChangeEvent evt) {
			if (!current.isDisposed()) {
				NBiometricStatus status = current.getStatus();
				if (evt.getPropertyName().equalsIgnoreCase("Status")) {
					clearStatus();
					lblStatus.setText(String.format("<html> Status: %s</html>", enumToString(status)));
					lblStatus.setForeground(getStatusColor(status));

					boolean isRolled = current.getImpressionType().isRolled();
					setStatus(isRolled ? "Please roll %s finger on scanner" : "Veuillez placer les %s sur le scanner", positionToString(current.getPosition()).toLowerCase());
				} else if (evt.getPropertyName().equalsIgnoreCase("Image")) {
					NImage image = current.getImage(false);
					if (image != null) {
						updateViewSize(image.getWidth(), image.getHeight());
					}
				}
			}

		}

	}

	private class TemplateCreationHandler implements CompletionHandler<NBiometricTask, Object> {
      Mongo mg=new Mongo();
		@Override
		public void completed(final NBiometricTask result, final Object attachment) {
			SwingUtilities.invokeLater(new Runnable() {

				@Override
				public void run() {
					NBiometricStatus status = current.getStatus();
					if (status == NBiometricStatus.OK) {
						lstScanQueue.updateUI();
						setStatus(new Color(0, 124, 0), Color.WHITE, "Création du modèle terminée avec succès");

						//System.out.println("<=======================Taille de la List des captures=========> "+subject.getTemplate().getFingers().getRecords().size());
						/*subject.getTemplate().getFingers().getRecords().forEach(element -> {
							System.out.println("<=======================Nombre de munities par doigt="+element.getMinutiae().size());

							for (int i=0;i<element.getMinutiae().size();i++){
								mg.insertMunitieToMongoDB(element.getMinutiae().get(i).x,element.getMinutiae().get(i).y,element.getPosition().toString());

							}

						});*/


					/*	if(subject.getTemplate().getFingers().getRecords().size()==4 ){
							for (int i=0;i<4;i++){
								mg.insertMunitieToMongoDB(subject.getTemplate().getFingers().getRecords().get(i).getMinutiae().get(i).x,subject.getTemplate().getFingers().getRecords().get(i).getMinutiae().get(i).y,subject.getTemplate().getFingers().getRecords().get(i).getPosition().toString());

							}

							for (int i=3;i<subject.getFingers().size();i++){
								System.out.println("<=======================Nom de doigt="+subject.getFingers().get(i).getPosition().toString());

								if(subject.getFingers().get(i).getBinarizedImage(true)!=null){
									try {
										convertBase64ToPNG(convertToBase64(subject.getFingers().get(i).getImage().toImage(),"png"),subject.getFingers().get(i).getPosition().toString()+".png");
									} catch (IOException e) {
										throw new RuntimeException(e);
									}
									mg.insertImageToMongoDB(mg.convertToByteArray(mg.convert(convertToBase64(subject.getFingers().get(i).getImage().toImage(),"png"))),subject.getFingers().get(i).getPosition().toString());

								}
						}
						}
						else if(subject.getTemplate().getFingers().getRecords().size()==8){
							for (int i=4;i<8;i++){
								mg.insertMunitieToMongoDB(subject.getTemplate().getFingers().getRecords().get(i).getMinutiae().get(i).x,subject.getTemplate().getFingers().getRecords().get(i).getMinutiae().get(i).y,subject.getTemplate().getFingers().getRecords().get(i).getPosition().toString());

							}
							for (int i1=7;i1<subject.getFingers().size();i1++){
								System.out.println("<=======================Nom de doigt="+subject.getFingers().get(i1).getPosition().toString());

								if(subject.getFingers().get(i1).getBinarizedImage(true)!=null){
									try {
										convertBase64ToPNG(convertToBase64(subject.getFingers().get(i1).getImage().toImage(),"png"),subject.getFingers().get(i1).getPosition().toString()+".png");
									} catch (IOException e) {
										throw new RuntimeException(e);
									}
									mg.insertImageToMongoDB(mg.convertToByteArray(mg.convert(convertToBase64(subject.getFingers().get(i1).getImage().toImage(),"png"))),subject.getFingers().get(i1).getPosition().toString());

								}
						}
						}
						else if(subject.getTemplate().getFingers().getRecords().size()==10){
							for (int i=8;i<10;i++){
								mg.insertMunitieToMongoDB(subject.getTemplate().getFingers().getRecords().get(i).getMinutiae().get(i).x,subject.getTemplate().getFingers().getRecords().get(i).getMinutiae().get(i).y,subject.getTemplate().getFingers().getRecords().get(i).getPosition().toString());

							}
							for (int i2=11;i2<subject.getFingers().size();i2++){
								if(subject.getFingers().get(i2).getBinarizedImage(true)!=null){
									try {
										convertBase64ToPNG(convertToBase64(subject.getFingers().get(i2).getImage().toImage(),"png"),subject.getFingers().get(i2).getPosition().toString()+".png");
									} catch (IOException e) {
										throw new RuntimeException(e);
									}
									mg.insertImageToMongoDB(mg.convertToByteArray(mg.convert(convertToBase64(subject.getFingers().get(i2).getImage().toImage(),"png"))),subject.getFingers().get(i2).getPosition().toString());

								}}
						}*/

					/*	subject.getFingers().forEach(element -> {

							if(element.getBinarizedImage(true)!=null){
								try {
								//	System.out.println("<=======================Doit concerné="+element.getPosition());

									convertBase64ToPNG(convertToBase64(element.getImage().toImage(),"png"),element.getPosition().toString()+".png");
									mg.insertImageToMongoDB(mg.convertToByteArray(mg.convert(convertToBase64(element.getImage().toImage(),"png"))),element.getPosition().toString());
								} catch (Exception e) {
									throw new RuntimeException(e);
								}

							}
						});*/


					} else {
						setError("Create template failed, status: %s", status);
					}
					isProcessingCurrentFinger = false;
					enableControls();

					isClientBusy = false;
					if (status == NBiometricStatus.OK) {
						moveToNext();
					}

					if (status == NBiometricStatus.CANCELED) {
						moveToSelectedIndex();
					}
				}
			});

		}

		public int getNbrecord(){
			return  subject.getTemplate().getFingers().getRecords().size();
		}

		public  void convertBase64ToPNG(String base64String, String fileName) throws IOException {
			// Retirer le préfixe si présent (par exemple, "data:image/png;base64,")
			if (base64String.startsWith("data:image/png;base64,")) {
				base64String = base64String.substring("data:image/png;base64,".length());
			}

			// Décoder la chaîne Base64
			byte[] imageBytes = Base64.getDecoder().decode(base64String);

			// Écrire les octets dans un fichier
			try (FileOutputStream fos = new FileOutputStream(fileName)) {
				fos.write(imageBytes);
			}
		}

		public  String convertToBase64(Image img, String formatName) {
			// Convert Image to BufferedImage
			BufferedImage bufferedImage = new BufferedImage(img.getWidth(null), img.getHeight(null), BufferedImage.TYPE_INT_ARGB);
			bufferedImage.getGraphics().drawImage(img, 0, 0, null);

			// Convert BufferedImage to Base64
			try (ByteArrayOutputStream baos = new ByteArrayOutputStream()) {
				ImageIO.write(bufferedImage, formatName, baos);
				byte[] imageBytes = baos.toByteArray();
				return Base64.getEncoder().encodeToString(imageBytes);
			} catch (IOException e) {
				e.printStackTrace();
				return null;
			}
		}

		@Override
		public void failed(final Throwable th, final Object attachment) {
			SwingUtilities.invokeLater(new Runnable() {

				@Override
				public void run() {
					isProcessingCurrentFinger = false;
					enableControls();
					th.printStackTrace();
					Utilities.showError(getOwner(), th.getMessage());
					isClientBusy = false;
				}
			});
		}

	}

	private class CapturingHandler implements CompletionHandler<NBiometricTask, Object> {

		@Override
		public void completed(final NBiometricTask result, final Object attachment) {
			SwingUtilities.invokeLater(new Runnable() {

				@Override
				public void run() {
					NBiometricStatus status = current.getStatus();

					if (status == NBiometricStatus.OK) {
						setStatus(new Color(0, 124, 0), Color.WHITE, "Capture des %s effectuée avec succès.  Ajustez les segments si nécessaire et appuyez sur le bouton Valider", positionToString(current.getPosition()).toLowerCase());
					} else {
						setError("Operation echouée, status: %s", status);
					}
					isCapturingCurrentFinger = false;
					enableControls();

					isClientBusy = false;
					if (status == NBiometricStatus.CANCELED) {
						moveToSelectedIndex();
					}
				}
			});

		}

		@Override
		public void failed(final Throwable th, final Object attachment) {
			SwingUtilities.invokeLater(new Runnable() {

				@Override
				public void run() {
					isCapturingCurrentFinger = false;
					enableControls();
					th.printStackTrace();
					Utilities.showError(getOwner(), th.getMessage());
					isClientBusy = false;
				}
			});

		}

	}

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private static methods
	// ==============================================

	private static String positionToString(NFPosition value) {
		if (value == NFPosition.PLAIN_LEFT_FOUR_FINGERS || value == NFPosition.PLAIN_RIGHT_FOUR_FINGERS || value == NFPosition.PLAIN_THUMBS) {
			String txt="";
			if(enumToString(value).contains("THUMB")){
				txt="POUCES";
			} else if (enumToString(value).contains("RIGHT")) {
				txt="QUATRE DOIGTS DE LA DROITE";

			}
			else if (enumToString(value).contains("LEFT")) {
				txt="QUATRE DOIGTS DE LA GAUCHE";

			}else{
				txt=enumToString(value).replace("PLAIN ", "");
			}
			return txt;
		}
		return enumToString(value);
	}

	private static String enumToString(Enum<?> value) {

		String txt="";
		if(value.toString().contains("OBJECT")){
			txt="MAUVAIS PLACEMENT, VEUILLEZ BIEN REPLACER LES DOIGTS CONCERNES";

		}
		else{
			txt=value.name().replaceAll("_", " ");
		}
		return txt;
	}

	// ==============================================
	// Private fields
	// ==============================================

	private HandSegmentSelector fingerSelector;

	private JButton btnPrevious;
	private JButton btnNext;
	private JButton btnRescan;
	private JButton btnAccept;
	private JLabel lblInfo;
	private NFingerView fingerView;

	private JLabel lblStatus;

	private JList lstScanQueue;
	private Vector<String> vctScanQueue;

	private GridBagUtils gridBagUtils;

	private final EnrollmentDataModel dataModel;

	private NBiometricClient biometricClient;
	private NSubject subject;
	private List<NFinger> captureList;
	private NFinger current;

	private volatile boolean isProcessingCurrentFinger;
	private volatile boolean isCapturingCurrentFinger;

	private boolean isClientBusy;
	private IndexChangingOrder indexChangingOrder;
	private final FingerPropertyChangeListener propertyChangedListner = new FingerPropertyChangeListener();
	// ==============================================
	// Public constructor
	// ==============================================

	public FingerCaptureFrame(Frame owner) {
		super(owner, "Capture en cours...");
		dataModel = EnrollmentDataModel.getInstance();

		setPreferredSize(new Dimension(920, 535));
		setResizable(true);
		initializeComponents();
		setLocationRelativeTo(owner);
		setBiometricClient(dataModel.getBiometricClient());
		setSubject(dataModel.getSubject());


		addWindowListener(new WindowAdapter() {

			@Override
			public void windowOpened(WindowEvent e) {
				captureFormLoad();
			}

			@Override
			public void windowClosing(WindowEvent e) {
				captureFormFormClosing();
				fingerSelector.onClose();

			}
		});

	}

	// ==============================================
	// Private methods
	// ==============================================

	private void moveToSelectedIndex() {
		if (indexChangingOrder != null) {
			switch (indexChangingOrder) {
			case MOVE_TO_NEXT_INDEX:
				moveToNext();
				break;
			case MOVE_TO_PRVIOUS_INDEX:
				moveToPrevious();
				break;
			case MOVE_TO_SELECTED_INDEX:
				changeSelectedTask();
				break;
			default:
				break;
			}
		}
	}

	private void initializeComponents() {
		getContentPane().setLayout(new BorderLayout());

		JSplitPane mainSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		mainSplitPane.setLeftComponent(createLeftPanel());
		mainSplitPane.setRightComponent(createRightPanel());
		mainSplitPane.setDividerLocation(200);

		getContentPane().add(mainSplitPane, BorderLayout.CENTER);
		pack();
	}

	private JPanel createLeftPanel() {
		JPanel leftPanel = new JPanel();
		GridBagLayout leftPanelLayout = new GridBagLayout();
		leftPanelLayout.columnWidths = new int[] {50, 50, 50, 50, 5};
		leftPanelLayout.rowHeights = new int[] {105, 40, 335};
		leftPanel.setLayout(leftPanelLayout);

		fingerSelector = new HandSegmentSelector();
		fingerSelector.setScenario(Scenario.ALL_PLAIN_FINGERS);
		fingerSelector.clear();
		fingerSelector.setEnabled(false);

		btnPrevious = new JButton(Utils.createIcon("images/GoToPrevious.png"));
		btnPrevious.addActionListener(this);

		btnNext = new JButton(Utils.createIcon("images/GoToNext.png"));
		btnNext.addActionListener(this);

		btnRescan = new JButton(Utils.createIcon("images/Repeat.png"));
		btnRescan.addActionListener(this);

		btnAccept = new JButton(Utils.createIcon("images/Accept.png"));
		btnAccept.addActionListener(this);

		gridBagUtils = new GridBagUtils(GridBagConstraints.BOTH);
		gridBagUtils.setInsets(new Insets(2, 1, 2, 1));

		gridBagUtils.addToGridBagLayout(0, 0, 4, 1, leftPanel, fingerSelector);
		gridBagUtils.addToGridBagLayout(0, 2, 4, 1, 0, 1, leftPanel, createScanQueuePanel());
		gridBagUtils.addToGridBagLayout(0, 1, 1, 1, 0, 0, leftPanel, btnPrevious);
		gridBagUtils.addToGridBagLayout(1, 1, leftPanel, btnNext);
		gridBagUtils.addToGridBagLayout(2, 1, leftPanel, btnRescan);
		gridBagUtils.addToGridBagLayout(3, 1, leftPanel, btnAccept);
		gridBagUtils.clearGridBagConstraints();
		return leftPanel;
	}

	private JPanel createScanQueuePanel() {
		JPanel scanQueuePanel = new JPanel(new BorderLayout());
		scanQueuePanel.setBorder(BorderFactory.createTitledBorder("File d'attente"));

		vctScanQueue = new Vector<String>();
		lstScanQueue = new JList(vctScanQueue);
		lstScanQueue.addListSelectionListener(new ListSelectionListener() {

			@Override
			public void valueChanged(ListSelectionEvent e) {
				if (current != null) {
					changeSelectedTask();
				}

			}
		});
		lstScanQueue.setCellRenderer(new DefaultListCellRenderer() {

			private static final long serialVersionUID = 1L;

			@Override
			public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
				Component c = super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
				NFinger item = captureList.get(index);
				if (isCreateTemplateDone(item)) {
					c.setForeground(Color.GREEN);
				} else {
					c.setForeground(Color.BLACK);
				}
				return c;
			}

		});
		JScrollPane scrollScanQueue = new JScrollPane(lstScanQueue, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scanQueuePanel.add(scrollScanQueue, BorderLayout.CENTER);
		return scanQueuePanel;
	}

	private JPanel createRightPanel() {
		JPanel rightPanel = new JPanel();
		GridBagLayout rightPanelLayout = new GridBagLayout();
		rightPanelLayout.rowHeights = new int[] {25, 430, 20, 20};
		rightPanel.setLayout(rightPanelLayout);

		lblInfo = new JLabel("Info");
		lblInfo.setOpaque(true);

		fingerView = new NFingerView();
		fingerView.setAutofit(true);
		JScrollPane fingerViewScrollPane = new JScrollPane(fingerView, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		SegmentManipulationTool<NFMinutia, NFCore, NFDelta, NFMinutiaNeighbor> tool = new SegmentManipulationTool<NFMinutia, NFCore, NFDelta, NFMinutiaNeighbor>(fingerView);
		tool.addSegmentManipulationListner(this);
		fingerView.setActiveTool(tool);

		lblStatus = new JLabel("Status");
		lblStatus.setOpaque(true);

		JPanel statusPanel = new JPanel();
		statusPanel.setLayout(new BoxLayout(statusPanel, BoxLayout.X_AXIS));

		gridBagUtils.setInsets(new Insets(1, 1, 1, 1));
		gridBagUtils.addToGridBagLayout(0, 0, 1, 1, 1, 0, rightPanel, lblInfo);
		gridBagUtils.addToGridBagLayout(0, 1, 1, 1, 1, 1, rightPanel, fingerViewScrollPane);
		gridBagUtils.addToGridBagLayout(0, 2, 1, 1, 1, 0, rightPanel, lblStatus);
		gridBagUtils.addToGridBagLayout(0, 3, rightPanel, statusPanel);

		return rightPanel;
	}

	private void setStatus(Color backColor, Color foreColor, String format, Object... args) {
		lblInfo.setBackground(backColor);
		lblInfo.setForeground(foreColor);
		if (format != null) {
			lblInfo.setText(String.format("<html>" + format + "</html>", args));
		}
	}

	private void setStatus(String format, Object... args) {
		setStatus(new Color(205, 205, 180), Color.BLACK, format, args);
	}

	private void setError(String format, Object... args) {
		setStatus(Color.RED, Color.WHITE, format, args);
	}

	private void setStatus(String text) {
		setStatus(Color.LIGHT_GRAY, Color.BLACK, text);
	}

	private Color getStatusColor(NBiometricStatus status) {
		if (status == NBiometricStatus.OK || status == NBiometricStatus.NONE || status == NBiometricStatus.OBJECT_MISSING) {
			return Color.GREEN;
		}
		return Color.RED;
	}

	private void cancelCapturing() {
		if (isCapturingCurrentFinger) {
			biometricClient.cancel();
		}
	}

	private void finishTask() {
		cancelCapturing();
		if (current != null) {
			if (isCaptureDone(current) && !isCreateTemplateDone(current)) {
				current.setImage(null);
			}
		}
	}

	private void startTask(NFinger finger) {
		if (current != null) {
			if (isCaptureDone(current) && !isCreateTemplateDone(current)) {
				if (!Utilities.showQuestion(this, "Records not extracted from this image! Press 'Yes' to continue anyway, press 'No' and then 'Accept' button to extract records")) {
					btnAccept.setToolTipText("Accept image and extract records");
					int index = captureList.indexOf(current);
					lstScanQueue.setSelectedIndex(index);
					return;
				}
			}
		}

		disableNavigation();
		finishTask();
		fingerView.setFinger(null);
		fingerView.setToolMouseCaptured(true);

		current = finger;
		fingerSelector.clearSelection();
		fingerSelector.clearRotation();
		fingerSelector.setRotated(current.getPosition(), current.getImpressionType().isRolled());
		selectFingers(finger.getPosition());

		int index = captureList.indexOf(current);
		lstScanQueue.setSelectedIndex(index);

		fingerView.setFinger(current);
		if (!isCreateTemplateDone(current)) {
			NBiometricTask biometricTask = biometricClient.createTask(EnumSet.of(NBiometricOperation.CAPTURE, NBiometricOperation.SEGMENT, NBiometricOperation.ASSESS_QUALITY), subject);
			biometricTask.setBiometric(current);
			current.addPropertyChangeListener(propertyChangedListner);
			isCapturingCurrentFinger = true;
			biometricClient.performTask(biometricTask, null, new CapturingHandler());
			isClientBusy = true;
		} else {
			setStatus(new Color(0, 178, 0), Color.WHITE, "Enregistrement(s) extrait(s) avec succès");
			onFingerViewResize();
		}
		enableControls();
		lstScanQueue.updateUI();
	}

	private void selectFingers(NFPosition position) {
		switch (position) {
		case PLAIN_LEFT_FOUR_FINGERS:
			fingerSelector.setSelected(NFPosition.LEFT_LITTLE_FINGER, !fingerSelector.getMissingPositions().contains(NFPosition.LEFT_LITTLE_FINGER));
			fingerSelector.setSelected(NFPosition.LEFT_RING_FINGER, !fingerSelector.getMissingPositions().contains(NFPosition.LEFT_RING_FINGER));
			fingerSelector.setSelected(NFPosition.LEFT_MIDDLE_FINGER, !fingerSelector.getMissingPositions().contains(NFPosition.LEFT_MIDDLE_FINGER));
			fingerSelector.setSelected(NFPosition.LEFT_INDEX_FINGER, !fingerSelector.getMissingPositions().contains(NFPosition.LEFT_INDEX_FINGER));
			break;
		case PLAIN_RIGHT_FOUR_FINGERS:
			fingerSelector.setSelected(NFPosition.RIGHT_LITTLE_FINGER, !fingerSelector.getMissingPositions().contains(NFPosition.RIGHT_LITTLE_FINGER));
			fingerSelector.setSelected(NFPosition.RIGHT_RING_FINGER, !fingerSelector.getMissingPositions().contains(NFPosition.RIGHT_RING_FINGER));
			fingerSelector.setSelected(NFPosition.RIGHT_MIDDLE_FINGER, !fingerSelector.getMissingPositions().contains(NFPosition.RIGHT_MIDDLE_FINGER));
			fingerSelector.setSelected(NFPosition.RIGHT_INDEX_FINGER, !fingerSelector.getMissingPositions().contains(NFPosition.RIGHT_INDEX_FINGER));
			break;
		case PLAIN_THUMBS:
			fingerSelector.setSelected(NFPosition.LEFT_THUMB, !fingerSelector.getMissingPositions().contains(NFPosition.LEFT_THUMB));
			fingerSelector.setSelected(NFPosition.RIGHT_THUMB, !fingerSelector.getMissingPositions().contains(NFPosition.RIGHT_THUMB));
			break;
		default:
			fingerSelector.setSelected(position, true);
			break;

		}
	}

	private void onFingerViewResize() {
		if (!isCapturingCurrentFinger && current != null) {
			NImage image = current.getImage(false);
			if (image != null) {
				updateViewSize(image.getWidth(), image.getHeight());
			}
		}
	}

	private void updateViewSize(int width, int height) {
		Dimension d = fingerView.getSize();
		double scale = Math.max(0.01, Math.min(d.getWidth() / width, d.getHeight() / height));
		fingerView.setScale(scale);
	}

	private boolean isCaptureDone(NFinger finger) {
		return !isCapturingCurrentFinger && finger.getImage() != null;
	}

	private boolean isCreateTemplateDone(NFinger finger) {
		if (finger == null || subject == null) {
			return false;
		}
		if (subject.getTemplate() != null && subject.getTemplate().getFingers() != null) {
			for (NFRecord fr : subject.getTemplate().getFingers().getRecords()) {
				if (fr.getPosition() == finger.getPosition() && fr.getImpressionType().isRolled() == finger.getImpressionType().isRolled()) {
					return true;
				}
			}
			int childCount = 0;
			int templateCount = 0;
			for (NFAttributes attribute : finger.getObjects()) {
				if (attribute.getChild() != null && attribute.getChild() instanceof NFinger) {
					// Slap's finger found
					NFinger childFinger = (NFinger) attribute.getChild();
					childCount++;
					for (NFRecord fr : subject.getTemplate().getFingers().getRecords()) {
						// Check for having at least one finger of slap in the template
						if (fr.getPosition() == childFinger.getPosition() && fr.getImpressionType().isRolled() == finger.getImpressionType().isRolled()) {
							templateCount++;
						}
					}
				}
			}
			return (childCount > 0 && childCount == templateCount);
		}
		return false;
	}

	private void clearStatus() {
		lblStatus.setText("");
	}

	private void enableControls() {
		if (captureList != null && captureList.size() > 0) {
			btnPrevious.setEnabled(current != captureList.get(0) && !isProcessingCurrentFinger);
			btnNext.setEnabled(current != captureList.get(captureList.size() - 1) && !isProcessingCurrentFinger);
			btnAccept.setEnabled(!isCapturingCurrentFinger && !isProcessingCurrentFinger && isCaptureDone(current) && !isCreateTemplateDone(current));
			btnRescan.setEnabled(!isCapturingCurrentFinger && !isProcessingCurrentFinger);
		}
		lblStatus.setVisible(isCapturingCurrentFinger);
	}

	private void disableNavigation() {
		btnPrevious.setEnabled(false);
		btnNext.setEnabled(false);
		btnAccept.setEnabled(false);
		btnRescan.setEnabled(false);
	}

	private void captureFormLoad() {
		setFingerSelectorScenario();
		if (biometricClient != null && subject != null) {
			biometricClient.setFingersCalculateNFIQ(true);
			if (subject.getMissingFingers() != null) {
				for (NFPosition missingPosition : subject.getMissingFingers()) {
					fingerSelector.setMissing(missingPosition, true);
				}
			}
			setStatus("");
			clearStatus();

			captureList = new ArrayList<NFinger>();
			for (NFinger finger : subject.getFingers()) {
				if (finger.getParentObject() == null) {
					captureList.add(finger);
				}
			}

			for (NFinger item : captureList) {
				boolean isRolled = item.getImpressionType().isRolled();
				String text = String.format("%s%s", positionToString(item.getPosition()), isRolled ? "(rolled)" : "");
				vctScanQueue.add(text);
			}
			lstScanQueue.updateUI();

			if (!moveToNext()) {
				setError("Echec de demarrage de la capture");
			}
		}
	}

	private void setFingerSelectorScenario() {
		EnrollmentSettings settings = EnrollmentSettings.getInstance();
		if (settings.isScanPlain() || settings.isScanSlaps()) {
			fingerSelector.setScenario(Scenario.ALL_PLAIN_FINGERS);
		} else if (settings.isScanRolled()) {
			fingerSelector.setScenario(Scenario.ALL_ROLLED_FINGERS);
		}
		fingerSelector.setEnabled(false);
	}

	private void captureFormFormClosing() {
		cancelCapturing();
		if (current != null && !isCreateTemplateDone(current)) {
			current.setImage(null);

		}
	}

	private void moveToPrevious() {
		if (isClientBusy) {
			indexChangingOrder = IndexChangingOrder.MOVE_TO_PRVIOUS_INDEX;
			biometricClient.cancel();
			return;
		}
		int index = captureList.indexOf(current) - 1;
		if (index >= 0) {
			startTask(captureList.get(index));
		}
	}

	private boolean moveToNext() {
		if (isClientBusy) {
			indexChangingOrder = IndexChangingOrder.MOVE_TO_NEXT_INDEX;
			biometricClient.cancel();
			return true;
		}
		if (captureList != null && captureList.size() > 0) {
			int index = 0;
			if (current != null) {
				index = captureList.indexOf(current) + 1;
			}

			if (index < captureList.size()) {
				startTask(captureList.get(index));
				return true;
			}
		}
		return false;
	}

	private void rescan() {
		current.setImage(null);
		lstScanQueue.updateUI();
		startTask(current);
	}

	private void accept() {
		if (current != null) {
			NBiometricTask task = biometricClient.createTask(EnumSet.of(NBiometricOperation.CREATE_TEMPLATE), subject);
			task.setBiometric(current);
			isProcessingCurrentFinger = true;
			biometricClient.performTask(task, null, new TemplateCreationHandler());
			isClientBusy = true;
			setStatus("Extraction des enregistrements. Veuillez patienter ...");
		}
		enableControls();
	}

	private void changeSelectedTask() {
		int[] selected = lstScanQueue.getSelectedIndices();
		if (selected.length > 0) {
			int currentIndex = captureList.indexOf(current);
			int index = selected[0];
			if (index != currentIndex) {
				if (isClientBusy) {
					indexChangingOrder = IndexChangingOrder.MOVE_TO_SELECTED_INDEX;
					biometricClient.cancel();
					return;
				}
				startTask(captureList.get(index));
			}
		}
	}

	// ==============================================
	// Public methods
	// ==============================================

	public NBiometricClient getBiometricClient() {
		return biometricClient;
	}

	public void setBiometricClient(NBiometricClient biometricClient) {
		this.biometricClient = biometricClient;
	}

	public NSubject getSubject() {
		return subject;
	}

	public void setSubject(NSubject subject) {
		this.subject = subject;

	}
	
	public  void showList(){
		captureList.forEach(element -> {
			System.out.println("<======================================List de capture================> "+element.getBinarizedImage());
		});
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		if (source == btnPrevious) {
			moveToPrevious();
		} else if (source == btnNext) {
			moveToNext();
		} else if (source == btnRescan) {
			rescan();
		} else if (source == btnAccept) {
			accept();
		}
	}

	@Override
	public void segmentManipulationEnded(SegmentManipulationEvent e) {
		if (current != null) {
			NBiometricTask biometricTask = biometricClient.createTask(EnumSet.of(NBiometricOperation.SEGMENT, NBiometricOperation.ASSESS_QUALITY), subject);
			biometricTask.setBiometric(current);
			current.addPropertyChangeListener(new FingerPropertyChangeListener());
			biometricClient.performTask(biometricTask, null, new CapturingHandler());
			isClientBusy = true;
			enableControls();
			lstScanQueue.updateUI();
		}
	}

}
