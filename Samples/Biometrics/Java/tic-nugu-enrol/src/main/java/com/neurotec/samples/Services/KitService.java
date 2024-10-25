package com.neurotec.samples.Services;

import com.neurotec.samples.model.Kit;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;
import java.util.Optional;

public interface KitService {

    Kit create(Kit kit);

    Kit update(Kit kit);

    Optional<Kit> get(Long id);

    Page<Kit> findAll(Pageable pageable);

    List<Kit> findAll();

    void delete(Long id);
}
