package com.neurotec.samples.Services;

import com.neurotec.samples.model.Carte;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface CarteService {

    Carte create(Carte carte);

    Carte update(Carte carte);

    Optional<Carte> get(Long id);

    Page<Carte> findAll(Pageable pageable);

    void delete(Long id);
}
