package com.neurotec.samples.Services.impl;

import com.neurotec.samples.Services.PhotoService;
import com.neurotec.samples.model.Photo;
import com.neurotec.samples.repository.PhotoRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class PhotoServiceImpl implements PhotoService {

    private final PhotoRepository photoRepository;

    @Override
    public Photo create(Photo photo) {
        return photoRepository.save(photo);
    }

    @Override
    public Photo update(Photo photo) {
        return photoRepository.save(photo);
    }


    @Override
    public Optional<Photo> get(Long id) {
        Photo photo;
        if (photoRepository.findById(id).isPresent()) {
            photo = photoRepository.findById(id).get();
        } else {
            photo = null;
        }
        return Optional.ofNullable(photo);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Photo> findAll(Pageable pageable) {
        return photoRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
        photoRepository.deleteById(id);

    }
}
