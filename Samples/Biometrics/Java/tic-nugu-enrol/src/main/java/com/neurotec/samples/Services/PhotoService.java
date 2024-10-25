package com.neurotec.samples.Services;

import com.neurotec.samples.model.Photo;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface PhotoService {

    Photo create(Photo photo);

    Photo update(Photo photo);

    Optional<Photo> get(Long id);

    Page<Photo> findAll(Pageable pageable);

    void delete(Long id);
}
