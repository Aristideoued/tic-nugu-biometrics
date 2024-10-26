package com.neurotec.samples.controller;


import com.neurotec.samples.Services.EnroleService;
import com.neurotec.samples.ui.*;
import com.neurotec.samples.utils.SessionManager;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import org.springframework.stereotype.Controller;

import javax.annotation.PostConstruct;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


@Controller
@AllArgsConstructor
@Getter
@Setter
public class MainController {
    private final PrincipalUI principalUI;
    private final EnrolementUI enrolementUI;
    private UtilisateurController utilisateurController;
    private EnroleController enroleController;
    private RegionController regionController;
    private CreerUserUI creerUserUI;
    private RegionUI regionUI;

    private InitkitController initkitController;
    private InitiationKitUI initiationKitUI;

    private ChangePasswordUI changePasswordUI;
    private DetailProfilUI detailProfilUI;
    private final ConnexionUI connexionUI;
    private final SessionManager sessionManager;
    private final ConsultUserUI consultUserUI;
    private final EnroleService enroleService;

    public void showMain() {
        principalUI.setVisible(true);
    }

    @PostConstruct
    public void openCreateUser() {
        System.out.println("utilisateur connecté en temps réel:" + sessionManager.getUtilisateurCourant());
        // utilisateurController.prepareAndOpenFrame();
        principalUI.getCreer().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                utilisateurController.loadProfils();
                principalUI.repaintPanel(creerUserUI);
//                   creerUserUI.setVisible(true);
            }
        });


        principalUI.getUtilisateurs().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // creerUserUI.setVisible(true);
                utilisateurController.loadAll();
                consultUserUI.setVisible(true);
            }
        });

        principalUI.getChangepassword().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                changePasswordUI.setVisible(true);
            }
        });

        principalUI.getMonprofil().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("utilisateur connecté:" + sessionManager.getUtilisateurCourant());
                detailProfilUI.setVisible(true);
            }
        });

        principalUI.getFonctionnaireItem().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                principalUI.repaintPanel(enrolementUI);
                //enroleController.creerEnrole();
            }
        });

        principalUI.getLogout().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Afficher une boîte de confirmation
                int option = JOptionPane.showConfirmDialog(principalUI,
                        "Voulez-vous vraiment vous déconnecter ?",
                        "Confirmation",
                        JOptionPane.YES_NO_OPTION,
                        JOptionPane.QUESTION_MESSAGE);

                // Vérifier la réponse de l'utilisateur
                if (option == JOptionPane.YES_OPTION) {
                    // Si l'utilisateur a cliqué sur "Oui", procédez à la déconnexion
                    System.out.println("Déconnexion en cours...");
                    sessionManager.clearSession();
                    // Par exemple, fermer la fenêtre actuelle pour simuler la déconnexion :
                    principalUI.dispose();
                    connexionUI.resetForm();  // Réinitialiser le formulaire de connexion
                    connexionUI.setVisible(true);
                } else {
                    // Si l'utilisateur a cliqué sur "Non", annuler la déconnexion
                    System.out.println("Déconnexion annulée");
                }
            }
        });

    }

    @PostConstruct
    public void openRegion() {
        // utilisateurController.prepareAndOpenFrame();
        principalUI.getRegionItem().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                regionController.afficherRegion();
                principalUI.repaintPanel(regionUI);
//                       regionUI.setVisible(true);

            }
        });
    }

    @PostConstruct
    public void openInitKit() {
        // utilisateurController.prepareAndOpenFrame();
        principalUI.getLancerItem().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //utilisateurController.loadProfils();
                //creerUserUI.setVisible(true);
                initkitController.afficherRegions();
//                initiationKitUI.setVisible(true);
                principalUI.repaintPanel(new InitiationKitUI());
            }
        });
    }
}

