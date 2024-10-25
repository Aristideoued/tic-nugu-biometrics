package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.EtatService;
import com.neurotec.samples.model.Etat;
import com.neurotec.samples.repository.EtatRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class EtatServiceImpl implements EtatService {


    private final EtatRepository etatRepository;

    @Override
    public Etat create(Etat etat) {
        return etatRepository.save(etat);
    }

    @Override
    public Etat update(Etat etat) {
        return etatRepository.save(etat);
    }


    @Override
    public Optional<Etat> get(Long id) {
        Etat etat;
        if (etatRepository.findById(id).isPresent()) {
            etat = etatRepository.findById(id).get();
        } else {
            etat = null;
        }
        return Optional.ofNullable(etat);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Etat> findAll(Pageable pageable) {
        return etatRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        etatRepository.deleteById(id);

    }
}
