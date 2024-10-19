package com.neurotec.samples.devices;

import java.util.EnumSet;

import javax.swing.JFrame;

import com.neurotec.devices.NCaptureDevice;
import com.neurotec.devices.NDeviceType;
import com.neurotec.event.ChangeEvent;
import com.neurotec.event.ChangeListener;
import com.neurotec.media.NMediaFormat;

public class CaptureDeviceFrame extends CaptureFrame implements ChangeListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================

	private NMediaFormat nextMediaFormat;
	private Object nextMediaFormatLock = new Object();

	// ==============================================
	// Public constructor
	// ==============================================

	public CaptureDeviceFrame(JFrame parent) {
		super(parent);
		setAutoCaptureStart(true);
	}

	// ==============================================
	// Protected methods
	// ==============================================

	@Override
	protected boolean isValidDeviceType(EnumSet<NDeviceType> value) {
		return super.isValidDeviceType(value) && (value.contains(NDeviceType.CAPTURE_DEVICE));
	}

	@Override
	protected void onCapture() {
		NCaptureDevice captureDevice = (NCaptureDevice) getDevice();
		captureDevice.addCapturingChangedListener(this);
		onStartingCapture();
		boolean stoppedCapturing = false;
		try {
			captureDevice.startCapturing();
			boolean sampleObtained = true;
			try {
				addMediaFormats(captureDevice.getFormats(), captureDevice.getCurrentFormat());
				while (sampleObtained && !isCancellationPending()) {
					synchronized (nextMediaFormatLock) {
						if (nextMediaFormat != null) {
							captureDevice.setCurrentFormat(nextMediaFormat);
							nextMediaFormat = null;
						}
					}
					sampleObtained = onObtainSample();
				}
			} catch (Exception e) {
				StringBuilder statusTextBuilder = new StringBuilder();
				statusTextBuilder.append(getStatusText());
				statusTextBuilder.append("Error: ");
				statusTextBuilder.append(e.toString());
				setStatusText(statusTextBuilder.toString());
			} finally {
				if (sampleObtained && captureDevice.isAvailable()) {
					captureDevice.stopCapturing();
					stoppedCapturing = true;
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			captureDevice.removeCapturingChangedListener(this);
			onFinishingCapture();
			if (!stoppedCapturing) onCaptureFinished();
		}
	}

	@Override
	protected void onCancelCapture() {
		super.onCancelCapture();
		if (getDevice().isAvailable()) {
			((NCaptureDevice)getDevice()).stopCapturing();
		}
	}

	@Override
	protected void onMediaFormatChanged(NMediaFormat mediaFormat) {
		synchronized (nextMediaFormatLock) {
			nextMediaFormat = mediaFormat;
		}
	}

	protected boolean onObtainSample() {
		throw new UnsupportedOperationException();
	}

	protected void onStartingCapture() {
	}

	protected void onFinishingCapture() {
	}

	// ======================================================
	// Event handling
	// ======================================================

	@Override
	public void stateChanged(ChangeEvent e) {
		if (getDevice().isAvailable() && ((NCaptureDevice) getDevice()).isCapturing()) {
			onCaptureStarted();
		} else {
			onCaptureFinished();
		}
	}

}
