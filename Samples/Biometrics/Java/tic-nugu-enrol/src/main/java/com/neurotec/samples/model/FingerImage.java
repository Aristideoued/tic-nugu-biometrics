/***********************************************************************
 * Module:  FingerImage.java
 * Author:  hamid
 * Purpose: Defines the Class FingerImage
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
public class FingerImage extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private String id;
   private byte[] data;
}