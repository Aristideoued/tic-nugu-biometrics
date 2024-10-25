package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.KitService;
import com.neurotec.samples.model.Kit;
import com.neurotec.samples.repository.KitRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@AllArgsConstructor
public class KitServiceImpl implements KitService {

    private final KitRepository kitRepository;

    @Override
    public Kit create(Kit kit) {
        return kitRepository.save(kit);
    }

    @Override
    public Kit update(Kit kit) {
        return kitRepository.save(kit);
    }


    @Override
    public Optional<Kit> get(Long id) {
        Kit kit;
        if (kitRepository.findById(id).isPresent()) {
            kit = kitRepository.findById(id).get();
        } else {
            kit = null;
        }
        return Optional.ofNullable(kit);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Kit> findAll(Pageable pageable) {
        return kitRepository.findAll(pageable);
    }

    @Override
    @Transactional(readOnly = true)
    public List<Kit> findAll() {
        return kitRepository.findAll();
    }

    @Override
    public void delete(Long id) {
        kitRepository.deleteById(id);

    }
}
