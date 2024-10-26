/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.neurotec.samples.ui;

import lombok.AllArgsConstructor;
import lombok.Data;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.awt.*;
import javax.swing.*;

/**
 *
 * @author hp ZINA
 */
@Data
@Component
@AllArgsConstructor
public class EnrolementUI extends JPanel{

    private final FormBodyPanelUI formBodyPanel ;
    private final KitInitialDataPanel kitInitialDataPanel ;
    private final JPanel enrolPanel;
    @Autowired
   private  PrincipalUI principalUI ;
    JLabel enteteBiogLabel = new JLabel("Données biographiques", JLabel.CENTER);

    public EnrolementUI(LayoutManager layout, boolean isDoubleBuffered, FormBodyPanelUI formBodyPanel, KitInitialDataPanel kitInitialDataPanel, JPanel enrolPanel, PrincipalUI principalUI, JLabel enteteBiogLabel) {
        super(layout, isDoubleBuffered);
        this.formBodyPanel = formBodyPanel;
        this.kitInitialDataPanel = kitInitialDataPanel;
        this.enrolPanel = enrolPanel;
        this.principalUI = principalUI;
        this.enteteBiogLabel = enteteBiogLabel;
    }

    public EnrolementUI() {

        kitInitialDataPanel =new KitInitialDataPanel();
        formBodyPanel = new FormBodyPanelUI();
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