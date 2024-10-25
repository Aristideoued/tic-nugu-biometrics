package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.ProvinceService;
import com.neurotec.samples.model.Province;
import com.neurotec.samples.model.Region;
import com.neurotec.samples.repository.ProvinceRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@AllArgsConstructor
public class ProvinceServiceImpl implements ProvinceService {

    private final ProvinceRepository provinceRepository;

    @Override
    public Province create(Province province) {
        return provinceRepository.save(province);
    }

    @Override
    public Province update(Province province) {
        return provinceRepository.save(province);
    }


    @Override
    public Optional<Province> get(Long id) {
        Province province;
        if (provinceRepository.findById(id).isPresent()) {
            province = provinceRepository.findById(id).get();
        } else {
            province = null;
        }
        return Optional.ofNullable(province);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Province> findAll(Pageable pageable) {
        return provinceRepository.findAll(pageable);
    }

    @Override
    public List<Province> findProvincesByRegion(Region region) {
        return provinceRepository.findProvinceByRegion(region);
    }


    @Override
    public void delete(Long id) {
        provinceRepository.deleteById(id);

    }

    @Override
    public List<Province> findProvinceByRegion(Region region) {
        return provinceRepository.findProvinceByRegion(region);
    }
}
