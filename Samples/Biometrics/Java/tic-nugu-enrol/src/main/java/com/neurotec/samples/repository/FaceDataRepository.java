package com.neurotec.samples.repository;

import com.neurotec.samples.model.FaceData;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface FaceDataRepository extends JpaRepository<FaceData, String>, JpaSpecificationExecutor<FaceData> {
}
