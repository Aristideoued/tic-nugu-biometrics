package com.neurotec.samples.Services.impl;

import com.neurotec.samples.Services.InitiationKitService;
import com.neurotec.samples.model.InitiationKit;
import com.neurotec.samples.repository.InitiationKitRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class InitiationKitImpl implements InitiationKitService {

    @Autowired
    private InitiationKitRepository initiationKitRepository;

    public InitiationKit create(InitiationKit initiationKit) {
        return initiationKitRepository.save(initiationKit);
    }

    @Override
    public InitiationKit updateInitiationKit(Long id, InitiationKit initiationKit) {
        Optional<InitiationKit> existingInitiationKit = initiationKitRepository.findById(id);
        if (existingInitiationKit.isPresent()) {
            InitiationKit kitToUpdate = existingInitiationKit.get();
            kitToUpdate.setObservations(initiationKit.getObservations());
            kitToUpdate.setKit(initiationKit.getKit());
            kitToUpdate.setEcole(initiationKit.getEcole());
            return initiationKitRepository.save(kitToUpdate);
        } else {
            throw new RuntimeException("InitiationKit not found with id: " + id);
        }
    }

    @Override
    public void deleteInitiationKit(Long id) {
        initiationKitRepository.deleteById(id);
    }


    @Override
    public List<InitiationKit> getAllInitiationKits() {
        return initiationKitRepository.findAll();
    }

    public InitiationKit getInitiationKitById(Long id) {
        return initiationKitRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("InitiationKit not found with id: " + id));
    }
}
