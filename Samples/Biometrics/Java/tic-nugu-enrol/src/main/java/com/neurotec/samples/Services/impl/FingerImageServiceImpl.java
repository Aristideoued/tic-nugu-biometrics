package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.FingerImageService;
import com.neurotec.samples.model.FingerImage;
import com.neurotec.samples.repository.FingerImageRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import com.machinezoo.sourceafis.FingerprintImage;
import com.machinezoo.sourceafis.FingerprintMatcher;
import com.machinezoo.sourceafis.FingerprintTemplate;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
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
        return fingerImageRepository.findById(id);
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

    @Override
    public byte[] ImageToBytes(String imagePath) {
        try {
            return Files.readAllBytes(Paths.get(imagePath));
        } catch (IOException e) {
            throw new RuntimeException("Failed to read image bytes from path: " + imagePath, e);
        }
    }

    @Override
    public FingerprintImage bytesToImage(byte[] encodedImage) {
        return new FingerprintImage(encodedImage);
    }

    @Override
    public boolean comparerFingerImage(byte[] image1, byte[] image2) {
        // Transformation des images en templates
        FingerprintTemplate template1 = new FingerprintTemplate(new FingerprintImage(image1));
        FingerprintTemplate template2 = new FingerprintTemplate(new FingerprintImage(image2));

        // Comparaison des empreintes
        double score = new FingerprintMatcher(template1).match(template2);

        // Définir un seuil pour déterminer la correspondance
        return score >= 40;  // Le seuil peut être ajusté selon les besoins
    }
}