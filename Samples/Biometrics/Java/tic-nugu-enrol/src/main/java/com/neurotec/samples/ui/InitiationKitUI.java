package com.neurotec.samples.ui;


import javax.swing.*;


import lombok.Data;
import org.springframework.stereotype.Component;

import java.awt.*;
import java.util.List;

@Data
@Component
public class InitiationKitUI extends JPanel {

    private JComboBox<String> regionChoix;
    private JComboBox<String> provinceChoix;
    private JComboBox<String> ecoleChoix;
    private JComboBox<String> kitChoix;

    private JButton btnInitKit;
    private JButton btnCancel;

    public InitiationKitUI(){

//        initUI();
        setLayout(new GridLayout(4,1));
        JPanel ligne1 = new JPanel();
        JPanel ligne2 = new JPanel();
        JPanel ligne3 = new JPanel();
        JPanel ligne4 = new JPanel();
        ligne1.setLayout(new GridLayout(1,4));
        ligne2.setLayout(new GridLayout(1,4));
        ligne3.setLayout(new GridLayout(1,4));
        ligne4.setLayout(new GridLayout(1,4));
        JLabel regionLabel = new JLabel("Choisir la region");
        regionChoix = new JComboBox<>();
        ligne1.add(regionLabel);
        ligne1.add(regionChoix);
        JLabel provLabel = new JLabel("Choisir la province");
        provinceChoix = new JComboBox<>(new String[]{"Choisir la province"});
        ligne1.add(provLabel);
        ligne1.add(provinceChoix);

        JLabel ecoleLabel = new JLabel("Choisir l'école");
        ecoleChoix = new JComboBox<>(new String[]{"Choisir l'école"});
        ligne2.add(ecoleLabel);
        ligne2.add(ecoleChoix);

        JLabel kitLabel = new JLabel("Choisir le kit");
        kitChoix = new JComboBox<>(new String[]{"Choisir le kit"});
        ligne2.add(kitLabel);
        ligne2.add(kitChoix);

        btnInitKit = new JButton("Initialiser le kit");
        btnInitKit.setBackground(Color.green);
        btnCancel = new JButton("Annuler et fermer la fenètre");
        btnCancel.setBackground(Color.orange);
        ligne3.add(btnInitKit);
        ligne3.add(btnCancel);
        add(ligne1);
        add(ligne2);
        add(ligne3);
        add(ligne4);
    }



    public JComboBox<String> getRegionChoix() {
        return regionChoix;
    }

    public void setRegionChoix(JComboBox<String> regionChoix) {
        this.regionChoix = regionChoix;
    }

    public JComboBox<String> getProvinceChoix() {
        return provinceChoix;
    }

    public void setProvinceChoix(JComboBox<String> provinceChoix) {
        this.provinceChoix = provinceChoix;
    }

    public JComboBox<String> getEcoleChoix() {
        return ecoleChoix;
    }

    public void setEcoleChoix(JComboBox<String> ecoleChoix) {
        this.ecoleChoix = ecoleChoix;
    }

    public JComboBox<String> getKitChoix() {
        return kitChoix;
    }

    public void setKitChoix(JComboBox<String> kitChoix) {
        this.kitChoix = kitChoix;
    }

    public JButton getBtnInitKit() {
        return btnInitKit;
    }

    public void setBtnInitKit(JButton btnInitKit) {
        this.btnInitKit = btnInitKit;
    }

    public JButton getBtnCancel() {
        return btnCancel;
    }

    public void setBtnCancel(JButton btnCancel) {
        this.btnCancel = btnCancel;
    }

//    void initUI(){
//        //  JFrame fen = new JFrame();
//        this.setTitle("Initionalisation du kit");
//        this.setSize(800, 400);
//        //Nous demandons maintenant à notre objet de se positionner au centre
//        this.setLocationRelativeTo(null);
//        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
//
//        this.setVisible(true);
//    }

}
