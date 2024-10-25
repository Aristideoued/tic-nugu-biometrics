package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.IrisDataService;
import com.neurotec.samples.model.IrisData;
import com.neurotec.samples.repository.IrisDataRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class IrisDataServiceImpl implements IrisDataService {

    private final IrisDataRepository irisDataRepository;

    @Override
    public IrisData create(IrisData irisData) {
        return irisDataRepository.save(irisData);
    }

    @Override
    public IrisData update(IrisData irisData) {
        return irisDataRepository.save(irisData);
    }


    @Override
    public Optional<IrisData> get(Long id) {
        IrisData irisData;
        if (irisDataRepository.findById(id).isPresent()) {
            irisData = irisDataRepository.findById(id).get();
        } else {
            irisData = null;
        }
        return Optional.ofNullable(irisData);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<IrisData> findAll(Pageable pageable) {
        return irisDataRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        irisDataRepository.deleteById(id);

    }
}
