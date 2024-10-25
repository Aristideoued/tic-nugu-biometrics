package com.neurotec.samples.controller;


import com.neurotec.samples.Services.CompteService;
import com.neurotec.samples.model.Compte;
import com.neurotec.samples.ui.ConnexionUI;
import com.neurotec.samples.ui.PrincipalUI;
import com.neurotec.samples.utils.SessionManager;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Controller;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

@Controller
@AllArgsConstructor
public class LoginController {
    private final CompteService compteService;
    private final ConnexionUI connexionUI;
    private MainController mainController;
    private final SessionManager sessionManager;
    private PrincipalUI principalUI;

    public boolean login(Compte compte) {
        return compteService.connexion(compte);
    }

    public void seConnecter(){
        String matricule = connexionUI.getMatriculeField().getText();
        String password = connexionUI.getPasswordField().getText();

        if (matricule.isEmpty() || password.isEmpty()) {
            JOptionPane.showMessageDialog(connexionUI, "Veuillez remplir tous les champs.", "Erreur", JOptionPane.ERROR_MESSAGE);
            return;
        }

        Compte compte = new Compte();
        compte.setUsername(matricule);
        compte.setPassword(password);

        boolean isAuthenticated = login(compte);
        if (isAuthenticated) {
            principalUI.getProfilButton().setText(sessionManager.getUtilisateurCourant().getUsername());
            mainController.getPrincipalUI().principal();
            System.out.println("==============utilisateur & compte connecté...>>>:"+sessionManager.getUtilisateurCourant());
            connexionUI.dispose(); // Close login window
        } else {
            JOptionPane.showMessageDialog(connexionUI, "Nom d'utilisateur ou mot de passe incorrect.", "Erreur", JOptionPane.ERROR_MESSAGE);
        }
    }

    public void init(){
        connexionUI.setVisible(true);
        connexionUI.getConnexionButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                seConnecter();
            }
        });

    }
}

