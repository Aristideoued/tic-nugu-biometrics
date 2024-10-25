package com.neurotec.samples.repository;

import com.neurotec.samples.model.Etat;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface EtatRepository extends JpaRepository<Etat, Long>, JpaSpecificationExecutor<Etat> {
}
