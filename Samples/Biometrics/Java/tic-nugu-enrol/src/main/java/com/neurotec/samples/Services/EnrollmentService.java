package com.neurotec.samples.Services;

import com.neurotec.samples.DAO.FingerPrintDAO;
import com.neurotec.samples.Domain.FingerPrint;

public class EnrollmentService {
    private FingerPrintDAO fingerPrintDAO = new FingerPrintDAO();


    public void saveEnrollement( FingerPrint fingerPrint) {
        // Enregistrer l'enrôlement dans PostgreSQL
       // enroleDAO.saveEnrole(enrole);
        // Enregistrer les empreintes dans MongoDB
        fingerPrintDAO.saveFingerPrint(fingerPrint);
    }
}
