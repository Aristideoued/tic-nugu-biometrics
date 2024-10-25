package com.neurotec.samples.ui;

import javax.swing.*;
import java.awt.*;

public class Formulaire extends JFrame {

    public Formulaire() {
        setTitle("Formulaire de saisie");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Utiliser GridBagLayout pour une disposition flexible
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5); // Marges entre les composants
        gbc.fill = GridBagConstraints.HORIZONTAL;

        // Ajout des étiquettes et des champs
        gbc.gridx = 0; gbc.gridy = 0;
        add(new JLabel("Nom:"), gbc);

        gbc.gridx = 1; gbc.gridy = 0;
        JTextField nomField = new JTextField(15);
        add(nomField, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        add(new JLabel("Prénom:"), gbc);

        gbc.gridx = 1; gbc.gridy = 1;
        JTextField prenomField = new JTextField(15);
        add(prenomField, gbc);

        gbc.gridx = 0; gbc.gridy = 2;
        add(new JLabel("Email:"), gbc);

        gbc.gridx = 1; gbc.gridy = 2;
        JTextField emailField = new JTextField(15);
        add(emailField, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        add(new JLabel("Téléphone:"), gbc);

        gbc.gridx = 1; gbc.gridy = 3;
        JTextField telephoneField = new JTextField(15);
        add(telephoneField, gbc);

        // Bouton de soumission
        gbc.gridx = 0; gbc.gridy = 4; gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        JButton submitButton = new JButton("Soumettre");
        add(submitButton, gbc);

        // Affichage de la fenêtre
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Formulaire());
    }
}
