package com.neurotec.samples.repository;

import com.neurotec.samples.model.Recepisse;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface RecepisseRepository extends JpaRepository<Recepisse, Long>, JpaSpecificationExecutor<Recepisse> {
}
