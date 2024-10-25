/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.neurotec.samples.ui;


import com.neurotec.samples.Services.CompteService;
import lombok.Data;
import org.springframework.stereotype.Component;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Date;
import javax.swing.*;

/**
 *
 * @author hp ZINA
 */
@Data
@Component
public class EnrolementUI extends JPanel{

    private final FormBodyPanel formBodyPanel ;
    private final KitInitialDataPanel kitInitialDataPanel ;
    private final JPanel enrolPanel;
   private final PrincipalUI principalUI ;
    JLabel enteteBiogLabel = new JLabel("Données biographiques", JLabel.CENTER);


    public EnrolementUI() {
        kitInitialDataPanel =new KitInitialDataPanel();
        formBodyPanel = new FormBodyPanel();
        principalUI = new PrincipalUI();
        enrolPanel = new JPanel(new GridLayout(1, 2));
        setLayout(new BorderLayout());
        enteteBiogLabel.setFont(new Font("Serif", Font.BOLD, 20));
        enrolPanel.add(formBodyPanel);
        enrolPanel.add(kitInitialDataPanel);
        this.add(enteteBiogLabel, BorderLayout.NORTH);
        this.add(enrolPanel, BorderLayout.CENTER);

        // Rendre la fenêtre visible
        setVisible(true);

    }

//    private void creerEnrole() {
//        Enrole enrole = new Enrole();
//        enrole.setMatricule(Integer.parseInt(formBodyPanel.matriculeField.getText()));
//        enrole.setNom(formBodyPanel.nomField.getText());
//        enrole.setPrenom(formBodyPanel.prenomField.getText());
//        enrole.setDateEnrolement(new Date());
//        enrole.setDateNaissance(formBodyPanel.dateNaissanceField.getText());
//    }


}

class FormBodyPanel extends JPanel {

    JTextField matriculeField;
    JTextField nipField;
    JComboBox<String> typePieceComboBox;
    JTextField refPieceField;
    JTextField nomField;
    JTextField nomJFField;
    JTextField prenomField;
    JTextField dateNaissanceField;
    JTextField lieuNaissanceField;
    JComboBox<String> sexeComboBox;
    JTextField telephoneField;
    JTextField emailField;
    private final CompteService compteService ;
   private final PrincipalUI principalUI ;


    FormBodyPanel() {
        compteService = null ;
        principalUI= new PrincipalUI();
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 5, 10, 5); // Marges entre les composants
        gbc.fill = GridBagConstraints.HORIZONTAL;

        // Ajout des étiquettes et des champs
        gbc.gridx = 0; gbc.gridy = 0;
        add(new JLabel("Matricule:"), gbc);

