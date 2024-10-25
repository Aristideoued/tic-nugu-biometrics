package com.neurotec.samples.Services;

import com.neurotec.samples.model.Matching;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface MatchingService {

    Matching create(Matching matching);

    Matching update(Matching matching);

    Optional<Matching> get(Long id);

    Page<Matching> findAll(Pageable pageable);

    void delete(Long id);
}
