package com.neurotec.samples.repository;

import com.neurotec.samples.model.Carte;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface CarteRepository extends JpaRepository<Carte, Long>, JpaSpecificationExecutor<Carte> {
}
