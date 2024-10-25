package com.neurotec.samples.Services;

import com.neurotec.samples.model.Profil;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;
import java.util.Optional;

public interface ProfilService {

    Profil create(Profil profil);

    Profil update(Profil profil);

    Optional<Profil> get(Long id);

    Page<Profil> findAll(Pageable pageable);
    void delete(Long id);

    List<Profil> findProfils();
    Profil getProfilByLibelle(String libelle);

}
