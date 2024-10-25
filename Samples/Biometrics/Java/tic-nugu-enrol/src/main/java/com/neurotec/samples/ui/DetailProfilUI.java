package com.neurotec.samples.ui;


import lombok.Data;
import org.springframework.stereotype.Component;

import javax.swing.*;
import java.awt.*;

@Data
@Component
public class DetailProfilUI extends JFrame {
    private JLabel usernameLabel;
    private JLabel profilLabel;
    private JLabel matriculeLabel;
    private JLabel nomLabel;
    private JLabel prenomLabel;
    private JLabel telephoneLabel;
    private JLabel emailLabel;
    private JButton closeButton;

    public DetailProfilUI() {
        initUI();
    }

    public void initUI() {
        setTitle("Détail du Profil Utilisateur");
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        // Créer le panel principal
        JPanel panel = new JPanel();
        panel.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10); // Marges

        // Champs pour afficher les informations utilisateur
        gbc.gridx = 0;
        gbc.gridy = 0;
        panel.add(new JLabel("Nom d'utilisateur:"), gbc);
        usernameLabel = new JLabel();
        gbc.gridx = 1;
        panel.add(usernameLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Profil:"), gbc);
        profilLabel = new JLabel();
        gbc.gridx = 1;
        panel.add(profilLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Matricule:"), gbc);
        matriculeLabel = new JLabel();
        gbc.gridx = 1;
        panel.add(matriculeLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Nom:"), gbc);
        nomLabel = new JLabel();
        gbc.gridx = 1;
        panel.add(nomLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Prénom:"), gbc);
        prenomLabel = new JLabel();
        gbc.gridx = 1;
        panel.add(prenomLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Téléphone:"), gbc);
        telephoneLabel = new JLabel();
        gbc.gridx = 1;
        panel.add(telephoneLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Email:"), gbc);
        emailLabel = new JLabel();
        gbc.gridx = 1;
        panel.add(emailLabel, gbc);

        // Bouton de fermeture
        closeButton = new JButton("Fermer");
        closeButton.addActionListener(e -> dispose()); // Fermer la fenêtre

        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 2;
        panel.add(closeButton, gbc);

        add(panel);
    }

}
