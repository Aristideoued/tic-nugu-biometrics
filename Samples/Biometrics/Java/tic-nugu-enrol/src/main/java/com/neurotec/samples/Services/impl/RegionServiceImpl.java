package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.RegionService;
import com.neurotec.samples.model.Region;
import com.neurotec.samples.repository.RegionRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@AllArgsConstructor
public class RegionServiceImpl implements RegionService {

    private final RegionRepository regionRepository;

    @Override
    public Region create(Region region) {
        return regionRepository.save(region);
    }

    @Override
    public Region update(Region region) {
        return regionRepository.save(region);
    }


    @Override
    public Optional<Region> get(Long id) {
        Region region;
        if (regionRepository.findById(id).isPresent()) {
            region = regionRepository.findById(id).get();
        } else {
            region = null;
        }
        return Optional.ofNullable(region);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Region> findAll(Pageable pageable) {
        return regionRepository.findAll(pageable);
    }


    @Override
    public List<Region> findAll() {
        return regionRepository.findAll();
    }

    @Override
    @Transactional(readOnly = true)
    public List<Region> laListe() {
        return regionRepository.findAll();
    }

    @Override
    public void delete(Long id) {
        regionRepository.deleteById(id);

    }
}
