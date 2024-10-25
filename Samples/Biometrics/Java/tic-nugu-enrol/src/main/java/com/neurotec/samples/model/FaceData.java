/***********************************************************************
 * Module:  FaceData.java
 * Author:  hamid
 * Purpose: Defines the Class FaceData
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
public class FaceData extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private String id;
   private byte[] data;
   private String description;
   private String remoteID;
}