        gbc.gridx = 1; gbc.gridy = 0;
        matriculeField = new JTextField(30);
        add(matriculeField, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        add(new JLabel("NIP:"), gbc);

        gbc.gridx = 1; gbc.gridy = 1;
        nipField = new JTextField(30);
        add(nipField, gbc);

        gbc.gridx = 0; gbc.gridy = 2;
        add(new JLabel("Type de pièce d'identification:"), gbc);

        gbc.gridx = 1; gbc.gridy = 2;
        String[] typePieceOptions = { "", "CNIB", "PASSPORT", "CARTE CONSULAIRE" };
        typePieceComboBox = new JComboBox<>(typePieceOptions);
        add(typePieceComboBox, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        add(new JLabel("Référence de la pièce:"), gbc);

        gbc.gridx = 1; gbc.gridy = 3;
        refPieceField = new JTextField(30);
        add(refPieceField, gbc);

        gbc.gridx = 0; gbc.gridy = 4;
        add(new JLabel("Nom:"), gbc);

        gbc.gridx = 1; gbc.gridy = 4;
        nomField = new JTextField(30);
        add(nomField, gbc);

        gbc.gridx = 0; gbc.gridy = 5;
        add(new JLabel("Nom de jeune fille:"), gbc);

        gbc.gridx = 1; gbc.gridy = 5;
        nomJFField = new JTextField(30);
        add(nomJFField, gbc);

        gbc.gridx = 0; gbc.gridy = 6;
        add(new JLabel("Prénom:"), gbc);

        gbc.gridx = 1; gbc.gridy = 6;
        prenomField = new JTextField(30);
        add(prenomField, gbc);

        gbc.gridx = 0; gbc.gridy = 7;
        add(new JLabel("Date de naissance:"), gbc);

        gbc.gridx = 1; gbc.gridy = 7;
        dateNaissanceField = new JTextField(30);
        add(dateNaissanceField, gbc);

        gbc.gridx = 0; gbc.gridy = 8;
        add(new JLabel("Lieu de naissance:"), gbc);

        gbc.gridx = 1; gbc.gridy = 8;
        lieuNaissanceField = new JTextField(30);
        add(lieuNaissanceField, gbc);

        gbc.gridx = 0; gbc.gridy = 9;
        add(new JLabel("Sexe:"), gbc);

        gbc.gridx = 1; gbc.gridy = 9;
        String[] sexeOptions = { "", "Homme", "Femme" };
        sexeComboBox = new JComboBox<>(sexeOptions);
        add(sexeComboBox, gbc);

        gbc.gridx = 0; gbc.gridy = 10;
        add(new JLabel("Téléphone:"), gbc);

        gbc.gridx = 1; gbc.gridy = 10;
        telephoneField = new JTextField(30);
        add(telephoneField, gbc);

        gbc.gridx = 0; gbc.gridy = 11;
        add(new JLabel("Email:"), gbc);

        gbc.gridx = 1; gbc.gridy = 11;
        emailField = new JTextField(30);
        add(emailField, gbc);

        // Bouton de soumission
        gbc.gridx = 0; gbc.gridy = 12; gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        JButton submitButton = new JButton("Suivant");
        add(submitButton, gbc);


        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String nom = nomField.getText();
                String email = emailField.getText();

                if (nom.isEmpty()) {
                    JOptionPane.showMessageDialog(FormBodyPanel.this,
                            "Le nom ne peut pas être vide", "Erreur", JOptionPane.ERROR_MESSAGE);
                } else if (!isValidEmail(email)) {
                    JOptionPane.showMessageDialog(FormBodyPanel.this,
                            "Veuillez entrer un email valide", "Erreur", JOptionPane.ERROR_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(FormBodyPanel.this,
                            "Formulaire soumis avec succès!", "Succès", JOptionPane.INFORMATION_MESSAGE);
                    //dispose():
                   // new CreerUserUI().setVisible(true);
                   // new ConnexionUI();

                    // Créer un nouveau JFrame et ajouter le panneau CreerUserUI
                /***    JFrame creerUserFrame = new JFrame("Créer Utilisateur");
                    creerUserFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                    creerUserFrame.setSize(600, 400);

                    // Ajouter une instance de CreerUserUI au JFrame
                    CreerUserUI creerUserPanel = new CreerUserUI();
                    creerUserFrame.add(creerUserPanel);

                    // Rendre le JFrame visible
                    creerUserFrame.setVisible(true);*/

                new Topaz().setVisible(true);
                }
            }
        });


    }
    // Méthode de validation de l'email
    private boolean isValidEmail(String email) {
        return email.matches("^[A-Za-z0-9+_.-]+@(.+)$");
    }

}

class KitInitialDataPanel extends JPanel {
    KitInitialDataPanel() {
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 5, 10, 5); // Marges entre les composants
        gbc.fill = GridBagConstraints.HORIZONTAL;

        // Ajout des étiquettes et des champs
        gbc.gridx = 0; gbc.gridy = 0;
        add(new JLabel("Numero du Kit :"), gbc);

        gbc.gridx = 1; gbc.gridy = 0;
        JLabel numeroLabel = new JLabel("");
        add(numeroLabel, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        add(new JLabel("Etat du Kit :"), gbc);

        gbc.gridx = 1; gbc.gridy = 1;
        JLabel etatLabel = new JLabel("");
        add(etatLabel, gbc);

        gbc.gridx = 0; gbc.gridy = 2;
        add(new JLabel("Region :"), gbc);

        gbc.gridx = 1; gbc.gridy = 2;
        JLabel regionLabel = new JLabel("");
        add(regionLabel, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        add(new JLabel("Province :"), gbc);

        gbc.gridx = 1; gbc.gridy = 3;
        JLabel provinceLabel = new JLabel("");
        add(provinceLabel, gbc);

        gbc.gridx = 0; gbc.gridy = 4;
        add(new JLabel("Province :"), gbc);

        gbc.gridx = 1; gbc.gridy = 4;
        JLabel ecoleLabel = new JLabel("");
        add(ecoleLabel, gbc);

        gbc.gridx = 0; gbc.gridy = 5;
        add(new JLabel("Lieu :"), gbc);

        gbc.gridx = 1; gbc.gridy = 5;
        JLabel lieuLabel = new JLabel("");
        add(lieuLabel, gbc);
    }
}