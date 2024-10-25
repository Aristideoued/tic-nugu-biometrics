package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.FaceDataService;
import com.neurotec.samples.model.FaceData;
import com.neurotec.samples.repository.FaceDataRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class FaceDataServiceImpl implements FaceDataService {

    private final FaceDataRepository faceDataRepository;

    @Override
    public FaceData create(FaceData faceData) {
        return faceDataRepository.save(faceData);
    }

    @Override
    public FaceData update(FaceData faceData) {
        return faceDataRepository.save(faceData);
    }


    @Override
    public Optional<FaceData> get(String id) {
        FaceData faceData;
        if (faceDataRepository.findById(id).isPresent()) {
            faceData = faceDataRepository.findById(id).get();
        } else {
            faceData = null;
        }
        return Optional.ofNullable(faceData);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<FaceData> findAll(Pageable pageable) {
        return faceDataRepository.findAll(pageable);
    }

    @Override
    public void delete(String id) {
        faceDataRepository.deleteById(id);

    }
}
