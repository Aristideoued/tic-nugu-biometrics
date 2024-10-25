package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.MatchingService;
import com.neurotec.samples.model.Matching;
import com.neurotec.samples.repository.MatchingRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class MatchingServiceImpl implements MatchingService {

    private final MatchingRepository matchingRepository;

    @Override
    public Matching create(Matching matching) {
        return matchingRepository.save(matching);
    }

    @Override
    public Matching update(Matching matching) {
        return matchingRepository.save(matching);
    }


    @Override
    public Optional<Matching> get(Long id) {
        Matching matching;
        if (matchingRepository.findById(id).isPresent()) {
            matching = matchingRepository.findById(id).get();
        } else {
            matching = null;
        }
        return Optional.ofNullable(matching);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Matching> findAll(Pageable pageable) {
        return matchingRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        matchingRepository.deleteById(id);

    }
}
