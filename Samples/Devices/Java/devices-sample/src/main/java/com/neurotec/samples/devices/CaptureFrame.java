package com.neurotec.samples.devices;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;
import java.util.EnumSet;
import java.util.Enumeration;
import java.util.LinkedList;
import java.util.UUID;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.neurotec.devices.NDevice;
import com.neurotec.devices.NDeviceType;
import com.neurotec.images.NImage;
import com.neurotec.media.NAudioFormat;
import com.neurotec.media.NMediaFormat;
import com.neurotec.media.NVideoFormat;
import com.neurotec.samples.devices.events.CustomizeFormatListener;

/**
 * This is the superclass for all the capture frames For each
 * device type there need to be a extended class of this.
 */
public abstract class CaptureFrame extends JDialog implements CustomizeFormatListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;
	private static final int PREFERRED_WIDTH = 640;
	private static final int PREFERRED_HEIGHT = 480;

	// ==============================================
	// Private static methods
	// ==============================================

	private static BufferedImage rescaleImage(BufferedImage image, int maxHeight, int maxWidth) {
		int newHeight = 0, newWidth = 0;
		int priorHeight = image.getHeight();
		int priorWidth = image.getWidth();

		// Calculate the correct new height and width
		if ((float) priorHeight / (float) priorWidth > (float) maxHeight / (float) maxWidth) {
			newHeight = maxHeight;
			newWidth = (int) (((float) priorWidth / (float) priorHeight) * (float) newHeight);
		} else {
			newWidth = maxWidth;
			newHeight = (int) (((float) priorHeight / (float) priorWidth) * (float) newWidth);
		}

		// Resize the image
		BufferedImage resizedImg = new BufferedImage(newWidth, newHeight, BufferedImage.TYPE_INT_RGB);
		Graphics2D g2 = resizedImg.createGraphics();
		g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
		g2.drawImage(image, 0, 0, newWidth, newHeight, null);
		g2.dispose();
		return resizedImg;
	}

	private static int getIndexOfJComboBoxItem(JComboBox cmbBox, Object item) {
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

	private boolean autoCaptureStart;
	private NDevice device;
	private boolean gatherImages;
	private boolean forceCapture;
	private boolean isCapturing;
	private BufferedImage image, finalImage;
	private int fps;
	private String userStatus, finalUserStatus;
	private LinkedList<Long> timestamps;
	private String imagesPath;

	private volatile boolean suppressMediaFormatEvents;
	private int imageCount = 0;
	private long lastReportTime = 0;
	private String statusText;
	private BackgroundWorker backgroundWorker;

	// =============================================
	// Private GUI controls
	// =============================================

	private JPanel picturePanel;
	private JLabel pictureLabel;
	private JComboBox cmbFormats;
	private JButton buttonCustomize;
	private JButton buttonForce;
	private JButton buttonClose;
	private JTextArea txtStatus;

	// =============================================
	// Protected fields
	// =============================================

	protected final Object statusLock = new Object();

	// =============================================
	// Protected constructor
	// =============================================

	protected CaptureFrame(JFrame parent) {
		super(parent);
		initGUI();
		onDeviceChanged();
	}

	// =============================================
	// Private methods
	// =============================================

	protected void initGUI() {
		this.setPreferredSize(new Dimension(680, 580));
		this.addComponentListener(new CaptureFrameListener());
		this.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent arg0) {
				super.windowClosing(arg0);
				closeCaptureFrame();
			}

		});
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		picturePanel = new JPanel();
		picturePanel.setPreferredSize(new Dimension(640, 390));
		picturePanel.setLayout(new BoxLayout(picturePanel, BoxLayout.X_AXIS));


		pictureLabel = new JLabel();
		picturePanel.add(Box.createHorizontalGlue());
		picturePanel.add(pictureLabel);
		picturePanel.add(Box.createHorizontalGlue());

		cmbFormats = new JComboBox();
		cmbFormats.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (suppressMediaFormatEvents) {
					return;
				}
				NMediaFormat mediaFormat = cmbFormats.getSelectedIndex() >= 0 ? (NMediaFormat) cmbFormats.getSelectedItem() : null;
				onMediaFormatChanged(mediaFormat);
			}
		});

		buttonCustomize = new JButton("Customize...");
		buttonCustomize.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				NMediaFormat selectedFormat = (NMediaFormat) cmbFormats.getSelectedItem();
				if (selectedFormat == null) {
					NDevice device = getDevice();
					if ((device.getDeviceType().contains(NDeviceType.CAMERA))) {
						selectedFormat = new NVideoFormat();
					} else if ((device.getDeviceType().contains(NDeviceType.MICROPHONE))) {
						selectedFormat = new NAudioFormat();
					} else {
						throw new IllegalArgumentException();
					}
				}
				customizeFormat(selectedFormat);
			}
		});

		buttonForce = new JButton("Force");
		buttonForce.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				forceCapture = true;
			}
		});

		buttonClose = new JButton("Close");
		buttonClose.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				closeCaptureFrame();
				dispose();
			}
		});

		txtStatus = new JTextArea();
		txtStatus.setPreferredSize(new Dimension(550, 100));
		txtStatus.setLineWrap(true);
		txtStatus.setWrapStyleWord(true);
		txtStatus.setEditable(false);

		JPanel middlePanel = new JPanel(new FlowLayout());
		middlePanel.add(cmbFormats);
		middlePanel.add(buttonCustomize);
		middlePanel.add(buttonForce);

		Box closeBox = Box.createVerticalBox();
		closeBox.add(Box.createGlue());
		closeBox.add(buttonClose);

		Box bottomBox = Box.createHorizontalBox();
		bottomBox.add(txtStatus);
		bottomBox.add(closeBox);

		mainPanel.add(picturePanel);
		mainPanel.add(middlePanel);
		mainPanel.add(bottomBox);

		this.getContentPane().add(mainPanel);
		this.pack();
	}

	private void closeCaptureFrame() {
		if (backgroundWorker.getState() != SwingWorker.StateValue.STARTED) {
			return;
		}
		onCancelCapture();
		waitForCaptureToFinish();
	}

	private void customizeFormat(NMediaFormat selectedFormat) {
		JDialog customizedDialog = new JDialog(this, true);
		customizedDialog.setPreferredSize(new Dimension(300, 300));
		customizedDialog.setTitle("Customize Format");
		CustomizeFormatDialog customPanel = new CustomizeFormatDialog(CaptureFrame.this, customizedDialog);
		customizedDialog.getContentPane().add(customPanel);
		customizedDialog.pack();
		customPanel.customizeFormat(selectedFormat);
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		customizedDialog.setLocation(screenSize.width / 2 - customizedDialog.getPreferredSize().width / 2, screenSize.height / 2 - customizedDialog.getPreferredSize().height / 2);
		customizedDialog.setVisible(true);
	}

	// ======================================================
	// Protected methods
	// ======================================================

	protected void onDeviceChanged() {
		if (device == null) {
			this.setTitle("No device");
		} else {
			this.setTitle(device.getDisplayName());
		}
		onStatusChanged();
	}

	protected void onStatusChanged() {
		synchronized (statusLock) {
			StringBuffer sb = new StringBuffer();
			BufferedImage theImage = null;
			String theUserStatus = null;
			if (isCapturing()) {
				sb.append(String.format("Capturing (%s fps)", fps));
				theImage = this.image;
				theUserStatus = userStatus;
			} else {
				sb.append("Finished");
				theImage = this.finalImage;
				theUserStatus = finalUserStatus;
			}

			if (pictureLabel.getIcon() != theImage) {
				if (pictureLabel.getIcon() != null) {
					pictureLabel.setIcon(null);
				}
				pictureLabel.setIcon(theImage == null ? null : new ImageIcon(theImage));
				pictureLabel.updateUI();
			}
			if (theImage != null) {
				sb.append(String.format(" (%sx%s ppi)", theImage.getWidth(), theImage.getHeight())); //TODO add resolution
			}
			if (theUserStatus != null) {
				sb.append(":" + userStatus);
			}
			sb.append("\n");
			txtStatus.setText(sb.toString());
			buttonForce.setEnabled(isCapturing);
			if (isCapturing) {
				buttonClose.setText("Cancel");
			} else {
				buttonClose.setText("Close");
			}
		}
	}

	protected final void checkIsBusy() {
		if (backgroundWorker != null && backgroundWorker.getState() == SwingWorker.StateValue.STARTED) {
			throw new IllegalStateException("Capturing is running");
		}
	}

	protected boolean isValidDeviceType(EnumSet<NDeviceType> value) {
		return true;
	}

	protected void onCaptureStarted() {
		isCapturing = true;
		onStatusChanged();
	}

	protected void onCaptureFinished() {
		isCapturing = false;
		onStatusChanged();
	}

	protected final boolean onImage(NImage image, String userStatus, String imageName, boolean isFinal) {
		synchronized (statusLock) {
			if (!isFinal) {
				long elapsed = System.currentTimeMillis();
				timestamps.addLast(elapsed);
				if (elapsed - lastReportTime >= 300) {
					long s = 0;
					@SuppressWarnings("unchecked")
					LinkedList<Long> timestampsCopy = (LinkedList<Long>) timestamps.clone();
					for (Long l : timestampsCopy) {
						s = (elapsed - l) / 1000;
						if (timestamps.size() <= 1 || s <= 1) {
							break;
						}
						timestamps.removeFirst();
					}
					if (s > 0) {
						fps = (int) Math.round(timestamps.size() / s);
					} else {
						fps = 0;
					}
					lastReportTime = elapsed;
				}
			}
			if (gatherImages && image != null) {
				try {
					image.save(String.format("%s/%s%s.png", imagesPath, isFinal ? "Final" : String.format("%08d", imageCount++), imageName == null ? "" : '_' + imageName));
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			BufferedImage bufferedImage = image == null ? null : rescaleImage((BufferedImage) image.toImage(), PREFERRED_HEIGHT, PREFERRED_WIDTH);
			if (isFinal) {
				this.finalImage = bufferedImage;
				this.finalUserStatus = userStatus;
			} else {
				this.image = bufferedImage;
				this.userStatus = userStatus;
			}
		}
		backgroundWorker.setWorkerProgress(0);
		onStatusChanged();
		return forceCapture;
	}

	protected final void writeParameter(Document doc, Element parent, String key, Object parameter) {
		Element element = doc.createElement("Parameter");
		element.setAttribute("Name", key);
		element.appendChild(doc.createTextNode(parameter.toString()));
		parent.appendChild(element);
	}

	protected void onWriteScanParameters(Document doc, Element parent) {
	}

	protected void onCancelCapture() {
		backgroundWorker.cancel(true);
	}

	protected abstract void onCapture();

	protected void addMediaFormatsHandler(Enumeration<NMediaFormat> mediaFormats, NMediaFormat currentFormat) {
	};

	protected final void addMediaFormats(NMediaFormat[] mediaFormats, NMediaFormat currentFormat) {
		if (mediaFormats == null) throw new NullPointerException("mediaFormats");
		suppressMediaFormatEvents = true;
		for (NMediaFormat mediaFormat : mediaFormats) {
			cmbFormats.addItem(mediaFormat);
		}

		if (currentFormat != null) {
			cmbFormats.setSelectedItem(currentFormat);
		}
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				cmbFormats.updateUI();
			}
		});
		suppressMediaFormatEvents = false;
	}

	protected void onMediaFormatChanged(NMediaFormat mediaFormat) {
	}

	protected Rectangle getPictureArea() {
		BufferedImage bmp = finalImage != null ? finalImage : image;
		int frameWidth = bmp == null ? 0 : bmp.getWidth();
		int frameHeight = bmp == null ? 0 : bmp.getHeight();
		Dimension cs = pictureLabel.getSize();
		float zoom = 1;
		if (frameWidth != 0 && frameHeight != 0)
			zoom = Math.min((float)cs.getWidth() / (float)frameWidth, (float)cs.getHeight() / (float)frameHeight);
		float sx = frameWidth * zoom;
		float sy = frameHeight * zoom;
		return new Rectangle((int)Math.round((cs.getWidth() - sx) / 2), (int)Math.round((cs.getHeight() - sy) / 2), (int)Math.round(sx), (int)Math.round(sy));
	}


	protected boolean isCapturing() {
		return isCapturing;
	}

	protected boolean hasFinal() {
		return finalImage != null;
	}

	protected final boolean isAutoCaptureStart() {
		return autoCaptureStart;
	}

	protected final void setAutoCaptureStart(boolean autoCaptureStart) {
		this.autoCaptureStart = autoCaptureStart;
	}

	protected final boolean isForcedCaptureEnabled() {
		return buttonForce.isVisible();
	}

	protected final void setForcedCaptureEnabled(boolean isForcedCaptureEnabled) {
		buttonForce.setVisible(isForcedCaptureEnabled);
	}

	protected final boolean isCancellationPending() {
		return backgroundWorker.getState() == SwingWorker.StateValue.PENDING;
	}

	protected final String getStatusText() {
		return statusText;
	}

	protected final void setStatusText(String statusText) {
		this.statusText = statusText;
		txtStatus.setText(statusText);
	}

	protected final JPanel getPicturePanel() {
		return picturePanel;
	}

	// ======================================================
	// Public methods
	// ======================================================

	public final void waitForCaptureToFinish() {
		while (backgroundWorker.getState() == SwingWorker.StateValue.STARTED) {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public final NDevice getDevice() {
		return device;
	}

	public final void setDevice(NDevice device) {
		if (this.device != device) {
			if (this.device != null && !isValidDeviceType(this.device.getDeviceType())) {
				throw new IllegalArgumentException("Invalid NDevice type");
			}
			checkIsBusy();
			this.device = device;
			onDeviceChanged();
		}
	}

	public final boolean isGatherImages() {
		return gatherImages;
	}

	public final void setGatherImages(boolean gatherImages) {
		if (this.gatherImages != gatherImages) {
			checkIsBusy();
			this.gatherImages = gatherImages;
		}
	}

	public final void createTimeStamps() {
		timestamps = new LinkedList<Long>();
	}

	public final void selectNewCustomFormat(NMediaFormat customFormat) {
		if (customFormat != null) {
			int index = getIndexOfJComboBoxItem(cmbFormats, customFormat);
			if (index == -1) {
				cmbFormats.addItem(customFormat);
				SwingUtilities.invokeLater(new Runnable() {

					public void run() {
						cmbFormats.updateUI();

					}
				});
			}
			cmbFormats.setSelectedItem(customFormat);
		}
	}

	// ============================================
	// Private class extending ComponentAdapter
	// ============================================

	private class CaptureFrameListener extends ComponentAdapter {
		@Override
		/**
		 * when the capture frame is shown
		 * if user asked to gather images crate a new folder to store scan info
		 */
		public void componentShown(ComponentEvent arg0) {
			if (device == null) {
				return;
			}
			if (gatherImages) {
				String devicePath = String.format("%s_%s", getDevice().getMake(), getDevice().getModel());
				File deviceDirectory = new File(devicePath);
				if (!deviceDirectory.exists()) {
					deviceDirectory.mkdir();
				}
				imagesPath = devicePath + "/" + UUID.randomUUID().toString();
				File imagesDirectory = new File(imagesPath);
				if (!imagesDirectory.exists()) {
					imagesDirectory.mkdir();
				}
				imageCount = 0;

				try {
					DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
					DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
					Document doc = docBuilder.newDocument();
					Element rootElement = doc.createElement("Scan");
					doc.appendChild(rootElement);

					onWriteScanParameters(doc, rootElement);

					TransformerFactory transformerFactory = TransformerFactory.newInstance();
					Transformer transformer = transformerFactory.newTransformer();
					DOMSource source = new DOMSource(doc);
					StreamResult result =  new StreamResult(new File(imagesPath + "/" + "ScanInfo.xml"));
					transformer.transform(source, result);
				} catch (ParserConfigurationException e) {
					e.printStackTrace();
				} catch (TransformerException e) {
					e.printStackTrace();
				}
			}
			if (!autoCaptureStart) {
				onCaptureStarted();
			}
			if (backgroundWorker != null) {
				backgroundWorker.cancel(true);
			}
			backgroundWorker = new BackgroundWorker(CaptureFrame.this);
			backgroundWorker.execute();
		}
	}

	// ============================================
	// Private class extending SwingWorker
	// ============================================

	private class BackgroundWorker extends SwingWorker<String, Object> implements PropertyChangeListener {

		// ===========================================================
		// Private  fields
		// ===========================================================

		private CaptureFrame captureFrame;

		// ===========================================================
		// Private constructor
		// ===========================================================

		private BackgroundWorker(CaptureFrame captureFrame) {
			super();
			this.captureFrame = captureFrame;
			this.addPropertyChangeListener(this);
		}

		// ==========================================================
		// Overridden methods
		// ==========================================================

		@Override
		protected String doInBackground() throws Exception {
			captureFrame.createTimeStamps();
			captureFrame.onCapture();
			return null;
		}

		@Override
		protected void done() {
			try {
				if (!captureFrame.isAutoCaptureStart()) {
					captureFrame.onCaptureFinished();
				}
			} catch (Exception e) {
				SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(captureFrame, e.toString()); });
			}
		}

		// ========================================================
		// Public methods
		// ========================================================

		public void setWorkerProgress(int progress) {
			setProgress(progress);
			captureFrame.onStatusChanged();
		}

		// ======================================================
		// Event handling
		// ======================================================

		public void propertyChange(PropertyChangeEvent arg0) {
			captureFrame.onStatusChanged();
		}

	}
}
