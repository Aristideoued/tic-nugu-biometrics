package com.neurotec.samples.controller;


import com.neurotec.samples.Services.EcoleService;
import com.neurotec.samples.Services.KitService;
import com.neurotec.samples.Services.ProvinceService;
import com.neurotec.samples.Services.RegionService;
import com.neurotec.samples.model.Ecole;
import com.neurotec.samples.model.Kit;
import com.neurotec.samples.model.Province;
import com.neurotec.samples.model.Region;
import com.neurotec.samples.ui.InitiationKitUI;
import org.springframework.stereotype.Controller;

import lombok.AllArgsConstructor;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

@Controller
@AllArgsConstructor
public class InitkitController {
    private final RegionService regionService;

    private final ProvinceService provinceService;
    private final EcoleService ecoleService;
    private final KitService kitService;
    private final InitiationKitUI initiationKitUI;

    private List<Region> liste;
    private List<Province> listP;
    private List<Ecole> listE;
    private List<Kit> listk;

    public List<String> findAllRegion(){
        System.out.println("Dans InitkitController findAllRegion");
        liste = regionService.laListe();
        List<String> rep = new ArrayList<>();
        rep.add("Choisir une region");
        for (int i = 0; i < liste.size(); i++) {
            //System.out.println(liste.get(i));
            rep.add(liste.get(i).getLibelle());
        }
        return rep;
    }

    void initButtons(){
        initiationKitUI.getBtnInitKit().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                long ecoleId, kitId;
                int rangEcole = initiationKitUI.getEcoleChoix().getSelectedIndex();
                int rangKit = initiationKitUI.getKitChoix().getSelectedIndex();
                if (rangEcole==0){
                    JOptionPane.showMessageDialog(initiationKitUI,
                            "Veuillez choisir une école",
                            "Erreur, formulaire incomplet",
                            JOptionPane.WARNING_MESSAGE);
                } else if (rangKit==0) {
                    JOptionPane.showMessageDialog(initiationKitUI,
                            "Veuillez choisir un kit",
                            "Erreur, formulaire incomplet",
                            JOptionPane.WARNING_MESSAGE);
                }
                //enregistrement de l'initialisation
            }
        });

        initiationKitUI.getBtnCancel().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int rep = JOptionPane.showConfirmDialog(null,"Voulez-vous vraiment annuler l'initiatlisation?", "Confirmation", JOptionPane.OK_CANCEL_OPTION);
                if (rep==0){
//                    initiationKitUI.dispose();
                }
            }
        });
    }

    public List<String> findAllKits(){
        //System.out.println("Dans InitkitController findAllRegion");
        listk = kitService.findAll();
        List<String> rep = new ArrayList<>();
        rep.add("Choisir un kit");
        for (int i = 0; i < listk.size(); i++) {
            //System.out.println(liste.get(i));
            rep.add(listk.get(i).getTypeKit()+" n°"+listk.get(i).getNumeroKit());
        }
        return rep;
    }

    public void afficherRegions(){
        List<String> regions = findAllRegion();
        initiationKitUI.getRegionChoix().setModel(new DefaultComboBoxModel(regions.toArray()));
        initiationKitUI.getRegionChoix().updateUI();
        List<String> kits = findAllKits();
        initiationKitUI.getKitChoix().setModel(new DefaultComboBoxModel(kits.toArray()));
        initiationKitUI.getKitChoix().updateUI();
//        initiationKitUI.setVisible(true);
        initiationKitUI.getRegionChoix().addItemListener(new ItemListener() {

            @Override
            public void itemStateChanged(ItemEvent e) {
                int nb = initiationKitUI.getRegionChoix().getSelectedIndex();
                //System.out.println("nb="+nb);
                if (nb==0){
                    initiationKitUI.getProvinceChoix().setModel(new DefaultComboBoxModel(new String[]{"Choisir une province"}));
                    initiationKitUI.getEcoleChoix().setModel(new DefaultComboBoxModel(new String[]{"Choisir une école"}));
                }else{
                    Region selectedRegion = liste.get(nb-1);
                    System.out.println("nb="+nb+"; choix= "+initiationKitUI.getRegionChoix().getSelectedItem()+"; region="+selectedRegion.getLibelle());
                    //provinces de la région
                    listP = provinceService.findProvinceByRegion(selectedRegion);
                    List<String> cProv = new ArrayList<>();
                    cProv.add("Choisir une province");
                    for (int i = 0; i < listP.size(); i++) {
                        cProv.add(listP.get(i).getLibelle());
                    }
                    initiationKitUI.getProvinceChoix().setModel(new DefaultComboBoxModel(cProv.toArray()));
                }
                initiationKitUI.getProvinceChoix().addItemListener(new ItemListener() {
                    @Override
                    public void itemStateChanged(ItemEvent e) {
                        int nb = initiationKitUI.getProvinceChoix().getSelectedIndex();
                        //System.out.println("nb="+nb);
                        if (nb==0){
                            initiationKitUI.getEcoleChoix().setModel(new DefaultComboBoxModel(new String[]{"Choisir une école"}));
                        }else{
                            Province selectedProvince = listP.get(nb-1);
                            System.out.println("nb="+nb+"; choix= "+initiationKitUI.getRegionChoix().getSelectedItem()+"; region="+selectedProvince.getLibelle());
                            //provinces de la région
                            List<Ecole> listP = ecoleService.findEcolesByProvinces(selectedProvince);
                            List<String> cEcole = new ArrayList<>();
                            cEcole.add("Choisir une école");
                            for (int i = 0; i < listP.size(); i++) {
                                cEcole.add(listP.get(i).getLibelle());
                            }
                            initiationKitUI.getEcoleChoix().setModel(new DefaultComboBoxModel(cEcole.toArray()));
                        }
                    }
                });
            }
        });

        initButtons();
    }

}
