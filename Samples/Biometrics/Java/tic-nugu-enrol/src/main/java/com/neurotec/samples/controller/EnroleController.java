package com.neurotec.samples.controller;


import com.neurotec.samples.Services.EnroleService;
import com.neurotec.samples.model.Enrole;
import com.neurotec.samples.swing.MainFrame;
import com.neurotec.samples.ui.EnrolementUI;
import com.neurotec.samples.ui.Topaz;
import com.neurotec.samples.utils.ValidateFieldForm;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Controller;

import javax.annotation.PostConstruct;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

@Controller
@AllArgsConstructor
public class EnroleController {

    private final EnrolementUI enrolementUI;
    //private final FormBodyPanelUI formBodyPanel;
    private final EnroleService enroleService;

    @PostConstruct
    public void prepareAndOpenFrame(){
        //formBodyPanel.setVisible(true);
        enrolementUI.getFormBodyPanel().getSubmitButton().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("enrolement 1");
                creerEnrole();
             //new MainFrame().setVisible(true);
            }
        });

    }

    public void creerEnrole() {
        String nom = enrolementUI.getFormBodyPanel().getNomField().getText();
        String email = enrolementUI.getFormBodyPanel().getEmailField().getText();

        if (nom.isEmpty()) {
            JOptionPane.showMessageDialog(enrolementUI.getFormBodyPanel(),
                    "Le nom ne peut pas être vide", "Erreur", JOptionPane.ERROR_MESSAGE);
        } else if (!ValidateFieldForm.validateEmail(email)) {
            JOptionPane.showMessageDialog(enrolementUI.getFormBodyPanel(),
                    "Veuillez entrer un email valide", "Erreur", JOptionPane.ERROR_MESSAGE);
        } else {
            Enrole enrole = new Enrole();
            enrole.setNom(enrolementUI.getFormBodyPanel().getNomJFField().getText());
            enrole.setPrenom(enrolementUI.getFormBodyPanel().getPrenomField().getText());
            enrole.setNomJF(enrolementUI.getFormBodyPanel().getNomJFField().getText());
            SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
            try {
                Date date = dateFormat.parse(enrolementUI.getFormBodyPanel().getDateNaissanceField().getText());
                enrole.setDateNaissance(date);
            } catch (ParseException ex) {
                throw new RuntimeException(ex);
            }
            enrole.setMatricule(Integer.valueOf(enrolementUI.getFormBodyPanel().getMatriculeField().getText()));
            enrole.setLieuNaissance(enrolementUI.getFormBodyPanel().getLieuNaissanceField().getText());
            enrole.setSexe((String) enrolementUI.getFormBodyPanel().getSexeComboBox().getSelectedItem());
            enrole.setTelephone(enrolementUI.getFormBodyPanel().getTelephoneField().getText());
            enrole.setMail(enrolementUI.getFormBodyPanel().getEmailField().getText());
            enrole.setTypePiece(enrolementUI.getFormBodyPanel().getTypePieceComboBox().getItemAt(enrolementUI.getFormBodyPanel().getTypePieceComboBox().getSelectedIndex()));
            enrole.setNip(enrolementUI.getFormBodyPanel().getNipField().getText());
            enrole.setRefPiece(enrolementUI.getFormBodyPanel().getRefPieceField().getText());

            enroleService.create(enrole);
            JOptionPane.showMessageDialog(enrolementUI.getFormBodyPanel(),
                    "Formulaire soumis avec succès!", "Succès", JOptionPane.INFORMATION_MESSAGE);
                 new Topaz().setVisible(true);
        }

    }

}
