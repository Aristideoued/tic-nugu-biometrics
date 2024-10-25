package com.neurotec.samples.swing;

import javax.swing.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Exemple extends JFrame {


    private JTextField matriculeField;
    private JPasswordField passwordField;
    private JLabel imageLabel;
    //private Authentification auth ;

    public Exemple() {
        setTitle("Login");
        setSize(500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Créer le panneau principal
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BorderLayout());
        mainPanel.setBackground(new Color(255, 255, 255)); // Couleur de fond douce

        // Ajouter une image en haut
        imageLabel = new JLabel(new ImageIcon("logo.PNG"), JLabel.CENTER);
        mainPanel.add(imageLabel, BorderLayout.NORTH);

        // Créer le panel pour le formulaire de connexion
        JPanel formPanel = new JPanel();
        formPanel.setLayout(new GridBagLayout());
        formPanel.setBackground(new Color(255, 255, 255)); // Fond blanc pour le formulaire
        formPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20)); // Marges autour du formulaire

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10); // Marges pour les composants

        // Ajouter les champs de saisie
        gbc.gridx = 0;
        gbc.gridy = 0;
        formPanel.add(new JLabel("Matricule:"), gbc);

        matriculeField = new JTextField(15);
        gbc.gridx = 1;
        formPanel.add(matriculeField, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        formPanel.add(new JLabel("Mot de passe:"), gbc);

        passwordField = new JPasswordField(15);
        gbc.gridx = 1;
        formPanel.add(passwordField, gbc);

        // Bouton de connexion
        JButton loginButton = new JButton("Se connecter");
        loginButton.setBackground(new Color(100, 149, 237)); // Couleur bleu clair
        loginButton.setForeground(Color.BLUE);
        loginButton.setBorder(BorderFactory.createRaisedBevelBorder());
        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 2; // Le bouton s'étend sur deux colonnes
        formPanel.add(loginButton, gbc);

        // Ajouter le formulaire au panneau principal
        mainPanel.add(formPanel, BorderLayout.CENTER);

        // Action du bouton de connexion
        //auth = new Authentification();
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String matricule = matriculeField.getText();
                String password = new String(passwordField.getPassword());

                // Ici, ajoutez la vérification de l'authentification
                if (true) {
                    //auth.authenticateUser(matricule, password)
                    //JOptionPane.showMessageDialog(null, "Connexion réussie !");
                    new PrincipalUI();
                    dispose(); // Ferme la fenêtre de connexion
                } else {
                    JOptionPane.showMessageDialog(null, "Matricule ou mot de passe incorrect.");
                }
            }
        });

        // Ajouter le panneau principal à la fenêtre
        add(mainPanel);
    }

}
