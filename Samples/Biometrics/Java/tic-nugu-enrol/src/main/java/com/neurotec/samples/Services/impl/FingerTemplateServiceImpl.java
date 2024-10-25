package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.FingerTemplateService;
import com.neurotec.samples.model.FingerTemplate;
import com.neurotec.samples.repository.FingerTemplateRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class FingerTemplateServiceImpl implements FingerTemplateService {

    private final FingerTemplateRepository fingerTemplateRepository;

    @Override
    public FingerTemplate create(FingerTemplate fingerTemplate) {
        return fingerTemplateRepository.save(fingerTemplate);
    }

    @Override
    public FingerTemplate update(FingerTemplate fingerTemplate) {
        return fingerTemplateRepository.save(fingerTemplate);
    }


    @Override
    public Optional<FingerTemplate> get(Long id) {
        FingerTemplate fingerTemplate;
        if (fingerTemplateRepository.findById(id).isPresent()) {
            fingerTemplate = fingerTemplateRepository.findById(id).get();
        } else {
            fingerTemplate = null;
        }
        return Optional.ofNullable(fingerTemplate);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<FingerTemplate> findAll(Pageable pageable) {
        return fingerTemplateRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        fingerTemplateRepository.deleteById(id);

    }
}
