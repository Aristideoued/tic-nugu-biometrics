package com.neurotec.samples.controller;



import com.neurotec.samples.Services.FingerTemplateService;
import com.neurotec.samples.model.FingerTemplate;
import lombok.Data;

import lombok.var;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;

import com.machinezoo.sourceafis.FingerprintMatcher;
import com.machinezoo.sourceafis.FingerprintTemplate;
import java.util.List;
import java.util.Optional;
@Data
@Controller
public class FingerTemplateController {



    private final FingerTemplateService templateService;
    // private final FingerTemplateUI tempplateUI;

    @Autowired
    public FingerTemplateController(FingerTemplateService templateService) {
        this.templateService = templateService;

    }

    public Optional<FingerTemplate> getTemplate(Long id) {
        return templateService.findById(id);
    }

    public FingerTemplate dedoublonnage(FingerTemplate sonde) {
        FingerprintTemplate sondeTemp = templateService.bytesToTemplate(sonde.getData());
        List<FingerTemplate> candidates = templateService.getAllFingerTemplates();
        var matcher = new FingerprintMatcher(sondeTemp);
        FingerTemplate match = null;
        double max = Double.NEGATIVE_INFINITY;

        for (var candidate : candidates) {
            double similarity = matcher.match(templateService.bytesToTemplate(candidate.getData()));
            if (similarity > max) {
                max = similarity;
                match = candidate;
            }
        }

        double threshold = 40;
        return max >= threshold ? match : null;
    }
}

