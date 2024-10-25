package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.CompteService;
import com.neurotec.samples.model.Compte;
import com.neurotec.samples.repository.CompteRepository;
import com.neurotec.samples.utils.SessionManager;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@AllArgsConstructor
public class CompteServiceImpl implements CompteService {

    private final CompteRepository compteRepository;
    private final SessionManager sessionManager;

    @Override

    public Compte create(Compte compte) {
        BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
        // Crypter le mot de passe avant de sauvegarder
        String encodedPassword = passwordEncoder.encode(compte.getPassword());
        compte.setPassword(encodedPassword);  // Mettre à jour le mot de passe avec le mot de passe crypté

        // Sauvegarder l'objet Compte avec le mot de passe crypté
        return compteRepository.save(compte);
    }

    @Override
    public boolean connexion(Compte compte) {
        System.out.println("==============matching password...");
        BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
        try {

            Optional<Compte> compteFound = compteRepository.findCompteByUsername(compte.getUsername());
            System.out.println("==============matching password..."+compteFound.get());
            if (compteFound.isPresent() && compteFound.get().isFlActivated()==true) {
                String hashedPassword = compteFound.get().getPassword();
                System.out.println("==============matching password..."+passwordEncoder.matches(compte.getPassword(), hashedPassword));
                sessionManager.setUtilisateurCourant(compteFound.get());
                System.out.println("==============utilisateur & compte connecté..."+sessionManager.getUtilisateurCourant());
                return passwordEncoder.matches(compte.getPassword(), hashedPassword);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        return false;
    }

    @Override
    public Compte update(Compte compte) {
        return compteRepository.save(compte);
    }


    @Override
    public Optional<Compte> get(Long id) {
        Compte compte;
        if (compteRepository.findById(id).isPresent()) {
            compte = compteRepository.findById(id).get();
        } else {
            compte = null;
        }
        return Optional.ofNullable(compte);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Compte> findAll(Pageable pageable) {
        return compteRepository.findAll(pageable);
    }
    @Transactional(readOnly = true)
    public List<Compte> findAllCompte() {
        return compteRepository.findAll();
    }

    @Override
    public Compte findById(Long id) {

        return compteRepository.findById(id).orElse(null);
    }

    @Override
    public void delete(Long id) {
        compteRepository.deleteById(id);

    }

    @Override
    public boolean changePassword(Long compteId, String currentPassword, String newPassword) {
        // Trouver le compte
        BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
        Optional<Compte> optionalCompte = compteRepository.findById(compteId);
        if (optionalCompte.isPresent()) {
            Compte compte = optionalCompte.get();

            // Vérifier si le mot de passe actuel est correct
            if (passwordEncoder.matches(currentPassword, compte.getPassword())) {
                // Mettre à jour le mot de passe
                compte.setPassword(passwordEncoder.encode(newPassword));
                compteRepository.save(compte);
                return true;  // Mot de passe changé avec succès
            }
        }
        return false;  // Le mot de passe actuel est incorrect ou le compte n'existe pas
    }
}
