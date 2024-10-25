package com.neurotec.samples.Services;

import com.neurotec.samples.model.FingerPrint;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface FingerPrintService {

    FingerPrint create(FingerPrint fingerPrint);

    FingerPrint update(FingerPrint fingerPrint);

    Optional<FingerPrint> get(Long id);

    Page<FingerPrint> findAll(Pageable pageable);

    void delete(Long id);
}
