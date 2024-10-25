package com.neurotec.samples.repository;

import com.neurotec.samples.model.FingerPrint;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface FingerPrintRepository extends JpaRepository<FingerPrint, Long>, JpaSpecificationExecutor<FingerPrint> {
}
