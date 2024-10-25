package com.neurotec.samples.repository;

import com.neurotec.samples.model.FingerData;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface FingerDataRepository extends JpaRepository<FingerData, Long>, JpaSpecificationExecutor<FingerData> {
}
