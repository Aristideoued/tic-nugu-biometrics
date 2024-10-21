package com.neurotec.samples.swing.controls;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

import com.neurotec.biometrics.NFPosition;
import com.neurotec.biometrics.swing.NFingerView;
import com.neurotec.samples.swing.GridBagUtils;

public final class SlapsPanel extends JPanel {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================
	private NFingerView nfvLeftFour;
	private NFingerView nfvRightFour;
	private NFingerView nfvThumbs;

	// ==============================================
	// Public constructor
	// ==============================================

	public SlapsPanel() {
		initializeComponents();
	}

	// ==============================================
	// Private methods
	// ==============================================

	private void initializeComponents() {
		GridBagLayout slapsPanelLayout = new GridBagLayout();
		slapsPanelLayout.rowHeights = new int[] {20, 365};
		setLayout(slapsPanelLayout);

		nfvLeftFour = new NFingerView();
		nfvLeftFour.setAutofit(true);
		JPanel leftPanel = new JPanel(new BorderLayout());
		leftPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		leftPanel.add(nfvLeftFour, BorderLayout.CENTER);
		leftPanel.setPreferredSize(leftPanel.getPreferredSize());
		JScrollPane leftScrollPane = new JScrollPane(leftPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		nfvThumbs = new NFingerView();
		nfvThumbs.setAutofit(true);
		JPanel thumbsPanel = new JPanel(new BorderLayout());
		thumbsPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		thumbsPanel.add(nfvThumbs, BorderLayout.CENTER);
		thumbsPanel.setPreferredSize(thumbsPanel.getPreferredSize());
		JScrollPane thumbScrollPane = new JScrollPane(thumbsPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		nfvRightFour = new NFingerView();
		nfvRightFour.setAutofit(true);
		JPanel rightPanel = new JPanel(new BorderLayout());
		rightPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		rightPanel.add(nfvRightFour, BorderLayout.CENTER);
		rightPanel.setPreferredSize(rightPanel.getPreferredSize());
		JScrollPane rightScrollPane = new JScrollPane(rightPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		GridBagUtils gridBagUtils = new GridBagUtils(GridBagConstraints.BOTH);
		gridBagUtils.setInsets(new Insets(1, 1, 1, 1));

		gridBagUtils.addToGridBagLayout(0, 0, 1, 1, 0.3, 0, this, new JLabel("Quatre doigts de la main gauche"));
		gridBagUtils.addToGridBagLayout(1, 0, this, new JLabel("Pouces"));
		gridBagUtils.addToGridBagLayout(2, 0, this, new JLabel("Quatre doigts de la main droite"));
		gridBagUtils.addToGridBagLayout(0, 1, 1, 1, 0.3, 1, this, leftScrollPane);
		gridBagUtils.addToGridBagLayout(1, 1, this, thumbScrollPane);
		gridBagUtils.addToGridBagLayout(2, 1, this, rightScrollPane);



		JButton saveAllButton = new JButton("Enregistrer toutes les empreintes");
		saveAllButton.setPreferredSize(new Dimension(50, 40));  // Largeur 150, Hauteur 40

		saveAllButton.setBackground(new Color(0, 128, 255));  // Bleu clair
		saveAllButton.setForeground(Color.WHITE);  // Texte en blanc

		// Créer des contraintes spécifiques pour le bouton
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = 1;  // Colonne
		gbc.gridy = 2;  // Ligne
		gbc.gridwidth = 1;  // Largeur sur une colonne
		gbc.gridheight = 1;  // Hauteur sur une ligne
		gbc.anchor = GridBagConstraints.CENTER;  // Centre le bouton
		gbc.fill = GridBagConstraints.HORIZONTAL;  // Le bouton s'étend horizontalement
		gbc.weightx = 1.0;  // Permet au bouton de s'étendre horizontalement en fonction de l'espace disponible
		gbc.insets = new Insets(10, 10, 10, 10);  // Marges autour du bouton

		add(saveAllButton, gbc);  // Ajout du bouton avec les nouvelles contraintes

		saveAllButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				saveAllFingerprints();
			}
		});
		//gridBagUtils.addToGridBagLayout(1, 2, this, saveAllButton);
	}
	private void saveAllFingerprints() {}
	// ==============================================
	// Public methods
	// ==============================================
////////////////////////////Ajout de boutton EnregistrerTout/////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
	public NFingerView getView(NFPosition position) {
		if (position == NFPosition.PLAIN_LEFT_FOUR_FINGERS) {
			return nfvLeftFour;
		} else if (position == NFPosition.PLAIN_RIGHT_FOUR_FINGERS) {
			return nfvRightFour;
		} else if (position == NFPosition.PLAIN_THUMBS) {
			return nfvThumbs;
		} else {
			return null;
		}
	}

}
