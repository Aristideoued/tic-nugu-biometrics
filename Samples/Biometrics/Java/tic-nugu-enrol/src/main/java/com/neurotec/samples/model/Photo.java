/***********************************************************************
 * Module:  Photo.java
 * Author:  hamid
 * Purpose: Defines the Class Photo
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
public class Photo extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private String id;
   private byte[] data;
   private String remoteID;
}