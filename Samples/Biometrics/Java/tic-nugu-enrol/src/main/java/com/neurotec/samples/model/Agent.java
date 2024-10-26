/***********************************************************************
 * Module:  Agent.java
 * Author:  hamid
 * Purpose: Defines the Class Agent
 ***********************************************************************/

package com.neurotec.samples.model;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

import javax.persistence.*;
import java.util.Date;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
@Table(name = "agent")
public class Agent extends CommonEntity {
     
    private static final long serialVersionUID = 7348866761268888347L;

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String nip;
    private String numeroCNIB;
    private String source;
    private int matricule;
    private String nom;
    private String prenom;
    private String nomJF;
    private String telephone;
    private String mail;
    private Date dateNaissance;
    private String lieuNaissance;
    private String sexe;

}
