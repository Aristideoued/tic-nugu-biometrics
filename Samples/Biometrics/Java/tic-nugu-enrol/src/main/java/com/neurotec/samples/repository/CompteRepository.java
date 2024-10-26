package com.neurotec.samples.repository;

import com.neurotec.samples.model.Compte;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface CompteRepository extends JpaRepository<Compte, Long>, JpaSpecificationExecutor<Compte> {

    Optional<Compte> findCompteByUsername(String username);
    List<Compte> findByFlActivatedTrue();
}
