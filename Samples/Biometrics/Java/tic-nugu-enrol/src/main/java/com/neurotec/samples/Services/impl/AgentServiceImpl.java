package com.neurotec.samples.Services.impl;


import com.neurotec.samples.Services.AgentService;
import com.neurotec.samples.model.Agent;
import com.neurotec.samples.repository.AgentRepository;
import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;

@Service
@AllArgsConstructor
public class AgentServiceImpl implements AgentService {
    
    private final AgentRepository agentRepository;

    @Override
    public Agent create(Agent agent) {
        return agentRepository.save(agent);
    }

    @Override
    public Agent update(Agent agent) {
        return agentRepository.save(agent);
    }

    
    @Override
    public Optional<Agent> get(Long id) {
        Agent agent;
        if (agentRepository.findById(id).isPresent()) {
            agent = agentRepository.findById(id).get();
        } else {
            agent = null;
        }
        return Optional.ofNullable(agent);

    }

    @Override
    @Transactional(readOnly = true)
    public Page<Agent> findAll(Pageable pageable) {
        return agentRepository.findAll(pageable);
    }

    @Override
    public void delete(Long id) {
            agentRepository.deleteById(id);

    }

}
