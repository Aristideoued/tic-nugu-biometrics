package com.neurotec.samples.ui;

import lombok.Data;
import org.springframework.stereotype.Component;

import javax.swing.*;
import java.awt.*;

@Data
@Component
public class FormBodyPanelUI extends JPanel {

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
    private JButton submitButton = new JButton("Suivant");


    FormBodyPanelUI() {
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
        submitButton = new JButton("Suivant");
        add(submitButton, gbc);


//        submitButton.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                String nom = nomField.getText();
//                String email = emailField.getText();
//
//                if (nom.isEmpty()) {
//                    JOptionPane.showMessageDialog(FormBodyPanel.this,
//                            "Le nom ne peut pas être vide", "Erreur", JOptionPane.ERROR_MESSAGE);
//                } else if (!isValidEmail(email)) {
//                    JOptionPane.showMessageDialog(FormBodyPanel.this,
//                            "Veuillez entrer un email valide", "Erreur", JOptionPane.ERROR_MESSAGE);
//                } else {
//                    Enrole enrole = new Enrole();
//                    enrole.setNom(nomField.getText());
//                    enrole.setPrenom(prenomField.getText());
//                    enrole.setNomJF(nomJFField.getText());
//                    SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
//                    try {
//                        Date date = dateFormat.parse(dateNaissanceField.getText());
//                        enrole.setDateNaissance(date);
//                    } catch (ParseException ex) {
//                        throw new RuntimeException(ex);
//                    }
//                    enrole.setMatricule(Integer.valueOf(matriculeField.getText()));
//                    enrole.setLieuNaissance(lieuNaissanceField.getText());
//                    enrole.setSexe((String) sexeComboBox.getSelectedItem());
//                    enrole.setTelephone(telephoneField.getText());
//                    enrole.setMail(emailField.getText());
//                    enrole.setTypePiece(typePieceComboBox.getItemAt(typePieceComboBox.getSelectedIndex()));
//                    enrole.setNip(nipField.getText());
//                    enrole.setNip(nipField.getText());
//                    enrole.setNip(nipField.getText());
//
//                    //enroleService.create(enrole);
//                    JOptionPane.showMessageDialog(FormBodyPanel.this,
//                            "Formulaire soumis avec succès!", "Succès", JOptionPane.INFORMATION_MESSAGE);
//                }
//
//            }
//        });

    }

    // Méthode de validation de l'email
    private boolean isValidEmail(String email) {
        return email.matches("^[A-Za-z0-9+_.-]+@(.+)$");
    }

}
