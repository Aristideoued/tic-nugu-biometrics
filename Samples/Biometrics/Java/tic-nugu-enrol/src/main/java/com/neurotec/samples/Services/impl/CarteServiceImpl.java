package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.CarteService;
import com.neurotec.samples.model.Carte;
import com.neurotec.samples.repository.CarteRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class CarteServiceImpl implements CarteService {

    private final CarteRepository carteRepository;

    @Override
    public Carte create(Carte carte) {
        return carteRepository.save(carte);
    }

    @Override
    public Carte update(Carte carte) {
        return carteRepository.save(carte);
    }


    @Override
    public Optional<Carte> get(Long id) {
        Carte carte;
        if (carteRepository.findById(id).isPresent()) {
            carte = carteRepository.findById(id).get();
        } else {
            carte = null;
        }
        return Optional.ofNullable(carte);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Carte> findAll(Pageable pageable) {
        return carteRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        carteRepository.deleteById(id);

    }
}
