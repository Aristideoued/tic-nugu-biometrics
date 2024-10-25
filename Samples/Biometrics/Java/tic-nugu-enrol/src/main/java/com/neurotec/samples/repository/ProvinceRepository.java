package com.neurotec.samples.repository;


import java.util.List;

import com.neurotec.samples.model.Province;
import com.neurotec.samples.model.Region;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface ProvinceRepository extends JpaRepository<Province, Long>, JpaSpecificationExecutor<Province> {

    List<Province> findProvinceByRegion(Region region);
}
