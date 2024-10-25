/***********************************************************************
 * Module:  Kit.java
 * Author:  hamid
 * Purpose: Defines the Class Kit
 ***********************************************************************/
package com.neurotec.samples.model;

import javax.persistence.*;

import lombok.*;

import java.util.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
public class Kit extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private String numeroKit;
   private String etatKit;
   private String typeKit;
   private Date miseEnService;
   private String numeroSerie;
   private Date dateRebut;
}