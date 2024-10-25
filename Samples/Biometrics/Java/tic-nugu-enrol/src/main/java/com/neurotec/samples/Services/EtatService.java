package com.neurotec.samples.Services;

import com.neurotec.samples.model.Etat;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface EtatService {

    Etat create(Etat etat);

    Etat update(Etat etat);

    Optional<Etat> get(Long id);

    Page<Etat> findAll(Pageable pageable);

    void delete(Long id);
}
