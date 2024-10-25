package com.neurotec.samples.Services;

import com.neurotec.samples.model.Utilisateur;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import java.util.Optional;


public interface UtilisateurService {

    Utilisateur create(Utilisateur utilisateur);

    Utilisateur update(Utilisateur utilisateur);

    Optional<Utilisateur> get(Long id);

    Page<Utilisateur> findAll(Pageable pageable);

    void delete(Long id);
}
