package com.neurotec.samples.swing.controls;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import com.neurotec.biometrics.NFPosition;
import com.neurotec.biometrics.swing.NFingerView;
import com.neurotec.samples.swing.GridBagUtils;


/*
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

	}

	// ==============================================
	// Public methods
	// ==============================================

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
*/

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
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
        slapsPanelLayout.rowHeights = new int[] { 20, 365, 50 }; // Added row for the button
        setLayout(slapsPanelLayout);

        // View for left four fingers
        nfvLeftFour = new NFingerView();
        nfvLeftFour.setAutofit(true);
        JPanel leftPanel = new JPanel(new BorderLayout());
        leftPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        leftPanel.add(nfvLeftFour, BorderLayout.CENTER);
        leftPanel.setPreferredSize(leftPanel.getPreferredSize());
        JScrollPane leftScrollPane = new JScrollPane(leftPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

        // View for thumbs
        nfvThumbs = new NFingerView();
        nfvThumbs.setAutofit(true);
        JPanel thumbsPanel = new JPanel(new BorderLayout());
        thumbsPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        thumbsPanel.add(nfvThumbs, BorderLayout.CENTER);
        thumbsPanel.setPreferredSize(thumbsPanel.getPreferredSize());
        JScrollPane thumbScrollPane = new JScrollPane(thumbsPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

        // View for right four fingers
        nfvRightFour = new NFingerView();
        nfvRightFour.setAutofit(true);
        JPanel rightPanel = new JPanel(new BorderLayout());
        rightPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        rightPanel.add(nfvRightFour, BorderLayout.CENTER);
        rightPanel.setPreferredSize(rightPanel.getPreferredSize());
        JScrollPane rightScrollPane = new JScrollPane(rightPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

        GridBagUtils gridBagUtils = new GridBagUtils(GridBagConstraints.BOTH);
        gridBagUtils.setInsets(new Insets(1, 1, 1, 1));

        // Adding the labels
        gridBagUtils.addToGridBagLayout(0, 0, 1, 1, 0.3, 0, this, new JLabel("Quatre doigts de la main gauche"));
        gridBagUtils.addToGridBagLayout(1, 0, this, new JLabel("Pouces"));
        gridBagUtils.addToGridBagLayout(2, 0, this, new JLabel("Quatre doigts de la main droite"));

        // Adding the NFingerView components (views)
        gridBagUtils.addToGridBagLayout(0, 1, 1, 1, 0.3, 1, this, leftScrollPane);
        gridBagUtils.addToGridBagLayout(1, 1, this, thumbScrollPane);
        gridBagUtils.addToGridBagLayout(2, 1, this, rightScrollPane);

        // Adding the single button to save all fingerprints
        JButton btnSaveAll = new JButton("Enregistrer toutes les empreintes");
        btnSaveAll.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                saveAllFingerprints();
            }
        });

        // Adding the button to the layout
        gridBagUtils.addToGridBagLayout(1, 2, this, btnSaveAll); // Positioned in the center
    }

    // ==============================================
    // Public methods
    // ==============================================

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

    // Save all fingerprints (left hand, thumbs, right hand)
    private void saveAllFingerprints() {
        // Save left four fingers
        saveFingerprints(nfvLeftFour, "Main Gauche");
        // Save thumbs
        saveFingerprints(nfvThumbs, "Pouces");
        // Save right four fingers
        saveFingerprints(nfvRightFour, "Main Droite");
    }

    // Method to save fingerprints from a specific view
    private void saveFingerprints(NFingerView view, String handName) {
        if (view.getFinger() != null) {
            // Here, implement the logic to save the fingerprint data
            System.out.println("Enregistrement des empreintes pour : " + handName);
            // Example: byte[] fingerprintData = view.getFinger().getImage().save();
            // Save fingerprintData to the desired location
        } else {
            System.out.println("Aucune empreinte à enregistrer pour : " + handName);
        }
    }

}
