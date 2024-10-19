package com.neurotec.samples.devices;

import java.util.EnumSet;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.neurotec.biometrics.NBiometricCaptureOption;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NAAttributes;
import com.neurotec.biometrics.NSignature;
import com.neurotec.biometrics.NSubject;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NSignatureScanner;
import com.neurotec.devices.event.NBiometricDeviceCapturePreviewEvent;
import com.neurotec.devices.event.NBiometricDeviceCapturePreviewListener;
import com.neurotec.media.NMediaFormat;

public final class SignatureScannerFrame extends BiometricDeviceFrame implements NBiometricDeviceCapturePreviewListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;
	
	// ==============================================
	// Public constructor
	// ==============================================

	public SignatureScannerFrame(JFrame parent) {
		super(parent);
		onDeviceChanged();
	}

	// ==============================================
	// Private methods
	// ==============================================

	private boolean onImage(NSignature biometric, boolean isFinal) {
		StringBuilder sb = new StringBuilder();
		sb.append(biometric.getStatus());
		return onImage(biometric.getImage(), sb.toString(), (biometric.getStatus() != NBiometricStatus.NONE ? biometric.getStatus() : NBiometricStatus.OK).toString(), isFinal);
	}

	// ==============================================
	// Protected methods
	// ==============================================

	@Override
	protected boolean isValidDeviceType(EnumSet<NDeviceType> value) {
		return super.isValidDeviceType(value) && value.contains(NDeviceType.SIGNATURE_SCANNER);
	}

	@Override
	protected void onCapture() {
		NSignatureScanner signatureScanner = (NSignatureScanner) getDevice();
		signatureScanner.addCapturePreviewListener(this);
		NSubject subject = new NSubject();
		try {
			NSignature signature = new NSignature();
			try {
				signatureScanner.capture(signature, getTimeout());
				onImage(signature, true);
			} finally {
				signature.dispose();
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(this, e.toString());
		} finally {
			signatureScanner.removeCapturePreviewListener(this);
			subject.dispose();
		}
	}

	@Override
	protected void onWriteScanParameters(Document doc, Element parent) {
		super.onWriteScanParameters(doc, parent);
	}

	@Override
	protected void onMediaFormatChanged(NMediaFormat mediaFormat) {
	}

	// ==============================================
	// Event handling
	// ==============================================

	@Override
	public void capturePreview(NBiometricDeviceCapturePreviewEvent event) {
		boolean force = onImage((NSignature)event.getBiometric(), false);
		NBiometricStatus status = event.getBiometric().getStatus();
		if (!status.isFinal()) {
			event.getBiometric().setStatus(force ? NBiometricStatus.OK : NBiometricStatus.NONE);
		}
	}
}
