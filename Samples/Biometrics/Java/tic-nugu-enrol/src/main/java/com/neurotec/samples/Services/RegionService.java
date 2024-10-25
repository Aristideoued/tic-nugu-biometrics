package com.neurotec.samples.Services;



import com.neurotec.samples.model.Region;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;
import java.util.Optional;

public interface RegionService {

    Region create(Region regionModel);

    Region update(Region region);

    Optional<Region> get(Long id);

    Page<Region> findAll(Pageable pageable);
    List<Region> laListe();

    List<Region> findAll();

    void delete(Long id);
}
