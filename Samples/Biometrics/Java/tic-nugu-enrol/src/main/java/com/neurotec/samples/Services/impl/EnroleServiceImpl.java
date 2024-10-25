package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.EnroleService;
import com.neurotec.samples.model.Enrole;
import com.neurotec.samples.repository.EnroleRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class EnroleServiceImpl implements EnroleService {

    private final EnroleRepository enroleRepository;

    @Override
    public Enrole create(Enrole enrole) {
        return enroleRepository.save(enrole);
    }

    @Override
    public Enrole update(Enrole enrole) {
        return enroleRepository.save(enrole);
    }


    @Override
    public Optional<Enrole> get(Long id) {
        Enrole enrole;
        if (enroleRepository.findById(id).isPresent()) {
            enrole = enroleRepository.findById(id).get();
        } else {
            enrole = null;
        }
        return Optional.ofNullable(enrole);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Enrole> findAll(Pageable pageable) {
        return enroleRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        enroleRepository.deleteById(id);

    }
}
