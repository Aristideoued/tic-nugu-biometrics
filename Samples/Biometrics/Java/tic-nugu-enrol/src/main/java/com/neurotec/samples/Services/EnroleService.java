package com.neurotec.samples.Services;

import com.neurotec.samples.model.Enrole;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface EnroleService {

    Enrole create(Enrole enrole);

    Enrole update(Enrole enrole);

    Optional<Enrole> get(Long id);

    Page<Enrole> findAll(Pageable pageable);

    void delete(Long id);
}
