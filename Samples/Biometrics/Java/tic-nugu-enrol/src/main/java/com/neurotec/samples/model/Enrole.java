/***********************************************************************
 * Module:  Enrole.java
 * Author:  hamid
 * Purpose: Defines the Class Enrole
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
public class Enrole extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private String nip;
   private String refPiece;
   private String typePiece;
   private Integer matricule;
   private String nom;
   private String prenom;
   private String nomJF;
   private String telephone;
   private String mail;
   private Date dateNaissance;
   private String lieuNaissance;
   private String sexe;
   private Date dateEnrolement;
   private Boolean statusMatch;
   private Boolean doublon;
   private Boolean supprime;
   private String motifSuppression;
   private Date dateSuppresion;
   private Boolean valide;
   private Date dateValidation;
   private Integer nbrCarte;
   private Boolean fSynchronise;
   private Date dateSync;
   private byte[] signature;

   @OneToMany
   public java.util.Collection<FingerPrint> fingerPrint;
   @OneToMany
   public java.util.Collection<IrisData> irisData;
   @OneToMany
   public java.util.Collection<FaceData> faceData;
   @OneToMany
   public java.util.Collection<Photo> photo;
   @OneToMany
   public java.util.Collection<Carte> carte;
   @OneToMany
   public java.util.Collection<Recepisse> recepisse;
   @ManyToOne
   public Compte compte;
   @ManyToOne
   public Kit kit;

}