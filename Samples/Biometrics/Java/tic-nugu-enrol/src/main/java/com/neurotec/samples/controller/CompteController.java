package com.neurotec.samples.controller;



import com.neurotec.samples.Services.CompteService;
import com.neurotec.samples.model.Compte;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;


@Controller
public class CompteController {

    @Autowired
    private final CompteService compteService;

    public CompteController(CompteService compteService) {
        this.compteService = compteService;
    }



    public boolean login(Compte compte) {
        return compteService.connexion(compte);
    }


}
