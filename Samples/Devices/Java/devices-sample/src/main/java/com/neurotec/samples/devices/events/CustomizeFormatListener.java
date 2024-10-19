package com.neurotec.samples.devices.events;

import com.neurotec.media.NMediaFormat;

/**
 * Interface for MainFrame and CaptureFrame to have customize format functionality.
 *
 */
public interface CustomizeFormatListener {

	void selectNewCustomFormat(NMediaFormat customFormat);

}
