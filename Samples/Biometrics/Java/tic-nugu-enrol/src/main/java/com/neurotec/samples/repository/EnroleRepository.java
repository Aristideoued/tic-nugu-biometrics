package com.neurotec.samples.repository;

import com.neurotec.samples.model.Enrole;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface EnroleRepository extends JpaRepository<Enrole, Long>, JpaSpecificationExecutor<Enrole> {
}
