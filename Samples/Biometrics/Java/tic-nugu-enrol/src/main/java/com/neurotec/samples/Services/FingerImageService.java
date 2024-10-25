package com.neurotec.samples.Services;

import com.neurotec.samples.model.FingerImage;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface FingerImageService {

    FingerImage create(FingerImage fingerImage);

    FingerImage update(FingerImage fingerImage);

    Optional<FingerImage> get(Long id);

    Page<FingerImage> findAll(Pageable pageable);

    void delete(Long id);
}
