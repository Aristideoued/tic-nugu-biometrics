package com.neurotec.samples.Services;

import com.neurotec.samples.model.FingerTemplate;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface FingerTemplateService {

    FingerTemplate create(FingerTemplate fingerTemplate);

    FingerTemplate update(FingerTemplate fingerTemplate);

    Optional<FingerTemplate> get(Long id);

    Page<FingerTemplate> findAll(Pageable pageable);

    void delete(Long id);
}
