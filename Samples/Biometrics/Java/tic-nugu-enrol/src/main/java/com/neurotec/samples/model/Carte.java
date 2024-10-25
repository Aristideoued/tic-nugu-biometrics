/***********************************************************************
 * Module:  Carte.java
 * Author:  hamid
 * Purpose: Defines the Class Carte
 ***********************************************************************/
package com.neurotec.samples.model;

import javax.persistence.*;
import lombok.*;
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

}