package com.neurotec.samples.Services;


import com.neurotec.samples.model.InitiationKit;

import java.util.List;

public interface InitiationKitService {
    List<InitiationKit> getAllInitiationKits();
    InitiationKit create(InitiationKit initiationKit);
    InitiationKit updateInitiationKit(Long id,InitiationKit initiationKit);
    void deleteInitiationKit(Long id);
    InitiationKit getInitiationKitById(Long id);

}
