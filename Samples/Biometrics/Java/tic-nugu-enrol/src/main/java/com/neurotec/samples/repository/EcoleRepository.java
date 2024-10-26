package com.neurotec.samples.repository;


import com.neurotec.samples.model.Ecole;
import com.neurotec.samples.model.Province;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface EcoleRepository extends JpaRepository<Ecole, Long>, JpaSpecificationExecutor<Ecole> {
    List<Ecole> findEcolesByProvince(Province province);
}
