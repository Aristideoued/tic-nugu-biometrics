package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.FingerTemplateService;
import com.neurotec.samples.model.FingerTemplate;
import com.neurotec.samples.repository.FingerTemplateRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.machinezoo.sourceafis.FingerprintImage;
import com.machinezoo.sourceafis.FingerprintMatcher;
import com.machinezoo.sourceafis.FingerprintTemplate;

import java.util.Optional;
import java.util.List;


@Service
@AllArgsConstructor
public class FingerTemplateServiceImpl implements FingerTemplateService {

    private final FingerTemplateRepository fingerTemplateRepository;

    @Override
    public FingerTemplate creer(FingerTemplate fingerTemplate) {
        return fingerTemplateRepository.save(fingerTemplate);
    }

    @Override
    public FingerTemplate update(FingerTemplate fingerTemplate) {
        return fingerTemplateRepository.save(fingerTemplate);
    }


    @Override
    public Optional<FingerTemplate> findById(Long id) {
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
    public List<FingerTemplate> getAllFingerTemplates() {
        return fingerTemplateRepository.findAll();
    }

    @Override
    public void delete(Long id) {
        fingerTemplateRepository.deleteById(id);

    }
    @Override
    public byte[] templateToBytes(FingerprintTemplate template) {
        return template.toByteArray();
    }

    // Méthode pour reconstruire un FingerprintTemplate à partir d'un tableau d'octets
    @Override
    public  FingerprintTemplate bytesToTemplate(byte[] encodedTemplate) {
        return new FingerprintTemplate(encodedTemplate);
    }
    @Override
    public FingerprintTemplate creerTemplate(byte[] image) {
        FingerprintTemplate template = new FingerprintTemplate(new FingerprintImage(image));
        return template;
    }
    @Override
    public boolean comparerFingerTemplateBoolean(FingerprintTemplate template1 , FingerprintTemplate template2 ) {

        double score = new FingerprintMatcher(template1).match(template2);
        return score >= 40;  // Le seuil peut être ajusté selon les besoins
    }
    @Override
    public double comparerFingerTemplateScore(FingerprintTemplate template1 , FingerprintTemplate template2 ) {

        double score = new FingerprintMatcher(template1).match(template2);
        return score ;
    }

}