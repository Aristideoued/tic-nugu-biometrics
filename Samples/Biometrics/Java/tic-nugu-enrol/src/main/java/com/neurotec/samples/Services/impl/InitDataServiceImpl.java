package com.neurotec.samples.Services.impl;

import java.util.Date;

import com.neurotec.samples.Services.InitiDataService;
import com.neurotec.samples.model.Compte;
import com.neurotec.samples.model.Profil;
import com.neurotec.samples.model.Utilisateur;
import com.neurotec.samples.repository.CompteRepository;
import com.neurotec.samples.repository.ProfilRepository;
import com.neurotec.samples.repository.UtilisateurRepository;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;


import lombok.AllArgsConstructor;

@Service
@AllArgsConstructor
public class InitDataServiceImpl implements InitiDataService {
 
     private final CompteRepository compteRepository;
     private final ProfilRepository profilRepository;
     private final UtilisateurRepository utilisateurRepository;
     private final BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
   
     public Compte create() {

// verification
        if(compteRepository.count()==0){
            Compte newCompte= new Compte();
            Profil newProfil=new Profil();
            Profil newProfil1=new Profil();
            Profil newProfil2=new Profil();
        Utilisateur newUtilisateur= new Utilisateur();
 //  init profil
        newProfil.setLibelle("admin");
        newProfil.setDescription("profil administrateur");
        newProfil.setCreatedBy("system");
        newProfil.setCreatedDate(new Date().toInstant());
        newProfil=profilRepository.save(newProfil);

        newProfil1.setLibelle("Superviseur");
        newProfil1.setDescription("profil Superviseur");
        newProfil1.setCreatedBy("system");
        newProfil1.setCreatedDate(new Date().toInstant());
        newProfil1=profilRepository.save(newProfil1);

        newProfil2.setLibelle("Opérateur");
        newProfil2.setDescription("profil Opérateur");
        newProfil2.setCreatedBy("system");
        newProfil2.setCreatedDate(new Date().toInstant());
        newProfil2=profilRepository.save(newProfil2);

    // init  compte
        newUtilisateur.setMatricule("admin");
        newUtilisateur.setNom("admin");
        newUtilisateur.setPrenom("admin");
        newUtilisateur.setCreatedBy("system");
        newUtilisateur.setCreatedDate(new Date().toInstant());
        newUtilisateur=utilisateurRepository.save(newUtilisateur);
        newCompte.setUsername("admin");
        newCompte.setProfil(newProfil);
        newCompte.setPassword(passwordEncoder.encode("admin"));
        newCompte.setUtilisateur(null);
        newCompte.setFlActivated(true);
        newCompte= compteRepository.save(newCompte);
        }
        return null;
       
        
        
    }

   
     
}
