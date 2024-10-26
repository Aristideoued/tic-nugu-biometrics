package com.neurotec.samples.controller;


import com.neurotec.samples.Services.CompteService;
import com.neurotec.samples.Services.ProfilService;
import com.neurotec.samples.Services.UtilisateurService;
import com.neurotec.samples.model.Compte;
import com.neurotec.samples.model.Profil;
import com.neurotec.samples.model.Utilisateur;
import com.neurotec.samples.ui.*;
import com.neurotec.samples.utils.SessionManager;
import com.neurotec.samples.utils.ValidateFieldForm;
import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;

import javax.annotation.PostConstruct;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableRowSorter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import java.time.Instant;
import java.util.List;

@Controller
@AllArgsConstructor
public class UtilisateurController {

    private final UtilisateurService utilisateurService;
    private final CreerUserUI creerUserUI;
    private final CompteService compteService;
    private ProfilService profilService;
    private ChangePasswordUI changePasswordUI;
    private DetailProfilUI detailProfilUI;
    private PrincipalUI principalUI;
    private SessionManager sessionManager;
    private ConsultUserUI consultUserUI;

    public Compte creerUser(Compte compte){
        System.out.println("creer user:"+compte);
        compteService.create(compte);
       // utilisateurService.create(utilisateur);
        return compte;
    }


    @PostConstruct
    public void prepareAndOpenFrame(){
        //creerUserUI.setVisible(true);
        creerUserUI.getCreateButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                creerUtilisateur();
            }
        });

        creerUserUI.getCancelButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
