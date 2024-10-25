package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.FingerImageService;
import com.neurotec.samples.model.FingerImage;
import com.neurotec.samples.repository.FingerImageRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class FingerImageServiceImpl implements FingerImageService {

    private final FingerImageRepository fingerImageRepository;

    @Override
    public FingerImage create(FingerImage fingerImage) {
        return fingerImageRepository.save(fingerImage);
    }

    @Override
    public FingerImage update(FingerImage fingerImage) {
        return fingerImageRepository.save(fingerImage);
    }


    @Override
    public Optional<FingerImage> get(Long id) {
        FingerImage fingerImage;
        if (fingerImageRepository.findById(id).isPresent()) {
            fingerImage = fingerImageRepository.findById(id).get();
        } else {
            fingerImage = null;
        }
        return Optional.ofNullable(fingerImage);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<FingerImage> findAll(Pageable pageable) {
        return fingerImageRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        fingerImageRepository.deleteById(id);

    }
}
