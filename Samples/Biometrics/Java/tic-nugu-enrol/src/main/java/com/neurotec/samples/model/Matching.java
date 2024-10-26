/***********************************************************************
 * Module:  Matching.java
 * Author:  hamid
 * Purpose: Defines the Class Matching
 ***********************************************************************/
package com.neurotec.samples.model;


import lombok.*;

import javax.persistence.*;
import java.util.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
public class Matching extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private Date dateDebut;
   private Date dateFin;
   private Long idPrincipal;
   private Long idSecondaire;
   private Double score;
   private Double score2;
   private Boolean supprime;
   private Date dateSuppressio;
   private String commentaire;
}