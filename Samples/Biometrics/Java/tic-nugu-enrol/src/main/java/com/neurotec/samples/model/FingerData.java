/***********************************************************************
 * Module:  FingerData.java
 * Author:  hamid
 * Purpose: Defines the Class FingerData
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
public class FingerData extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private String id;
   private String typeFinger;
   private Integer x;
   private Integer y;
}