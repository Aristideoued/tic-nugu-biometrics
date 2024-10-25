package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.ProfilService;
import com.neurotec.samples.model.Profil;
import com.neurotec.samples.repository.ProfilRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@AllArgsConstructor
public class ProfilServiceImpl implements ProfilService {

    private final ProfilRepository profilRepository;

    @Override
    public Profil create(Profil profil) {
        return profilRepository.save(profil);
    }

    @Override
    public Profil update(Profil profil) {
        return profilRepository.save(profil);
    }

    @Override
    public Optional<Profil> get(Long id) {
        Profil profil;
        if (profilRepository.findById(id).isPresent()) {
            profil = profilRepository.findById(id).get();
        } else {
            profil = null;
        }
        return Optional.ofNullable(profil);
    }

    @Override
    @Transactional(readOnly = true)
    public Page<Profil> findAll(Pageable pageable) {
        return profilRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        profilRepository.deleteById(id);
    }

    @Override
    public List<Profil> findProfils() {
        return profilRepository.findAll();
    }

    @Override
    public Profil getProfilByLibelle(String libelle) {
        return profilRepository.getProfilByLibelle(libelle);
    }

}
