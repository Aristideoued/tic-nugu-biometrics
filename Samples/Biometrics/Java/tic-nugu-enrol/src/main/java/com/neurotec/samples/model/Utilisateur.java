/***********************************************************************
 * Module:  Utilisateur.java
 * Author:  hamid
 * Purpose: Defines the Class Utilisateur
 ***********************************************************************/
package com.neurotec.samples.model;


import lombok.*;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
public class Utilisateur extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private String matricule;
   private String nom;
   private String prenom;
   private String telephone;
   private String email;

   public Utilisateur(String matricule, String nom, String prenom, String telephone, String email) {
      super();
   }
}