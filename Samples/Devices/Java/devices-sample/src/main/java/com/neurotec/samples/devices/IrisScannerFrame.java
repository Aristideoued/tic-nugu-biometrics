package com.neurotec.samples.devices;

import java.util.EnumSet;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.neurotec.biometrics.NBiometricCaptureOption;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NEAttributes;
import com.neurotec.biometrics.NEPosition;
import com.neurotec.biometrics.NIris;
import com.neurotec.biometrics.NSubject;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NIrisScanner;
import com.neurotec.devices.event.NBiometricDeviceCapturePreviewEvent;
import com.neurotec.devices.event.NBiometricDeviceCapturePreviewListener;
import com.neurotec.media.NMediaFormat;

public final class IrisScannerFrame extends BiometricDeviceFrame implements NBiometricDeviceCapturePreviewListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================

	private NEPosition position;
	private NEPosition[] missingPositions;

	// ==============================================
	// Public constructor
	// ==============================================

	public IrisScannerFrame(JFrame parent) {
		super(parent);
		onDeviceChanged();
	}

	// ==============================================
	// Private methods
	// ==============================================

	private boolean onImage(NIris biometric, boolean isFinal) {
		StringBuilder sb = new StringBuilder();
		sb.append(biometric.getStatus());
		for (NEAttributes obj : biometric.getObjects()) {
			sb.append("\n");
			sb.append(String.format("\t%s: %s (Position: $s)", obj.getPosition(), obj.getStatus(), obj.getBoundingRect()));
		}
		return onImage(biometric.getImage(), sb.toString(), (biometric.getStatus() != NBiometricStatus.NONE ? biometric.getStatus() : NBiometricStatus.OK).toString(), isFinal);
	}

	// ==============================================
	// Protected methods
	// ==============================================

	@Override
	protected boolean isValidDeviceType(EnumSet<NDeviceType> value) {
		return super.isValidDeviceType(value) && value.contains(NDeviceType.IRIS_SCANNER);
	}

	@Override
	protected void onCapture() {
		NIrisScanner irisScanner = (NIrisScanner) getDevice();
		irisScanner.addCapturePreviewListener(this);
		NSubject subject = new NSubject();
		try {
			if (missingPositions != null) {
				for (NEPosition missingPosition : missingPositions) {
					subject.getMissingEyes().add(missingPosition);
				}
			}
			NIris iris = new NIris();
			try {
				iris.setPosition(position);
				if (!isAutomatic()) iris.setCaptureOptions(EnumSet.of(NBiometricCaptureOption.MANUAL));
				irisScanner.capture(iris, getTimeout());
				onImage(iris, true);
			} finally {
				iris.dispose();
			}
		} catch (Exception e) {
			SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, e.toString()); });
		} finally {
			irisScanner.removeCapturePreviewListener(this);
			subject.dispose();
		}
	}

	@Override
	protected void onWriteScanParameters(Document doc, Element parent) {
		super.onWriteScanParameters(doc, parent);
		writeParameter(doc, parent, "Position", getPosition());
		if (getMissingPositions() != null) {
			for (NEPosition position : getMissingPositions()) {
				writeParameter(doc, parent, "Missing", position);
			}
		}
	}

	@Override
	protected void onMediaFormatChanged(NMediaFormat mediaFormat) {
	}

	// ==============================================
	// Public methods
	// ==============================================

	public NEPosition getPosition() {
		return position;
	}

	public void setPosition(NEPosition position) {
		if (this.position != position) {
			checkIsBusy();
			this.position = position;
		}
	}

	public NEPosition[] getMissingPositions() {
		return missingPositions;
	}

	public void setMissingPositions(NEPosition[] missingPositions) {
		if (this.missingPositions != missingPositions) {
			checkIsBusy();
			this.missingPositions = missingPositions;
		}
	}

	// ==============================================
	// Event handling
	// ==============================================

	@Override
	public void capturePreview(NBiometricDeviceCapturePreviewEvent event) {
		boolean force = onImage((NIris)event.getBiometric(), false);
		NBiometricStatus status = event.getBiometric().getStatus();
		if (!isAutomatic()) {
			if (status == NBiometricStatus.OK || !status.isFinal())
			event.getBiometric().setStatus(force ? NBiometricStatus.OK : NBiometricStatus.BAD_OBJECT);
		} else if (force) {
			event.getBiometric().setStatus(NBiometricStatus.OK);
		}
	}
}
