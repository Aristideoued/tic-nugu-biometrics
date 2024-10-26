package com.neurotec.samples.controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.ResultSet;
import java.util.List;
import java.util.Vector;

import javax.annotation.PostConstruct;
import javax.swing.table.DefaultTableModel;

import com.neurotec.samples.Services.RegionService;
import com.neurotec.samples.model.Region;
import com.neurotec.samples.ui.RegionUI;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;


import lombok.AllArgsConstructor;
@Controller
@AllArgsConstructor
public class RegionController {
    private final RegionService regionService;
    private final RegionUI regionUI;
    

    public Region creerRegion(Region regionModel){
        System.out.println("creer region:"+regionModel);
        regionService.create(regionModel);
        return regionModel;      
        
    }
    
    public Region modifierRegion(Region regionModel){
        System.out.println("modifier region:"+regionModel);
        regionService.update(regionModel);
        return regionModel;
    }

    public List<Region> findAllRegion(){
        return regionService.laListe();
    } 

    public void creationRegion() {
        Region regionModel=new Region();
        regionModel.setLibelle(regionUI.getLibelle_region().getText());
        creerRegion(regionModel);
        afficherRegion();
    }

    public void modificationRegion(){
        Region regionModel=new Region();
        regionModel.setLibelle(regionUI.getLibelle_region().getText());
        modifierRegion(regionModel);
        afficherRegion();
    }

    /**
     * 
     */
     public void loadRegion() {
        List<Region> regions= this.findAllRegion();
        
    }

    public void afficherRegion(){       
         List<Region> rs= this.findAllRegion();
        
          Vector tab= new Vector();        
          for(Region reg: rs){
            Vector element= new Vector();
            element.addElement(reg.getLibelle());
            tab.add(element);
           
          }
          Vector tabColonne=new Vector();
          tabColonne.addElement("libelle");
          DefaultTableModel tabModel= new DefaultTableModel(tab,tabColonne );
          regionUI.getListRegions().setModel(tabModel);
    }

     @PostConstruct
    public void prepareAndOpenFrame(){
        
        regionUI.getAjouterRegion().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                creationRegion();
                
            }          
        }
       
        );
    }


}
