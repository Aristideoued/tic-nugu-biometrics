/***********************************************************************
 * Module:  Carte.java
 * Author:  hamid
 * Purpose: Defines the Class Carte
 ***********************************************************************/
package com.neurotec.samples.model;

import lombok.*;

import javax.persistence.*;
import java.sql.Blob;
import java.util.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
public class Carte extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private String nip;
   private Integer matricule;
   private String nom;
   private String prenom;
   private String nomJF;
   private Date dateNaissance;
   private String lieuNaissance;
   private String sexe;
   private String emploi;
   @Lob
   private Blob signatureAgent;
   @Lob
   private Blob signatureAutorite;
   private String position;
   private Boolean fActive;
   private String motifDesactivation;
   private Date dateValidite;

   public Long getId() {
      return id;
   }

   public String getNip() {
      return nip;
   }

   public Integer getMatricule() {
      return matricule;
   }

   public String getNom() {
      return nom;
   }

   public String getPrenom() {
      return prenom;
   }

   public String getNomJF() {
      return nomJF;
   }

   public Date getDateNaissance() {
      return dateNaissance;
   }

   public String getLieuNaissance() {
      return lieuNaissance;
   }

   public String getSexe() {
      return sexe;
   }

   public String getEmploi() {
      return emploi;
   }

   public Blob getSignatureAgent() {
      return signatureAgent;
   }

   public Blob getSignatureAutorite() {
      return signatureAutorite;
   }

   public String getPosition() {
      return position;
   }

   public Boolean getfActive() {
      return fActive;
   }

   public String getMotifDesactivation() {
      return motifDesactivation;
   }

   public Date getDateValidite() {
      return dateValidite;
   }
}