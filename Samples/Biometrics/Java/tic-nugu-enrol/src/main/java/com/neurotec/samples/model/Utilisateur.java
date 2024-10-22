/***********************************************************************
 * Module:  Utilisateur.java
 * Author:  hamid
 * Purpose: Defines the Class Utilisateur
 ***********************************************************************/
package com.neurotec.samples.model;

import java.sql.Timestamp;
import java.time.LocalDateTime;

public class Utilisateur {
   private Long id;
   private String matricule;
   private String nom;
   private String prenom;
   private String telephone;
   private String email;
   private String createBy;
   private Timestamp createAt;

   private String deletedBy;
   private Timestamp deletedAt;
   private Timestamp updateAt;
   private String updateBy;
public Utilisateur(){}
   public Utilisateur(String matricule, String nom, String prenom, String telephone, String email) {
      this.matricule = matricule;
      this.nom = nom;
      this.prenom = prenom;
      this.telephone = telephone;
      this.email = email;
      //this.createAt = LocalDateTime.now();
      this.createBy= "1100";
      this.createAt = Timestamp.valueOf(LocalDateTime.now());
   }
   public Long getId() {
      return id;
   }

   public void setId(Long id) {
      this.id = id;
   }

   public String getMatricule() {
      return matricule;
   }

   public void setMatricule(String matricule) {
      this.matricule = matricule;
   }

   public String getNom() {
      return nom;
   }

   public void setNom(String nom) {
      this.nom = nom;
   }

   public String getPrenom() {
      return prenom;
   }

   public void setPrenom(String prenom) {
      this.prenom = prenom;
   }

   public String getTelephone() {
      return telephone;
   }

   public void setTelephone(String telephone) {
      this.telephone = telephone;
   }

   public String getEmail() {
      return email;
   }

   public void setEmail(String email) {
      this.email = email;
   }

   public String getCreateBy() {
      return createBy;
   }

   public void setCreateBy(String createBy) {
      this.createBy = createBy;
   }

   public void setUpdateAt(Timestamp updateAt) {
      this.updateAt = updateAt;
   }

   public Timestamp getCreateAt() {
      return createAt;
   }

   public void setCreateAt(Timestamp createAt) {
      this.createAt = createAt;
   }

   public String getDeletedBy() {
      return deletedBy;
   }

   public void setDeletedBy(String deletedBy) {
      this.deletedBy = deletedBy;
   }

   public Timestamp getDeletedAt() {
      return deletedAt;
   }

   public void setDeletedAt(Timestamp deletedAt) {
      this.deletedAt = deletedAt;
   }

   public void setUpdateAt(String createBy) {
      this.createBy = createBy;
   }

   public void setUpdateBy(String updateBy) {
      this.updateBy = updateBy;
   }

   public String getUpdateBy() {
      return updateBy;
   }
   @Override
   public String toString() {
      return "Utilisateur{" +
              "id=" + id +
              ", matricule='" + matricule + '\'' +
              ", nom='" + nom + '\'' +
              ", prenom='" + prenom + '\'' +
              ", telephone='" + telephone + '\'' +
              ", email='" + email + '\'' +
              '}';
   }
}