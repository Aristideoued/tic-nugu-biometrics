package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.FingerDataService;
import com.neurotec.samples.model.FingerData;
import com.neurotec.samples.repository.FingerDataRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class FingerDataServiceImpl implements FingerDataService {

    private final FingerDataRepository fingerDataRepository;

    @Override
    public FingerData create(FingerData fingerData) {
        return fingerDataRepository.save(fingerData);
    }

    @Override
    public FingerData update(FingerData fingerData) {
        return fingerDataRepository.save(fingerData);
    }


    @Override
    public Optional<FingerData> get(Long id) {
        FingerData fingerData;
        if (fingerDataRepository.findById(id).isPresent()) {
            fingerData = fingerDataRepository.findById(id).get();
        } else {
            fingerData = null;
        }
        return Optional.ofNullable(fingerData);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<FingerData> findAll(Pageable pageable) {
        return fingerDataRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        fingerDataRepository.deleteById(id);

    }
}
