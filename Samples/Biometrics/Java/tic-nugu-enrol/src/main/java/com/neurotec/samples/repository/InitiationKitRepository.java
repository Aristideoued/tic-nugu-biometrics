package com.neurotec.samples.repository;

import com.neurotec.samples.model.InitiationKit;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;

public interface InitiationKitRepository extends JpaRepository<InitiationKit, Long>, JpaSpecificationExecutor<InitiationKit> {
}
