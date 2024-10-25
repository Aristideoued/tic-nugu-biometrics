package com.neurotec.samples.Services;

import com.neurotec.samples.model.IrisData;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface IrisDataService {

    IrisData create(IrisData irisData);

    IrisData update(IrisData irisData);

    Optional<IrisData> get(Long id);

    Page<IrisData> findAll(Pageable pageable);

    void delete(Long id);
}
