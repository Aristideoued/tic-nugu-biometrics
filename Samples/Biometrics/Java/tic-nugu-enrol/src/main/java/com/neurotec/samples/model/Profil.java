/***********************************************************************
 * Module:  Profil.java
 * Author:  hamid
 * Purpose: Defines the Class Profil
 ***********************************************************************/
package com.neurotec.samples.model;

import javax.persistence.*;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
public class Profil extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private String libelle;
   private String description;

}