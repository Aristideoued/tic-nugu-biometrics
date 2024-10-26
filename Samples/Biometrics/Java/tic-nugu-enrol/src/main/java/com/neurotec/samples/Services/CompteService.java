package com.neurotec.samples.Services;

import com.neurotec.samples.model.Compte;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

public interface CompteService {
    Compte create(Compte compte);

    boolean connexion(Compte compte);

    Compte update(Compte compte);

    Optional<Compte> get(Long id);

    Page<Compte> findAll(Pageable pageable);
    List<Compte> findAllCompte();

    List<Compte> findActiveComptes();

    Compte findById(Long id);

    void delete(Long id);

    boolean changePassword(Long compteId, String currentPassword, String newPassword);

    boolean resetPassword(Long compteId);
}
