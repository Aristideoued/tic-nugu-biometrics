package com.neurotec.samples.repository;

import com.neurotec.samples.model.Matching;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface MatchingRepository extends JpaRepository<Matching, Long>, JpaSpecificationExecutor<Matching> {
}
