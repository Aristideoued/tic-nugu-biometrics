package com.neurotec.samples.devices;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import com.neurotec.media.NMediaFormat;
import com.neurotec.swing.NPropertyGrid;
import com.neurotec.samples.devices.events.CustomizeFormatListener;

public final class CustomizeFormatDialog extends JPanel implements ActionListener {

	// ==============================================
	// Private static fields
	// ==============================================
	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================
	private NMediaFormat clone;
	private Container parent;
	private Container owner;

	// =============================================
	// Private GUI controls
	// =============================================
	private JButton buttonOk;
	private JButton buttonCancel;
	private NPropertyGrid formatsPropertyGrid;

	// ==============================================
	// Public constructor
	// ==============================================
	public CustomizeFormatDialog(Container parent, Container owner) {
		this.parent = parent;
		this.owner = owner;
		initializeComponents();
	}

	// =============================================
	// Private methods
	// =============================================
	private void initializeComponents() {
		this.setLayout(new BorderLayout());
		formatsPropertyGrid = new NPropertyGrid();

		buttonOk = new JButton("OK");
		buttonOk.addActionListener(this);

		buttonCancel = new JButton("Cancel");
		buttonCancel.addActionListener(this);

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
		buttonPanel.add(Box.createGlue());
		buttonPanel.add(buttonOk);
		buttonPanel.add(Box.createHorizontalStrut(3));
		buttonPanel.add(buttonCancel);
		buttonPanel.add(Box.createHorizontalStrut(2));

		this.add(formatsPropertyGrid, BorderLayout.CENTER);
		this.add(buttonPanel, BorderLayout.AFTER_LAST_LINE);
	}

	// =============================================
	// Public methods
	// =============================================
	public void customizeFormat(NMediaFormat mediaFormat) {
		if (mediaFormat == null) {
			throw new NullPointerException("mediaFormat");
		}
		try {
			clone = (NMediaFormat) mediaFormat.clone();
			formatsPropertyGrid.setSource(clone);

		} catch (CloneNotSupportedException e) {
			SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, e.toString()); });
		}
	}

	// =============================================
	// Event handling
	// =============================================
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		if (source == buttonOk) {
			formatsPropertyGrid.stopEditing();
			if (parent instanceof CustomizeFormatListener) {
				((CustomizeFormatListener) parent).selectNewCustomFormat(clone);
			}
		} else if (source == buttonCancel) {
			clone.dispose();
		}
		if (owner instanceof JDialog) {
			((JDialog) owner).dispose();
		} else if (owner instanceof JFrame) {
			((JFrame) owner).dispose();
		}
	}
}
