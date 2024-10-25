package com.neurotec.samples.repository;

import com.neurotec.samples.model.IrisData;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface IrisDataRepository extends JpaRepository<IrisData, Long>, JpaSpecificationExecutor<IrisData> {
}
