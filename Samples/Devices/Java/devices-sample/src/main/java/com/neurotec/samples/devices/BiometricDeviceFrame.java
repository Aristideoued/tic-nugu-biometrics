package com.neurotec.samples.devices;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.neurotec.devices.NBiometricDevice;
import com.neurotec.devices.NDeviceType;

import java.util.EnumSet;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

public abstract class BiometricDeviceFrame extends CaptureFrame {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================

	private boolean automatic = true;
	private int timeout = -1;

	// ==============================================
	// Protected constructor
	// ==============================================

	protected BiometricDeviceFrame(JFrame parent) {
		super(parent);
	}

	// ==============================================
	// Protected methods
	// ==============================================

	@Override
	protected boolean isValidDeviceType(EnumSet<NDeviceType> value) {
		return super.isValidDeviceType(value) && value.contains(NDeviceType.BIOMETRIC_DEVICE);
	}

	@Override
	protected final void onCancelCapture() {
		super.onCancelCapture();
		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					((NBiometricDevice) getDevice()).cancel();
				} catch (Exception e) {
					SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(BiometricDeviceFrame.this, e.toString()); });
				}

			}
		}).start();
	}

	@Override
	protected void onWriteScanParameters(Document doc, Element parent) {
		super.onWriteScanParameters(doc, parent);
		writeParameter(doc, parent, "Modality", ((NBiometricDevice) getDevice()).getBiometricType());
	}

	// ============================================
	// Public methods
	// ============================================

	public final boolean isAutomatic() {
		return automatic;
	}

	public final void setAutomatic(boolean automatic) {
		if (this.automatic != automatic) {
			checkIsBusy();
			this.automatic = automatic;
		}
	}

	public final int getTimeout() {
		return timeout;
	}

	public final void setTimeout(int timeout) {
		if (this.timeout != timeout) {
			checkIsBusy();
			this.timeout = timeout;
		}
	}
}
