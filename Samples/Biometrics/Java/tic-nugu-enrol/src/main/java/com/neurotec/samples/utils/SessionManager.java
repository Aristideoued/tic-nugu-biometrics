package com.neurotec.samples.utils;

import com.neurotec.samples.model.Compte;
import org.springframework.stereotype.Component;

@Component
public class SessionManager {
    private Compte utilisateurCourant;

    public Compte getUtilisateurCourant() {
        return utilisateurCourant;
    }

    public void setUtilisateurCourant(Compte utilisateurCourant) {
        this.utilisateurCourant = utilisateurCourant;
    }

    public void clearSession() {
        this.utilisateurCourant = null;
    }

    public boolean isAuthenticated() {
        return utilisateurCourant != null;
    }
}
