package com.neurotec.samples.Services;


import com.neurotec.samples.model.Province;
import com.neurotec.samples.model.Region;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;
import java.util.Optional;

public interface ProvinceService {

    Province create(Province province);

    Province update(Province province);

    Optional<Province> get(Long id);

    Page<Province> findAll(Pageable pageable);

    List<Province> findProvincesByRegion(Region region);
    List<Province> findProvinceByRegion(Region region);

    void delete(Long id);
}
