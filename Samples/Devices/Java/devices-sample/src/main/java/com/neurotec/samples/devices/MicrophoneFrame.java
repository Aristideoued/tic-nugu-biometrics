package com.neurotec.samples.devices;

import java.awt.Dimension;
import java.util.EnumSet;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JProgressBar;

import com.neurotec.devices.NDeviceType;
import com.neurotec.devices.NMicrophone;
import com.neurotec.sound.NSoundBuffer;
import com.neurotec.sound.processing.NSoundProc;

public final class MicrophoneFrame extends CaptureDeviceFrame {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================

	private double soundLevel;

	// ==============================================
	// Private GUI controls
	// ==============================================

	private JProgressBar soundLevelProgressBar;

	// ==============================================
	// Public constructor
	// ==============================================

	public MicrophoneFrame(JFrame parent) {
		super(parent);
		setForcedCaptureEnabled(false);
	}

	// ==============================================
	// Private methods
	// ==============================================

	@Override
	protected void initGUI() {
		super.initGUI();
		soundLevelProgressBar = new JProgressBar();
		soundLevelProgressBar.setPreferredSize(new Dimension(200, 40));
		JPanel picturePanel = getPicturePanel();
		picturePanel.removeAll();

		picturePanel.setLayout(new BoxLayout(picturePanel, BoxLayout.Y_AXIS));
		picturePanel.add(Box.createVerticalStrut(140));

		Box middleBox = Box.createHorizontalBox();
		middleBox.add(Box.createHorizontalStrut(140));
		middleBox.add(soundLevelProgressBar);
		middleBox.add(Box.createGlue());

		picturePanel.add(middleBox);
		picturePanel.add(Box.createGlue());
	}

	private void onSoundSample(NSoundBuffer soundBuffer) {
		synchronized (statusLock) {
			soundLevel = NSoundProc.getSoundLevel(soundBuffer);
		}
		onStatusChanged();
	}

	// ==============================================
	// Protected methods
	// ==============================================

	@Override
	protected void onStatusChanged() {
		synchronized (statusLock) {
			int level = (int) (soundLevel * 100.0);
			soundLevelProgressBar.setValue(level);
			soundLevelProgressBar.setVisible(isCapturing());
		}
		super.onStatusChanged();
	}

	@Override
	protected boolean isValidDeviceType(EnumSet<NDeviceType> value) {
		return super.isValidDeviceType(value) && value.contains(NDeviceType.MICROPHONE);
	}

	@Override
	protected boolean onObtainSample() {
		NMicrophone microphone = (NMicrophone)getDevice();
		NSoundBuffer soundSample = null;
		try {
			soundSample = microphone.getSoundSample();
			if (soundSample != null) {
				onSoundSample(soundSample);
				return true;
			}
			return false;
		} finally {
			if (soundSample != null) soundSample.dispose();
		}
	}
}
