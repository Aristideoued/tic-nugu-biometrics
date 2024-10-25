package com.neurotec.samples.Services;

import com.neurotec.samples.model.FaceData;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface FaceDataService {

    FaceData create(FaceData faceData);

    FaceData update(FaceData faceData);

    Optional<FaceData> get(String id);

    Page<FaceData> findAll(Pageable pageable);

    void delete(String id);
}
