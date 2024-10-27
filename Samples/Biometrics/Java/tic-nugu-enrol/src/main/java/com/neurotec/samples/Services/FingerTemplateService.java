package com.neurotec.samples.Services;
import com.neurotec.samples.model.FingerTemplate;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import com.machinezoo.sourceafis.FingerprintTemplate;

import java.util.List;
import java.util.Optional;

public interface FingerTemplateService {

    /**
     * Create a new FingerTemplate.
     */
    FingerTemplate creer(FingerTemplate fingerTemplate);
    // FingerprintTemplate creerTemplate(byte[] image);
    /**
     * Update an existing FingerTemplate.
     */
    FingerTemplate update(FingerTemplate fingerTemplate);

    /**
     * Find a FingerTemplate by its ID.
     */
    Optional<FingerTemplate> findById(Long id);

    /**
     * Retrieve a pageable list of all FingerTemplates.
     */
    Page<FingerTemplate> findAll(Pageable pageable);

    /**
     * Get all FingerTemplates in a list.
     */
    List<FingerTemplate> getAllFingerTemplates();

    /**
     * Delete a FingerTemplate by its ID.
     */
    void delete(Long id);

    /**
     * Convert a FingerprintTemplate to a byte array.
     */
    byte[] templateToBytes(FingerprintTemplate template);

    /**
     * Convert a byte array to a FingerprintTemplate.
     */
    FingerprintTemplate bytesToTemplate(byte[] templateBinary);

    /**
     * Create a FingerprintTemplate from a binary image.
     */
    FingerprintTemplate creerTemplate(byte[] binaryImage);

    /**
     * Compare two FingerprintTemplates and return a boolean match result.
     */
    boolean comparerFingerTemplateBoolean(FingerprintTemplate template1, FingerprintTemplate template2);

    /**
     * Compare two FingerprintTemplates and return a score.
     */
    double comparerFingerTemplateScore(FingerprintTemplate template1 , FingerprintTemplate template2);
}