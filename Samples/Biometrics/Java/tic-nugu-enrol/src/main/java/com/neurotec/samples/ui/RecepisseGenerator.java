/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.neurotec.samples.ui;

import com.itextpdf.text.Document;
import com.itextpdf.text.DocumentException;
import com.itextpdf.text.Paragraph;
import com.itextpdf.text.pdf.PdfWriter;
import com.neurotec.samples.model.Agent;


import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;


/**
 *
 * @author Canisius <canisiushien@gmail.com>
 */
public class RecepisseGenerator {
    
    public static void generateReceiptPDF(Long idAgent) throws IOException {
        Document document = new Document();
        String docName = "recipisse_" + idAgent + ".pdf";
        try {
            // Création du fichier PDF
            PdfWriter.getInstance(document, new FileOutputStream(docName));
            java.awt.Desktop.getDesktop().open(new File(docName));//on ouvre automatiquement le doc generé avec le lecteur pdf par defaut du system
            document.open();//actuellement le fichier est généré et stocké dans le projet

            // Formatage de la date
            SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
            SimpleDateFormat formatter2 = new SimpleDateFormat("dd/MM/yyyy");
            Date date = new Date();
            //initialisation des infos. ????????????????a recuperer plus tard en bd
            Agent agent = new Agent();
            agent.setMatricule(371267);
            agent.setDateNaissance(date);
            agent.setLieuNaissance("DANO");
            agent.setMail("canisius.hien@fonction-publique.gov.bf");
            agent.setNip("0123456789785");
            agent.setNom("HIEN");
            agent.setPrenom("Zilèdem Pierre Canisius");
            agent.setSexe("M");
            agent.setTelephone("(+226)70612916");
            agent.setNumeroCNIB("B14902600");

            // Contenu du récépissé
            document.add(new Paragraph("RECEPISSE D'ENROLEMENT BIOMETRIQUE"));
            document.add(new Paragraph("========================================"));
            document.add(new Paragraph("Matricule : " + agent.getMatricule()));
            document.add(new Paragraph("Nom : " + agent.getNom()));
            document.add(new Paragraph("Prenom : " + agent.getPrenom()));
            document.add(new Paragraph("Date de naissance : " + formatter2.format(agent.getDateNaissance())));
            document.add(new Paragraph("Lieu de naissance : " + agent.getLieuNaissance()));
            document.add(new Paragraph("Téléphone : " + agent.getTelephone()));
            document.add(new Paragraph("Email : " + agent.getMail()));
            document.add(new Paragraph("----------------------------"));
            document.add(new Paragraph("Date d'enrolement : " + formatter.format(date)));
            
        } catch (DocumentException | FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            document.close();
        }
    }
}
