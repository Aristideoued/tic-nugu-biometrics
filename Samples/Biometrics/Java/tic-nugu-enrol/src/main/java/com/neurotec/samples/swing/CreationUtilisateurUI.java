package com.neurotec.samples.swing;
import com.neurotec.samples.DAO.ProfilDao;
import com.neurotec.samples.DAO.UtilisateurDAO;
import com.neurotec.samples.config.ChainCon;
import com.neurotec.samples.model.Compte;
import com.neurotec.samples.model.Profil;
import com.neurotec.samples.model.Utilisateur;
import com.neurotec.samples.swing.PrincipalUI;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.List;

public class CreationUtilisateurUI extends JFrame {

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
    public CreationUtilisateurUI() {
        // Initialiser les labels d'erreur
        telephoneErrorLabel = new JLabel();
        telephoneErrorLabel.setForeground(Color.RED); // Couleur du texte en rouge
        telephoneErrorLabel.setVisible(false); // Cacher par défaut

        emailErrorLabel = new JLabel();
        emailErrorLabel.setForeground(Color.RED); // Couleur du texte en rouge
        emailErrorLabel.setVisible(false); // Cacher par défaut
        setTitle("Création d'utilisateur");
        setSize(400, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Créer le panel principal
        JPanel panel = new JPanel();
        panel.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10); // Marges

        // Couleur de fond
       // panel.setBackground(new Color(44, 44, 73)); // Une couleur lavande claire

        // Champs pour Profil
        gbc.gridx = 0;
        gbc.gridy = 0;
        panel.add(new JLabel("Profil:"), gbc);

        profilComboBox = new JComboBox<>();
        gbc.gridx = 1;
        panel.add(profilComboBox, gbc);

        // Champs pour Compte
        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Nom d'utilisateur:"), gbc);

        usernameField = new JTextField(15);
        gbc.gridx = 1;
        panel.add(usernameField, gbc);

        // Champs pour Utilisateur
        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Matricule:"), gbc);

        matriculeField = new JTextField(15);
        gbc.gridx = 1;
        panel.add(matriculeField, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Nom:"), gbc);

        nomField = new JTextField(15);
        gbc.gridx = 1;
        panel.add(nomField, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Prénom:"), gbc);

        prenomField = new JTextField(15);
        gbc.gridx = 1;
        panel.add(prenomField, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Téléphone:"), gbc);

        telephoneField = new JTextField(15);
        gbc.gridx = 1;
        panel.add(telephoneField, gbc);

        // Ajouter le label d'erreur pour le téléphone
        gbc.gridx = 1;
        gbc.gridy++;
        panel.add(telephoneErrorLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Email:"), gbc);

        emailField = new JTextField(15);
        gbc.gridx = 1;
        panel.add(emailField, gbc);
        // Ajouter le label d'erreur pour l'email
        gbc.gridx = 1;
        gbc.gridy++;
        panel.add(emailErrorLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy++;
        panel.add(new JLabel("Mot de passe:"), gbc);

        passwordField = new JPasswordField(15); // Utilisation d'un JPasswordField
        gbc.gridx = 1;
        panel.add(passwordField, gbc);

        // Bouton de création
        JButton createButton = new JButton("Créer Utilisateur");
        JButton cancelButton = new JButton("Annuler");
        createButton.setBackground(new Color(166, 237, 100)); // Couleur bleu clair
        createButton.setForeground(Color.WHITE);
        createButton.setBorder(BorderFactory.createRaisedBevelBorder());

        cancelButton.setBackground(new Color(237, 100, 121)); // Couleur bleu clair
        cancelButton.setForeground(Color.WHITE);
        cancelButton.setBorder(BorderFactory.createRaisedBevelBorder());

        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 1; // Le bouton s'étend sur 1 colonne
        panel.add(createButton, gbc);

        gbc.gridx = 1; // Passer à la colonne suivante
        panel.add(cancelButton, gbc);
        gbc.gridwidth = 2; // Par défaut pour les futurs composants
        // Action du bouton

        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose(); // Ferme la fenêtre de connexion
            }
        });
        createButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            
                new PrincipalUI().setVisible(true);
                dispose();

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

                // Validation des champs
                /*boolean valid = true;

                if (!validateTelephone(telephone)) {
                    telephoneErrorLabel.setText("Le numéro de téléphone doit contenir 8 chiffres.");
                    telephoneErrorLabel.setVisible(true); // Afficher le message d'erreur
                    valid = false; // Indiquer que la validation a échoué
                }

                if (!validateEmail(email)) {
                    emailErrorLabel.setText("L'adresse email n'est pas valide.");
                    emailErrorLabel.setVisible(true); // Afficher le message d'erreur
                    valid = false; // Indiquer que la validation a échoué
                }

                if (!valid) {
                    return; // Sortir si la validation échoue
                }
*/
                Connection conn = null;
                try {
                    conn = ChainCon.getConnection();
                    // Désactiver l'auto-commit pour gérer la transaction manuellement
                    conn.setAutoCommit(false);

                    // Étape 1 : Enregistrer l'utilisateur dans la base de données
                    Utilisateur utilisateur = new Utilisateur(matricule, nom, prenom, telephone, email);
                    UtilisateurDAO utilisateurDao = new UtilisateurDAO();
                    long utilisateurId = utilisateurDao.save(conn, utilisateur); // Passer la connexion

                    if (utilisateurId > 0) {
                        // Étape 2 : Récupérer l'ID du profil sélectionné
                        ProfilDao profilDao = new ProfilDao();
                        long profilId = profilDao.getProfilIdByLibelle(libelle);

                        // Étape 3 : Créer un compte pour l'utilisateur
                        Profil profil = new Profil();
                        profil.setId(profilId);

                        Utilisateur utilisateurRef = new Utilisateur();
                        utilisateurRef.setId(utilisateurId);

                        Compte compte = new Compte();
                        compte.setProfil(profil);  // Lien entre Compte et Profil
                        compte.setUtilisateur(utilisateurRef);  // Lien entre Compte et Utilisateur
                        compte.setUsername(username);
                        compte.setPassword(password);
                        compte.setCreateBy("Francis");
                        compte.setCreateAt(Timestamp.valueOf(LocalDateTime.now()));
                        compte.setFlActivated(true);

                        // Étape 4 : Sauvegarder le compte
                   //*************     CompteDAO compteDao = new CompteDAO();
                    //************    compteDao.save(conn, compte); // Passer la connexion

                        // Valider la transaction si tout est OK
                        conn.commit();

                        JOptionPane.showMessageDialog(null, "Utilisateur et compte créés avec succès !");
                    } else {
                        JOptionPane.showMessageDialog(null, "Erreur lors de la création de l'utilisateur.");
                        conn.rollback(); // Annuler la transaction si l'utilisateur n'a pas pu être enregistré
                    }

                } catch (SQLException ex) {
                    ex.printStackTrace();
                    try {
                        if (conn != null) {
                            conn.rollback();
                        }
                    } catch (SQLException rollbackEx) {
                        rollbackEx.printStackTrace();
                    }
                } finally {
                    if (conn != null) {
                        try {
                            conn.setAutoCommit(true); // Remettre l'auto-commit par défaut
                            conn.close(); // Fermer la connexion
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                    }
                }
            }

        });

        // Remplir le JComboBox avec les profils
        loadProfils();

        // Ajouter le panel à la fenêtre
        add(panel);
    }

    private void loadProfils() {
        ProfilDao profilDAO = new ProfilDao();
        List<String> profils = profilDAO.getAllProfils();

        for (String profil : profils) {
            profilComboBox.addItem(profil);
        }
    }

    // Méthode de validation du téléphone
    private boolean validateTelephone(String telephone) {
        return telephone.matches("\\d{8}"); // Vérifie si le téléphone contient exactement 8 chiffres
    }

    // Méthode de validation de l'email
    private boolean validateEmail(String email) {
        String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@[a-zA-Z0-9-]+(?:\\.[a-zA-Z0-9-]+)*$";
        return email.matches(emailRegex); // Vérifie si l'email a un format valide
    }

    // Méthode pour afficher un message d'erreur en rouge


    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            CreationUtilisateurUI creationUtilisateurUI = new CreationUtilisateurUI();
            creationUtilisateurUI.setVisible(true);
        });
    }
}
