package com.neurotec.samples.repository;


import com.neurotec.samples.model.Kit;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface KitRepository extends JpaRepository<Kit, Long>, JpaSpecificationExecutor<Kit> {
}
