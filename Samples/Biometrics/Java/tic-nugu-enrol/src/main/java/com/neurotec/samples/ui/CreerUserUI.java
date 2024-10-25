package com.neurotec.samples.ui;


import com.neurotec.samples.model.Compte;
import com.neurotec.samples.model.Profil;
import com.neurotec.samples.model.Utilisateur;
import lombok.Data;
import org.springframework.stereotype.Component;

import javax.swing.*;
import java.awt.*;
import java.time.Instant;

@Data
@Component
public class CreerUserUI extends JPanel {
    //uuuu
    private JComboBox<String> profilComboBox;
    private JTextField usernameField;
    private JPasswordField passwordField; // Utilisation de JPasswordField pour les mots de passe
    private JTextField matriculeField;
    private JTextField nomField;
    private JTextField prenomField;
    private JTextField telephoneField;
    private JTextField emailField;
    private JLabel telephoneErrorLabel; // Pour afficher l'erreur de téléphone
    private JLabel emailErrorLabel; // Pour afficher l'erreur d'email
    private JLabel matriculeErrorLabel; // Pour afficher l'erreur de téléphone
    private JLabel usernameErrorLabel; // Pour afficher l'erreur d'email
    private JLabel nomErrorLabel; // Pour afficher l'erreur de téléphone
    private JLabel prenomErrorLabel; // Pour afficher l'erreur d'email
    private JButton createButton = new JButton("Créer Utilisateur");
    private JButton cancelButton = new JButton("Annuler");
    ////private UtilisateurController utilisateurController;
    //private ProfilService profilService;

//    @PostConstruct
    public CreerUserUI() {
        // Initialiser les labels d'erreur
        telephoneErrorLabel = new JLabel("");
        telephoneErrorLabel.setForeground(Color.RED); // Couleur du texte en rouge
        telephoneErrorLabel.setVisible(false); // Cacher par défaut

        emailErrorLabel = new JLabel("");
        emailErrorLabel.setForeground(Color.RED); // Couleur du texte en rouge
        emailErrorLabel.setVisible(false); // Cacher par défaut

        matriculeErrorLabel = new JLabel("");
        matriculeErrorLabel.setForeground(Color.RED);
        matriculeErrorLabel.setVisible(false);

        usernameErrorLabel = new JLabel("");
        usernameErrorLabel.setForeground(Color.RED);
        usernameErrorLabel.setVisible(false);

        nomErrorLabel = new JLabel("");
        nomErrorLabel.setForeground(Color.RED);
        nomErrorLabel.setVisible(false);

        prenomErrorLabel = new JLabel("");
        prenomErrorLabel.setForeground(Color.RED);
        prenomErrorLabel.setVisible(false);

        // Créer le this principal
//        Jthis this = new Jthis();
        this.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10); // Marges

        // Couleur de fond
        // this.setBackground(new Color(44, 44, 73)); // Une couleur lavande claire

        // Champs pour Profil
        gbc.gridx = 0;
        gbc.gridy = 0;
        this.add(new JLabel("Profil:"), gbc);

        profilComboBox = new JComboBox<>();
        gbc.gridx = 1;
        this.add(profilComboBox, gbc);

        // Champs pour Compte
        gbc.gridx = 0;
        gbc.gridy++;
        this.add(new JLabel("Nom d'utilisateur:"), gbc);

        usernameField = new JTextField(15);
        gbc.gridx = 1;
        this.add(usernameField, gbc);
        gbc.gridx = 1;
        gbc.gridy++;
        this.add(usernameErrorLabel, gbc);

        // Champs pour Utilisateur
        gbc.gridx = 0;
        gbc.gridy++;
        this.add(new JLabel("Matricule:"), gbc);

