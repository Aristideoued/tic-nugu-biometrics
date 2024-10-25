package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.RecepisseService;
import com.neurotec.samples.model.Recepisse;
import com.neurotec.samples.repository.RecepisseRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class RecepisseServiceImpl implements RecepisseService {

    private final RecepisseRepository recepisseRepository;

    @Override
    public Recepisse create(Recepisse recepisse) {
        return recepisseRepository.save(recepisse);
    }

    @Override
    public Recepisse update(Recepisse recepisse) {
        return recepisseRepository.save(recepisse);
    }


    @Override
    public Optional<Recepisse> get(Long id) {
        Recepisse recepisse;
        if (recepisseRepository.findById(id).isPresent()) {
            recepisse = recepisseRepository.findById(id).get();
        } else {
            recepisse = null;
        }
        return Optional.ofNullable(recepisse);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Recepisse> findAll(Pageable pageable) {
        return recepisseRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        recepisseRepository.deleteById(id);

    }
}
