package com.neurotec.samples.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;
import com.neurotec.samples.model.FingerTemplate;

@Repository
public interface FingerTemplateRepository extends JpaRepository<FingerTemplate, Long>, JpaSpecificationExecutor<FingerTemplate> {
}
