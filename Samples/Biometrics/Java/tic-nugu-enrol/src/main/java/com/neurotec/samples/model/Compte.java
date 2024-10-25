/***********************************************************************
 * Module:  Compte.java
 * Author:  hamid
 * Purpose: Defines the Class Compte
 ***********************************************************************/
package com.neurotec.samples.model;

import lombok.*;

import javax.persistence.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
public class Compte extends CommonEntity {

   private static final long serialVersionUID = 7348866761268888347L;

   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private String username;
   private String password;
   private boolean flActivated;

   @ManyToOne
   public Profil profil;
   @ManyToOne(cascade = CascadeType.ALL)
   public Utilisateur utilisateur;
}