package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.EcoleService;
import com.neurotec.samples.model.Ecole;
import com.neurotec.samples.model.Province;
import com.neurotec.samples.repository.EcoleRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@AllArgsConstructor
public class EcoleServiceImpl implements EcoleService {

    private final EcoleRepository ecoleRepository;

    @Override
    public Ecole create(Ecole ecole) {
        return ecoleRepository.save(ecole);
    }

    @Override
    public Ecole update(Ecole ecole) {
        return ecoleRepository.save(ecole);
    }


    @Override
    public Optional<Ecole> get(Long id) {
        Ecole ecole;
        if (ecoleRepository.findById(id).isPresent()) {
            ecole = ecoleRepository.findById(id).get();
        } else {
            ecole = null;
        }
        return Optional.ofNullable(ecole);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Ecole> findAll(Pageable pageable) {
        return ecoleRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        ecoleRepository.deleteById(id);

    }

    @Override
    public List<Ecole> findEcolesByProvinces(Province province) {
        return ecoleRepository.findEcolesByProvince(province);
    }
}
