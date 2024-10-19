package com.neurotec.samples.devices;

import java.util.EnumSet;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

import com.neurotec.biometrics.NBiometricCaptureOption;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFAttributes;
import com.neurotec.biometrics.NFImpressionType;
import com.neurotec.biometrics.NFPosition;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NFrictionRidge;
import com.neurotec.biometrics.NPalm;
import com.neurotec.biometrics.NSubject;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NFScanner;
import com.neurotec.devices.event.NBiometricDeviceCapturePreviewEvent;
import com.neurotec.devices.event.NBiometricDeviceCapturePreviewListener;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public final class FScannerFrame extends BiometricDeviceFrame implements NBiometricDeviceCapturePreviewListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================

	private NFImpressionType impressionType;
	private NFPosition position;
	private NFPosition[] missingPositions;

	// ==============================================
	// Public constructor
	// ==============================================

	public FScannerFrame(JFrame parent) {
		super(parent);
	}

	// ==============================================
	// Private methods
	// ==============================================

	private boolean onImage(NFrictionRidge biometric, boolean isFinal) {
		StringBuilder sb = new StringBuilder();
		sb.append(biometric.getStatus());
		for (NFAttributes obj : biometric.getObjects()) {
			sb.append("\n");
			sb.append(String.format("\t{%s}: {%s}", obj.getPosition(), obj.getStatus()));
		}
		return onImage(biometric.getImage(), sb.toString(), (biometric.getStatus() != NBiometricStatus.NONE ? biometric.getStatus() : NBiometricStatus.OK).toString(), isFinal);
	}

	// ==============================================
	// Protected methods
	// ==============================================

	@Override
	protected boolean isValidDeviceType(EnumSet<NDeviceType> value) {
		return super.isValidDeviceType(value) && value.contains(NDeviceType.FINGER_SCANNER);
	}

	@Override
	protected void onCapture() {
		NFScanner fScanner = (NFScanner) getDevice();
		fScanner.addCapturePreviewListener(this);
		NSubject subject = new NSubject();
		try {
			if (missingPositions != null) {
				for (NFPosition missingPosition : missingPositions) {
					subject.getMissingFingers().add(missingPosition);
				}
			}
			NFrictionRidge biometric = NFrictionRidge.fromPosition(position);
			try {
				biometric.setImpressionType(impressionType);
				biometric.setPosition(position);
				if (position.isFinger()) {
					subject.getFingers().add((NFinger) biometric);
				} else {
					subject.getPalms().add(((NPalm) biometric));
				}
				if (!isAutomatic()) biometric.setCaptureOptions(EnumSet.of(NBiometricCaptureOption.MANUAL));
				fScanner.capture(biometric, getTimeout());
				onImage(biometric, true);
			} finally {
				biometric.dispose();
			}
		} catch (Exception e) {
			SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, e.toString()); });
		} finally {
			fScanner.removeCapturePreviewListener(this);
			subject.dispose();
		}
	}

	@Override
	protected void onWriteScanParameters(Document doc, Element parent) {
		super.onWriteScanParameters(doc, parent);
		writeParameter(doc, parent, "ImpressionType", getImpressionType());
		writeParameter(doc, parent, "Position", getPosition());
		if (getMissingPositions() != null) {
			for (NFPosition position : getMissingPositions()) {
				writeParameter(doc, parent, "Missing", position);
			}
		}
	}

	// ==============================================
	// Public methods
	// ==============================================

	public NFImpressionType getImpressionType() {
		return impressionType;
	}

	public void setImpressionType(NFImpressionType impressionType) {
		if (this.impressionType != impressionType) {
			checkIsBusy();
			this.impressionType = impressionType;
		}
	}

	public NFPosition getPosition() {
		return position;
	}

	public void setPosition(NFPosition position) {
		if (this.position != position) {
			checkIsBusy();
			this.position = position;
		}
	}

	public NFPosition[] getMissingPositions() {
		return missingPositions;
	}

	public void setMissingPositions(NFPosition[] missingPositions) {
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
		boolean force = onImage((NFrictionRidge)event.getBiometric(), false);
		NBiometricStatus status = event.getBiometric().getStatus();
		if (!isAutomatic()) {
			if (status == NBiometricStatus.OK || !status.isFinal())
			event.getBiometric().setStatus(force ? NBiometricStatus.OK : NBiometricStatus.BAD_OBJECT);
		} else if (force) {
			event.getBiometric().setStatus(NBiometricStatus.OK);
		}
	}

}
