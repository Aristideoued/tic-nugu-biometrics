/***********************************************************************
 * Module:  Profil.java
 * Author:  hamid
 * Purpose: Defines the Class Profil
 ***********************************************************************/
package com.neurotec.samples.model;

public class Profil {
   private Long id;
   private String libelle;
   private String description;

   public Profil() {
   }
   public Profil(Long id, String libelle, String description) {}

   public Long getId() {
      return id;
   }

   public void setId(Long id) {
      this.id = id;
   }

   public String getLibelle() {
      return libelle;
   }

   public void setLibelle(String libelle) {
      this.libelle = libelle;
   }

   public String getDescription() {
      return description;
   }

   public void setDescription(String description) {
      this.description = description;
   }

   @Override
   public String toString() {
      return "Profil{" +
              "id=" + id +
              ", libelle='" + libelle + '\'' +
              ", description='" + description + '\'' +
              '}';
   }
}