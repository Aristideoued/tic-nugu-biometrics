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

        // Création du panneau principal
        JPanel panel = new JPanel();
        panel.setLayout(new GridBagLayout());
        panel.setBackground(Color.WHITE); // Fond blanc pour le panneau principal
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);

        // Style de base pour les étiquettes
        Font labelFont = new Font("Arial", Font.BOLD, 14);
        Font valueFont = new Font("Arial", Font.PLAIN, 14);

        // Création et disposition des champs d'affichage des informations utilisateur
        gbc.gridx = 0;
        gbc.gridy = 0;
        panel.add(createStyledLabel("Nom d'utilisateur:", labelFont), gbc);
        usernameLabel = createStyledValueLabel(valueFont);
        gbc.gridx = 1;
        panel.add(usernameLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(createStyledLabel("Profil:", labelFont), gbc);
        profilLabel = createStyledValueLabel(valueFont);
        gbc.gridx = 1;
        panel.add(profilLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(createStyledLabel("Matricule:", labelFont), gbc);
        matriculeLabel = createStyledValueLabel(valueFont);
        gbc.gridx = 1;
        panel.add(matriculeLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(createStyledLabel("Nom:", labelFont), gbc);
        nomLabel = createStyledValueLabel(valueFont);
        gbc.gridx = 1;
        panel.add(nomLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(createStyledLabel("Prénom:", labelFont), gbc);
        prenomLabel = createStyledValueLabel(valueFont);
        gbc.gridx = 1;
        panel.add(prenomLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(createStyledLabel("Téléphone:", labelFont), gbc);
        telephoneLabel = createStyledValueLabel(valueFont);
        gbc.gridx = 1;
        panel.add(telephoneLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(createStyledLabel("Email:", labelFont), gbc);
        emailLabel = createStyledValueLabel(valueFont);
        gbc.gridx = 1;
        panel.add(emailLabel, gbc);

        // Bouton de fermeture avec style amélioré
        closeButton = new JButton("Fermer");
        closeButton.setBackground(new Color(0, 123, 255)); // Couleur gris Bootstrap
        closeButton.setForeground(Color.WHITE); // Texte blanc (ou noir si vous préférez)
        closeButton.setFocusPainted(false);
        closeButton.setOpaque(true);
        closeButton.setFocusPainted(false);
        closeButton.setBorder(BorderFactory.createEmptyBorder(10, 25, 10, 25));
        closeButton.setFont(new Font("Arial", Font.BOLD, 14));
        closeButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
        closeButton.addActionListener(e -> dispose());

        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        panel.add(closeButton, gbc);

        add(panel);
    }

    private JLabel createStyledLabel(String text, Font font) {
        JLabel label = new JLabel(text);
        label.setFont(font);
        label.setForeground(new Color(0, 123, 255)); // Couleur Bootstrap blue pour le texte des labels
        return label;
    }

    private JLabel createStyledValueLabel(Font font) {
        JLabel label = new JLabel();
        label.setFont(font);
        label.setForeground(Color.DARK_GRAY); // Couleur grise pour les valeurs
        return label;
    }
}
