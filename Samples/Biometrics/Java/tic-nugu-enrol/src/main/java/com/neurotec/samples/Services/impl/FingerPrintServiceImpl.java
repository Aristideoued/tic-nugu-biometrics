package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.FingerPrintService;
import com.neurotec.samples.model.FingerPrint;
import com.neurotec.samples.repository.FingerPrintRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class FingerPrintServiceImpl implements FingerPrintService {

    private final FingerPrintRepository fingerPrintRepository;

    @Override
    public FingerPrint create(FingerPrint fingerPrint) {
        return fingerPrintRepository.save(fingerPrint);
    }

    @Override
    public FingerPrint update(FingerPrint fingerPrint) {
        return fingerPrintRepository.save(fingerPrint);
    }


    @Override
    public Optional<FingerPrint> get(Long id) {
        FingerPrint fingerPrint;
        if (fingerPrintRepository.findById(id).isPresent()) {
            fingerPrint = fingerPrintRepository.findById(id).get();
        } else {
            fingerPrint = null;
        }
        return Optional.ofNullable(fingerPrint);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<FingerPrint> findAll(Pageable pageable) {
        return fingerPrintRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        fingerPrintRepository.deleteById(id);

    }
}
