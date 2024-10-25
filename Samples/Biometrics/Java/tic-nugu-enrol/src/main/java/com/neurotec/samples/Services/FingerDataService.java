package com.neurotec.samples.Services;

import com.neurotec.samples.model.FingerData;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface FingerDataService {

    FingerData create(FingerData fingerData);

    FingerData update(FingerData fingerData);

    Optional<FingerData> get(Long id);

    Page<FingerData> findAll(Pageable pageable);

    void delete(Long id);
}
