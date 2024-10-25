package com.neurotec.samples.Services;


import com.neurotec.samples.model.Agent;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.Optional;

public interface AgentService {

    Agent create(Agent agent);

    Agent update(Agent agent);

    Optional<Agent> get(Long id);

    Page<Agent> findAll(Pageable pageable);

    void delete(Long id);
}
