/***********************************************************************
 * Module:  FingerPrint.java
 * Author:  hamid
 * Purpose: Defines the Class FingerPrint
 ***********************************************************************/
package com.neurotec.samples.model;

import javax.persistence.*;
import lombok.*;
import java.util.List;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
public class FingerPrint extends CommonEntity {
   private static final long serialVersionUID = 7348866761268888347L;
   @Id
   @GeneratedValue(strategy = GenerationType.AUTO)
   private String id;
   private String main;
   private String doigt;
   private String commentaire;
   private String remoteID;
   @OneToMany
   public List<FingerData> fingerData;
   @OneToMany
   public List<FingerTemplate> fingerTemplate;
   @OneToMany
   public List<FingerImage> fingerImage;
}