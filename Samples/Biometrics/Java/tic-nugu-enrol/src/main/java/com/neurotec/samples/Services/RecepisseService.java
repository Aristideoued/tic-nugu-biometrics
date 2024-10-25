package com.neurotec.samples.Services;

import com.neurotec.samples.model.Recepisse;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface RecepisseService {

    Recepisse create(Recepisse recepisse);

    Recepisse update(Recepisse recepisse);

    Optional<Recepisse> get(Long id);

    Page<Recepisse> findAll(Pageable pageable);

    void delete(Long id);
}