//                creerUserUI.dispose();
            }
        });

        changePasswordUI.getChangeButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                changerMotDePasse();
            }
        });

        principalUI.getMonprofil().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                loadUserDetails();
            }
        });
    }

    public List<Compte> loadAll(){
        List<Compte> compteAll=compteService.findAllCompte();
       return compteAll;
    }
    public void loadProfils() {
        List<Profil> profils = profilService.findProfils();
        if (profils != null && !profils.isEmpty()) {
            creerUserUI.getProfilComboBox().addItem("Selectionner un profil");
            for (Profil profil : profils) {
                creerUserUI.getProfilComboBox().addItem(profil.getLibelle());
            }
        } else {
            System.out.println("Aucun profil disponible !");
        }
    }

    private void creerUtilisateur() {
        // Récupérer les valeurs des champs
        String libelle = (String) creerUserUI.getProfilComboBox().getSelectedItem();
        String username = creerUserUI.getUsernameField().getText();
        String matricule = creerUserUI.getMatriculeField().getText();
        String nom = creerUserUI.getNomField().getText();
        String prenom = creerUserUI.getPrenomField().getText();
        String telephone = creerUserUI.getTelephoneField().getText();
        String email = creerUserUI.getEmailField().getText();
        String password = new String(creerUserUI.getPasswordField().getPassword()); // Récupérer le mot de passe
        // Réinitialiser les messages d'erreur
        creerUserUI.getTelephoneErrorLabel().setText("");
        creerUserUI.getEmailErrorLabel().setText("");
        creerUserUI.getTelephoneErrorLabel().setVisible(false);
        creerUserUI.getEmailErrorLabel().setVisible(false);
        // Validation des champs
        boolean valid = true;

        if (!ValidateFieldForm.validateTelephone(telephone)) {
            creerUserUI.getTelephoneErrorLabel().setText("Le numéro de téléphone doit contenir 8 chiffres.");
            creerUserUI.getTelephoneErrorLabel().setVisible(true); // Afficher le message d'erreur
            valid = false; // Indiquer que la validation a échoué
        }

        if (libelle=="Selectionner un profil") {
            JOptionPane.showMessageDialog(creerUserUI, "Veuillez selectionner un profil pour l'utilisateur.", "Erreur de saisie", JOptionPane.ERROR_MESSAGE);
            valid = false; // Indiquer que la validation a échoué
        }
        else if(!ValidateFieldForm.validatePassword(password)) {
            if (ValidateFieldForm.validateEmail(email))
                JOptionPane.showMessageDialog(creerUserUI, "Le mot de passe doit contenir 8 caractères avec moins une lettre, un chiffre et un caractère spécial", "Erreur de saisie", JOptionPane.ERROR_MESSAGE);
            valid = false;
        }

        if (!ValidateFieldForm.validateUsername(username)) {
            creerUserUI.getUsernameErrorLabel().setText("Le nom d'utilisateur est requis");
            creerUserUI.getUsernameErrorLabel().setVisible(true);
            valid = false;
        }

        if (!ValidateFieldForm.validateNom(nom)) {
            creerUserUI.getNomErrorLabel().setText("Le nom de famille est obligatoire");
            creerUserUI.getNomErrorLabel().setVisible(true);
            valid = false;
        }

        if (!ValidateFieldForm.validatePrenom(nom)) {
            creerUserUI.getPrenomErrorLabel().setText("Le nom de famille est obligatoire");
            creerUserUI.getPrenomErrorLabel().setVisible(true);
            valid = false;
        }

        if (!ValidateFieldForm.validateEmail(email)) {
            creerUserUI.getEmailErrorLabel().setText("L'adresse email n'est pas valide.");
            creerUserUI.getEmailErrorLabel().setVisible(true); // Afficher le message d'erreur
            valid = false; // Indiquer que la validation a échoué
        }

        if (!ValidateFieldForm.validateMatricule(matricule)) {
            creerUserUI.getMatriculeErrorLabel().setText("Le matricule doit contenir au moins 5 caractèree");
            creerUserUI.getMatriculeErrorLabel().setVisible(true); // Afficher le message d'erreur
            valid = false; // Indiquer que la validation a échoué
        }

        if (!valid) {
            return; // Sortir si la validation échoue
        }
        Utilisateur utilisateur = new Utilisateur();
        utilisateur.setEmail(email);
        utilisateur.setMatricule(matricule);
        utilisateur.setNom(nom);
        utilisateur.setPrenom(prenom);
        utilisateur.setTelephone(telephone);
        utilisateur.setCreatedBy("Francis");

        Profil profil= profilService.getProfilByLibelle(libelle);

        Compte compte = new Compte();
        compte.setProfil(profil);  // Lien entre Compte et Profil
        compte.setUtilisateur(utilisateur);  // Lien entre Compte et Utilisateur
        compte.setUsername(username);
        compte.setPassword(password);
        compte.setCreatedBy("Francis");
        compte.setCreatedDate(Instant.now());
        compte.setFlActivated(true);
        System.out.println("User:"+ utilisateur);

        /// utilisateurController.creerUser(compte);
         creerUser(compte);
        JOptionPane.showMessageDialog(null, "Utilisateur et compte créés avec succès !");
        consultUserUI.refreshTable();
        consultUserUI.setVisible(true);

    }


    private void changerMotDePasse() {

        String currentPassword = new String(changePasswordUI.getPasswordField().getText());
        String newPassword = new String(changePasswordUI.getNewPasswordField().getText());
        Long compteId = sessionManager.getUtilisateurCourant().getId();
        boolean isPasswordChanged = compteService.changePassword(compteId, currentPassword, newPassword);
        if (isPasswordChanged) {
            JOptionPane.showMessageDialog(null, "Mot de passe changé avec succès !");
            //mainController.getPrincipalUI().principal();
            changePasswordUI.dispose(); // Close login window

        } else {
            JOptionPane.showMessageDialog(changePasswordUI, "les mots de passe saisis sont incorrect.", "Erreur", JOptionPane.ERROR_MESSAGE);
        }

    }

    // Méthode pour charger les détails d'un utilisateur dans l'interface
    public void loadUserDetails() {
        Compte compte = sessionManager.getUtilisateurCourant();
        if (compte != null) {
            Utilisateur utilisateur = compte.getUtilisateur();
            Profil profil = compte.getProfil();

            detailProfilUI.getUsernameLabel().setText(compte.getUsername());
            detailProfilUI.getProfilLabel().setText(profil != null ? profil.getLibelle() : "Aucun profil");
            detailProfilUI.getMatriculeLabel().setText(utilisateur.getMatricule());
            detailProfilUI.getNomLabel().setText(utilisateur.getNom());
            detailProfilUI.getPrenomLabel().setText(utilisateur.getPrenom());
            detailProfilUI.getTelephoneLabel().setText(utilisateur.getTelephone());
            detailProfilUI.getEmailLabel().setText(utilisateur.getEmail());
        } else {
            JOptionPane.showMessageDialog(principalUI, "Utilisateur non trouvé !");
        }


    }

    private void deleteFromDatabase(Long compteId) {

        //suppression dans la table compte
       // Long compteId2=(Long)compteId ;
            compteService.delete(compteId);
       //suppression dans la table utilisateur
      }

}
