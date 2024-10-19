package com.neurotec.samples.devices;

import java.awt.geom.Rectangle2D;
import java.io.IOException;
import java.util.EnumSet;

import javax.swing.JFrame;

import com.neurotec.devices.NCamera;
import com.neurotec.devices.NCameraStatus;
import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.event.NCameraStillCaptureListener;
import com.neurotec.devices.event.NCameraStillCapturedEvent;
import com.neurotec.images.NImage;

public final class CameraFrame extends CaptureDeviceFrame implements NCameraStillCaptureListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================

	private NCameraStatus cameraStatus = NCameraStatus.NONE;
	private Rectangle2D.Float focusRegion;
//	private readonly Pen _focusPen = Pens.White;

	// ==============================================
	// Public constructor
	// ==============================================

	public CameraFrame(JFrame parent) {
		super(parent);
		onDeviceChanged();
		onCameraStatusChanged();
	}

	// ==============================================
	// Private methods
	// ==============================================
	private void onCameraStatusChanged() {
		//TODO implement
//		cameraStatusLabel.Text = cameraStatus == NCameraStatus.NONE ? null : cameraStatus.toString();
	}

	// ==============================================
	// Protected methods
	// ==============================================

	@Override
	protected boolean isValidDeviceType(EnumSet<NDeviceType> value) {
		return super.isValidDeviceType(value) && (value.contains(NDeviceType.CAMERA));
	}

	@Override
	protected void onDeviceChanged() {
		super.onDeviceChanged();
		NCamera camera = (NCamera)getDevice();
		setForcedCaptureEnabled(camera != null && camera.isStillCaptureSupported());
		//TODO finish up
//		resetFocusButton.Visible = focusButton.Visible = camera != null && camera.IsFocusSupported;
//		clickToFocusCheckBox.Visible = camera != null && camera.IsFocusRegionSupported;
	}

	@Override
	protected void onStatusChanged() {
		super.onStatusChanged();
		//TODO finish up
//		resetFocusButton.Enabled = focusButton.Enabled = IsCapturing;
//		clickToFocusCheckBox.Enabled = IsCapturing;
	}

	@Override
	protected void onStartingCapture() {
		super.onStartingCapture();
		NCamera camera = (NCamera) getDevice();
		camera.addStillCaptureListener(this);

	}

	@Override
	protected void onFinishingCapture() {
		super.onFinishingCapture();
		NCamera camera = (NCamera) getDevice();
		camera.removeStillCaptureListener(this);
	}

	@Override
	protected boolean onObtainSample() {
		NCamera camera = (NCamera)getDevice();
		NImage image = null;
		try {
			image = camera.getFrame();
			if (image != null) {
				Rectangle2D.Float focusRegion = camera.getFocusRegion();
				synchronized (statusLock) {
					this.focusRegion = focusRegion;
				}
				if (onImage(image, null, null, false)) {
					camera.captureStill();
				}
				return true;
			}
			return false;
		} finally {
			if (image != null) image.dispose();
		}
	}

	@Override
	protected void onCaptureFinished() {
		synchronized (statusLock) {
			focusRegion = null;
		}
		super.onCaptureFinished();
	}

	// ==============================================
	// Public methods
	// ==============================================

	@Override
	public void stillCaptured(NCameraStillCapturedEvent event) {
		if (!hasFinal()) {
			NImage image = null;
			try {
				try {
					image = NImage.fromStream(event.getStream());
					onImage(image, null, null, true);
				} catch (IOException e) {
					e.printStackTrace();
				}
			} finally {
				if (image != null) image.dispose();
			}
			onCancelCapture();
		}
	}

}
