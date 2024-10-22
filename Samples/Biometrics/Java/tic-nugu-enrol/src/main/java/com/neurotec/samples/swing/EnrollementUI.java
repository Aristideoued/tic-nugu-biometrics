/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.neurotec.samples.swing;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

/**
 *
 * @author hp ZINA
 */
public class EnrollementUI extends JFrame{
    
    private JTextField matriculeField;
    private JTextField cnibField;
    private JTextField nomField;
    private JTextField nomJeuneFilleField;
    private JTextField prenomField;
    private JTextField dateNaissanceField;
    private JTextField lieuNaissanceField;
    private JComboBox<String> sexeComboBox;
    private JTextField telephoneField;
    private JTextField emailField;

    public EnrollementUI() {
        setTitle("Formulaire d'inscription");
        setSize(800, 500); // Augmenter la taille de la fenêtre si nécessaire
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Utilisation de GridBagLayout pour disposer correctement les labels et champs
        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.anchor = GridBagConstraints.WEST;

        // Ajuster la taille des champs de texte en utilisant setColumns()
        Dimension fieldDimension = new Dimension(300, 25);

        gbc.gridx = 0;
        gbc.gridy = 0;
        panel.add(new JLabel("Matricule:"), gbc);
        gbc.gridx = 1;
        matriculeField = new JTextField(20);  // Définit 20 colonnes de texte visible
        matriculeField.setPreferredSize(fieldDimension);
        panel.add(matriculeField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        panel.add(new JLabel("CNIB:"), gbc);
        gbc.gridx = 1;
        cnibField = new JTextField(20);  // Définit 20 colonnes de texte visible
        cnibField.setPreferredSize(fieldDimension);
        panel.add(cnibField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        panel.add(new JLabel("Nom:"), gbc);
        gbc.gridx = 1;
        nomField = new JTextField(25);  // Définit 25 colonnes de texte visible
        nomField.setPreferredSize(fieldDimension);
        panel.add(nomField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        panel.add(new JLabel("Nom de jeune fille:"), gbc);
        gbc.gridx = 1;
        nomJeuneFilleField = new JTextField(25);  // Définit 25 colonnes de texte visible
        nomJeuneFilleField.setPreferredSize(fieldDimension);
        panel.add(nomJeuneFilleField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        panel.add(new JLabel("Prénom:"), gbc);
        gbc.gridx = 1;
        prenomField = new JTextField(25);  // Définit 25 colonnes de texte visible
        prenomField.setPreferredSize(fieldDimension);
        panel.add(prenomField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 5;
        panel.add(new JLabel("Date de naissance:"), gbc);
        gbc.gridx = 1;
        dateNaissanceField = new JTextField(15);  // Définit 15 colonnes de texte visible
        dateNaissanceField.setPreferredSize(fieldDimension);
        panel.add(dateNaissanceField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 6;
        panel.add(new JLabel("Lieu de naissance:"), gbc);
        gbc.gridx = 1;
        lieuNaissanceField = new JTextField(20);  // Définit 20 colonnes de texte visible
        lieuNaissanceField.setPreferredSize(fieldDimension);
        panel.add(lieuNaissanceField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 7;
        panel.add(new JLabel("Sexe:"), gbc);
        gbc.gridx = 1;
        String[] sexeOptions = {"Homme", "Femme"};
        sexeComboBox = new JComboBox<>(sexeOptions);
        panel.add(sexeComboBox, gbc);

        gbc.gridx = 0;
        gbc.gridy = 8;
        panel.add(new JLabel("Téléphone:"), gbc);
        gbc.gridx = 1;
        telephoneField = new JTextField(15);  // Définit 15 colonnes de texte visible
        telephoneField.setPreferredSize(fieldDimension);
        panel.add(telephoneField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 9;
        panel.add(new JLabel("Email:"), gbc);
        gbc.gridx = 1;
        emailField = new JTextField(30);  // Définit 30 colonnes de texte visible
        emailField.setPreferredSize(fieldDimension);
        panel.add(emailField, gbc);

        // Ajouter les boutons "Suivant" et "Annuler"
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        JButton suivantButton = new JButton("Suivant");
        JButton annulerButton = new JButton("Annuler");
        buttonPanel.add(suivantButton);
        buttonPanel.add(annulerButton);

        // Listener pour bouton "Suivant"
        suivantButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                insertIntoDatabase();
            }
        });

        // Listener pour bouton "Annuler"
        annulerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose(); // Ferme la fenêtre actuelle
            }
        });

        // Ajouter le panel des boutons en bas
        add(panel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);

        // Centrer la fenêtre
        setLocationRelativeTo(null);
        setVisible(true);
    }

    // Méthode pour insérer les données dans la base PostgreSQL
    private void insertIntoDatabase() {
        String matricule = matriculeField.getText();
        String cnib = cnibField.getText();
        String nom = nomField.getText();
        String nomJeuneFille = nomJeuneFilleField.getText();
        String prenom = prenomField.getText();
        String dateNaissance = dateNaissanceField.getText();
        String lieuNaissance = lieuNaissanceField.getText();
        String sexe = (String) sexeComboBox.getSelectedItem();
        String telephone = telephoneField.getText();
        String email = emailField.getText();

        // Connexion à la base de données PostgreSQL
       /* try (Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/your_database", "your_username", "your_password")) {
            String sql = "INSERT INTO etudiants (matricule, cnib, nom, nom_jeune_fille, prenom, date_naissance, lieu_naissance, sexe, telephone, email) " +
                    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, matricule);
            pstmt.setString(2, cnib);
            pstmt.setString(3, nom);
            pstmt.setString(4, nomJeuneFille);
            pstmt.setString(5, prenom);
            pstmt.setString(6, dateNaissance);
            pstmt.setString(7, lieuNaissance);
            pstmt.setString(8, sexe);
            pstmt.setString(9, telephone);
            pstmt.setString(10, email);

            pstmt.executeUpdate();
            JOptionPane.showMessageDialog(this, "Les informations ont été enregistrées avec succès !");
        } catch (SQLException ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(this, "Erreur lors de l'insertion des données : " + ex.getMessage());
        }*/
       dispose();
       new CaptureUI().setVisible(true);
}
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new EnrollementUI());
    }
}
