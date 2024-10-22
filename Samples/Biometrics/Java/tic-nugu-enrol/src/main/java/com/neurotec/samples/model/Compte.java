/***********************************************************************
 * Module:  Compte.java
 * Author:  hamid
 * Purpose: Defines the Class Compte
 ***********************************************************************/
package com.neurotec.samples.model;

import java.sql.Timestamp;
import java.time.LocalDateTime;

public class Compte {
   private Long id;
   private String username;
   private String password;
   private Boolean flActivated;
   
   public Profil profil;
   public Utilisateur utilisateur;
   public Long profilID;

   private String createBy;
   private Timestamp createAt;

   private String deletedBy;
   private Timestamp deletedAt;
   private Timestamp updateAt;
   private String updateBy;

   public Compte() {
   }
   public Compte(Long profilId, Long utilisateurId, String username, String password, Boolean flActivated) {
      this.createAt = Timestamp.valueOf(LocalDateTime.now());
      this.createBy= "1100";
   }
   public Compte(
           Long profilId, Long utilisateurId, String username, String password,
           Boolean flActivated, String createBy, Timestamp createAt, String deletedBy, Timestamp deleteAt, String updateBy, Timestamp updateAt) {
            this.createAt = Timestamp.valueOf(LocalDateTime.now());
            this.createBy= "110";
   }

   public Long getId() {
      return id;
   }

   public void setId(Long id) {
      this.id = id;
   }

   public String getUsername() {
      return username;
   }

   public void setUsername(String username) {
      this.username = username;
   }

   public String getPassword() {
      return password;
   }

   public void setPassword(String password) {
      this.password = password;
   }

   public Boolean getFlActivated() {
      return flActivated;
   }

   public void setFlActivated(Boolean flActivated) {
      this.flActivated = flActivated;
   }

   public Utilisateur getUtilisateur() {
      return utilisateur;
   }

   public void setUtilisateur(Utilisateur utilisateur) {
      this.utilisateur = utilisateur;
   }

   public Profil getProfil() {
      return profil;
   }

   public void setProfil(Profil profil) {
      this.profil = profil;
   }

   public String getCreateBy() {
      return createBy;
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

   public Timestamp getUpdateAt() {
      return this.updateAt;
   }

   public void setUpdateBy(String updateBy) {
      this.updateBy = updateBy;
   }

   public String getUpdateBy() {
      return updateBy;
   }

   public void setCreateBy(String createBy) {
      this.createBy = createBy;
   }

   public void setUpdateAt(Timestamp updateAt) {
      this.updateAt = updateAt;
   }

   @Override
   public String toString() {
      return "Compte{" +
              "id=" + id +
              ", username='" + username + '\'' +
              ", password='" + password + '\'' +
              ", flActivated=" + flActivated +
              ", profil=" + profil +
              '}';
   }
}