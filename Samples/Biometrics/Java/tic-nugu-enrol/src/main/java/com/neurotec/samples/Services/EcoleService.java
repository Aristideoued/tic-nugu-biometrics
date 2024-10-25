package com.neurotec.samples.Services;


import com.neurotec.samples.model.Ecole;
import com.neurotec.samples.model.Province;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;
import java.util.Optional;

public interface EcoleService {

    Ecole create(Ecole ecole);

    Ecole update(Ecole ecole);

    Optional<Ecole> get(Long id);

    Page<Ecole> findAll(Pageable pageable);

    void delete(Long id);

    List<Ecole> findEcolesByProvinces(Province province);
}
