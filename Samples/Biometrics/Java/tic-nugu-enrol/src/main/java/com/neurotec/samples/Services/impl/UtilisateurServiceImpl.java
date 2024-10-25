package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.UtilisateurService;
import com.neurotec.samples.model.Utilisateur;
import com.neurotec.samples.repository.UtilisateurRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class UtilisateurServiceImpl implements UtilisateurService {

    private final UtilisateurRepository utilisateurRepository;

    @Override
    public Utilisateur create(Utilisateur utilisateur) {
        return utilisateurRepository.save(utilisateur);
    }

    @Override
    public Utilisateur update(Utilisateur utilisateur) {
        return utilisateurRepository.save(utilisateur);
    }


    @Override
    public Optional<Utilisateur> get(Long id) {
        Utilisateur utilisateur;
        if (utilisateurRepository.findById(id).isPresent()) {
            utilisateur = utilisateurRepository.findById(id).get();
        } else {
            utilisateur = null;
        }
        return Optional.ofNullable(utilisateur);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Utilisateur> findAll(Pageable pageable) {
        return utilisateurRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        utilisateurRepository.deleteById(id);

    }
}