        matriculeField = new JTextField(15);
        gbc.gridx = 1;
        this.add(matriculeField, gbc);
        gbc.gridx = 1;
        gbc.gridy++;
        add(matriculeErrorLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        add(new JLabel("Nom:"), gbc);

        nomField = new JTextField(15);
        gbc.gridx = 1;
        this.add(nomField, gbc);
        gbc.gridx = 1;
        gbc.gridy++;
        this.add(nomErrorLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        this.add(new JLabel("Prénom:"), gbc);

        prenomField = new JTextField(15);
        gbc.gridx = 1;
        this.add(prenomField, gbc);
        gbc.gridx = 1;
        gbc.gridy++;
        this.add(prenomErrorLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        this.add(new JLabel("Téléphone:"), gbc);

        telephoneField = new JTextField(15);
        gbc.gridx = 1;
        this.add(telephoneField, gbc);

        // Ajouter le label d'erreur pour le téléphone
        gbc.gridx = 1;
        gbc.gridy++;
        this.add(telephoneErrorLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        this.add(new JLabel("Email:"), gbc);

        emailField = new JTextField(15);
        gbc.gridx = 1;
        this.add(emailField, gbc);
        // Ajouter le label d'erreur pour l'email
        gbc.gridx = 1;
        gbc.gridy++;
        this.add(emailErrorLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        this.add(new JLabel("Mot de passe:"), gbc);

        passwordField = new JPasswordField(15); // Utilisation d'un JPasswordField
        gbc.gridx = 1;
        this.add(passwordField, gbc);

        // Bouton de création
        // Appliquer les styles au bouton "Primary" (Bootstrap btn-primary)
        createButton.setBackground(new Color(0, 123, 255)); // Couleur bleu Bootstrap
        createButton.setForeground(Color.WHITE); // Texte blanc
        createButton.setFocusPainted(false); // Retirer l'effet de focus
        createButton.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20)); // Bordure interne pour rendre le bouton plus large
        createButton.setOpaque(true);
        createButton.setBorder(BorderFactory.createLineBorder(new Color(0, 105, 217), 2)); // Bordure bleue foncée

        // Appliquer les styles au bouton "Default" (Bootstrap btn-default)
        cancelButton.setBackground(new Color(108, 117, 125)); // Couleur gris Bootstrap
        cancelButton.setForeground(Color.WHITE); // Texte blanc (ou noir si vous préférez)
        cancelButton.setFocusPainted(false);
        cancelButton.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20)); // Même bordure interne
        cancelButton.setOpaque(true);
        cancelButton.setBorder(BorderFactory.createLineBorder(new Color(90, 98, 104), 2)); // Bordure gris foncé

        // Appliquer une taille préférée aux deux boutons pour qu'ils aient la même taille
        Dimension buttonSize = new Dimension(140, 40); // Largeur et hauteur fixes pour les deux boutons
        createButton.setPreferredSize(buttonSize);
        cancelButton.setPreferredSize(buttonSize);

        // Ajouter les boutons à la fenêtre
        //setLayout(new FlowLayout());
       // add(createButton);
       // add(cancelButton);

        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 1; // Le bouton s'étend sur 1 colonne
        this.add(createButton, gbc);

        gbc.gridx = 1; // Passer à la colonne suivante
        this.add(cancelButton, gbc);
        gbc.gridwidth = 2; // Par défaut pour les futurs composants
        // Action du bouton

//        add(this);

    }

    private void creerUtilisateur() {
        // Récupérer les valeurs des champs
        String libelle = (String) profilComboBox.getSelectedItem();
        String username = usernameField.getText();
        String matricule = matriculeField.getText();
        String nom = nomField.getText();
        String prenom = prenomField.getText();
        String telephone = telephoneField.getText();
        String email = emailField.getText();
        String password = new String(passwordField.getPassword()); // Récupérer le mot de passe
        // Réinitialiser les messages d'erreur
        telephoneErrorLabel.setText("");
        emailErrorLabel.setText("");
        telephoneErrorLabel.setVisible(false);
        emailErrorLabel.setVisible(false);
        Utilisateur utilisateur = new Utilisateur();
        utilisateur.setEmail(email);
        utilisateur.setMatricule(matricule);
        utilisateur.setNom(nom);
        utilisateur.setPrenom(prenom);
        utilisateur.setTelephone(telephone);
        utilisateur.setCreatedBy("Francis");


        Profil profil= new Profil();

        profil.setId(1L);
        profil.setLibelle("Operateur");
        Compte compte = new Compte();
        compte.setProfil(profil);  // Lien entre Compte et Profil
        compte.setUtilisateur(utilisateur);  // Lien entre Compte et Utilisateur
        compte.setUsername(username);
        compte.setPassword(password);
        compte.setCreatedBy("Francis");
        compte.setCreatedDate(Instant.now());
        compte.setFlActivated(true);
        System.out.println("User:"+ utilisateur);

       ////// utilisateurController.creerUser(compte);
        JOptionPane.showMessageDialog(null, "Utilisateur et compte créés avec succès !");
//        dispose();

    }

    /*public void loadProfils() {
        List<Profil> profils = profilService.findProfils();
        if (profils != null && !profils.isEmpty()) {
            for (Profil profil : profils) {
                profilComboBox.addItem(profil.getLibelle());
            }
        } else {
            System.out.println("Aucun profil disponible !");
        }
    }*/


}
