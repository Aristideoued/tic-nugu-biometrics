/***********************************************************************
 * Module:  Recepisse.java
 * Author:  hamid
 * Purpose: Defines the Class Recepisse
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
public class Recepisse extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private Long id;
   private String numeroRecepisse;
   private Date dateRecepisse;
}