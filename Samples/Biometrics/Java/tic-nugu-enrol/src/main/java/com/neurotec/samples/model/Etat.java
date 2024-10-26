/***********************************************************************
 * Module:  Etat.java
 * Author:  hamid
 * Purpose: Defines the Class Etat
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
public class Etat extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private String libelle;
   private String description;
}