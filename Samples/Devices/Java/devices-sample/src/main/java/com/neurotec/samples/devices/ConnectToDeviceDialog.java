package com.neurotec.samples.devices;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import com.neurotec.beans.NParameterBag;
import com.neurotec.beans.NParameterDescriptor;
import com.neurotec.devices.NDeviceManager;
import com.neurotec.lang.NAttribute;
import com.neurotec.plugins.NPlugin;
import com.neurotec.plugins.NPluginState;
import com.neurotec.swing.NPropertyGrid;
import com.neurotec.util.NPropertyBag;

public final class ConnectToDeviceDialog extends JDialog implements ActionListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// =============================================
	// Private methods
	// =============================================

	private JButton buttonOk;
	private JButton buttonCancel;
	private NPropertyGrid propertyGrid;
	private JComboBox comboBoxPlugins;
	private DefaultComboBoxModel model;

	private NParameterDescriptor[] parameters;
	private boolean isValid = false;

	// ==============================================
	// Public constructor
	// ==============================================

	ConnectToDeviceDialog(JFrame owner) {
		super(owner);
		initGUI();
		for (NPlugin plugin : NDeviceManager.getPluginManager().getPlugins()) {
			if (plugin.getState() == NPluginState.PLUGGED && NDeviceManager.isConnectToDeviceSupported(plugin)) {
				comboBoxPlugins.addItem(plugin);
			}
		}
		if (model.getSize() > 0) {
			comboBoxPlugins.setSelectedIndex(0);
		}
		onSelectedPluginChanged();
		comboBoxPlugins.updateUI();
		comboBoxPlugins.revalidate();
		comboBoxPlugins.invalidate();
	}

	// =============================================
	// Private methods
	// =============================================

	private void initGUI() {
		this.setTitle("Connect to device");
		Dimension size = new Dimension(450, 540);
		this.setPreferredSize(size);
		this.setMinimumSize(size);
		setLayout(new BorderLayout());

		JPanel panelPlugins = new JPanel();
		FlowLayout flowLayout = (FlowLayout) panelPlugins.getLayout();
		flowLayout.setAlignment(FlowLayout.LEFT);
		getContentPane().add(panelPlugins, BorderLayout.NORTH);

		JLabel lblPlugin = new JLabel("Plugin:");
		panelPlugins.add(lblPlugin);

		model = new DefaultComboBoxModel();
		comboBoxPlugins = new JComboBox(model);
		panelPlugins.add(comboBoxPlugins);
		comboBoxPlugins.addItemListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent event) {
				if (event.getStateChange() == ItemEvent.SELECTED) {
					onSelectedPluginChanged();
				}
			}
		});

		propertyGrid = new NPropertyGrid();
		getContentPane().add(propertyGrid, BorderLayout.CENTER);

		JPanel panelButtons = new JPanel();
		panelButtons.setLayout(new FlowLayout(FlowLayout.RIGHT, 5, 5));
		getContentPane().add(panelButtons, BorderLayout.AFTER_LAST_LINE);

		buttonOk = new JButton("OK");
		buttonOk.addActionListener(this);
		panelButtons.add(buttonOk);

		buttonCancel = new JButton("Cancel");
		buttonCancel.addActionListener(this);
		panelButtons.add(buttonCancel);
	}

	private void onSelectedPluginChanged() {
		NPlugin plugin = getSelectedPlugin();
		parameters = plugin == null ? null : NDeviceManager.getConnectToDeviceParameters(plugin);
		NParameterBag parameterBag = new NParameterBag(parameters);
		propertyGrid.setSource(parameterBag);
		buttonOk.setEnabled(plugin != null);
		propertyGrid.setEnabled(plugin != null);
	}

	private boolean isParametersValid() {
		if (parameters != null) {
			NParameterBag parameterBag = (NParameterBag)propertyGrid.getSource();
			for (int i = 0; i < parameters.length; i++) {
				if (!(parameters[i].getAttributes().contains(NAttribute.OPTIONAL))) {
					if (parameterBag.values().get(i) == null) {
						final int index = i;
						SwingUtilities.invokeLater(() -> { JOptionPane.showMessageDialog(this, String.format("{0} value not specified", parameters[index].getName()), getTitle(), JOptionPane.WARNING_MESSAGE); });
						return false;
					}
				}
			}
		}
		return true;
	}

	// =============================================
	// Public methods
	// =============================================

	@Override
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		if (source == buttonOk) {
			propertyGrid.stopEditing();
			isValid = isParametersValid();
			if (isValid) {
				setVisible(false);
				dispose();
			}
		} else if (source == buttonCancel) {
			setVisible(false);
			dispose();
		}
	}

	public NPlugin getSelectedPlugin() {
		return (NPlugin) comboBoxPlugins.getSelectedItem();
	}

	public void setSelectedPlugin(NPlugin plugin) {
		if (model.getIndexOf(plugin) != -1) {
			comboBoxPlugins.setSelectedItem(plugin);
		}
	}

	public NPropertyBag getParameters() {
		if (!isValid) return null;
		NParameterBag parameterBag = (NParameterBag) propertyGrid.getSource();
		return parameterBag == null ? null : parameterBag.toPropertyBag();
	}

	public void setParameters(NPropertyBag value) {
		NParameterBag parameterBag = (NParameterBag) propertyGrid.getSource();
		if (parameterBag != null) {
			parameterBag.apply(value, true);
		}
	}

	public boolean showDialog() {
		setModal(true);
		setVisible(true);
		return isValid;
	}
}
