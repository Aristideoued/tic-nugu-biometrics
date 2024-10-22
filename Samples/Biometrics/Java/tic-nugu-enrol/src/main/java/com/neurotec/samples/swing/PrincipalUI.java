/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.neurotec.samples.swing;

import com.neurotec.samples.Panel.PanelPrincipal;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

/**
 *
 * @author hp ZINA
 */
public class PrincipalUI  extends JFrame{
    
    
       
private JButton bouton = new JButton("bouton1");
private JMenuBar menuBar = new JMenuBar();
private JMenu test1 = new JMenu("Initialisation");
private JMenu test2 = new JMenu("Help");
private JMenu test3 = new JMenu("Enroller");
private JMenu test4 = new JMenu("Consulter");
private JMenu parametre = new JMenu("Paramètre");

private JMenu utilisateur = new JMenu("Utilisateur");



private JMenuItem item1 = new JMenuItem("A propos");
private JMenuItem item2 = new JMenuItem("Manuel");
private JMenuItem item3 = new JMenuItem("Lancer");
private JMenuItem item4 = new JMenuItem("Arrêter");

private JMenuItem item5 = new JMenuItem("Fonctionnaire");
private JMenuItem item6 = new JMenuItem("Non fonctionnaire");
private JMenuItem creer = new JMenuItem("nouveau utilisateur");
private JMenuItem listeUtilisateur = new JMenuItem("Consulter");
    
    public PrincipalUI(){
        
      //  JFrame fen = new JFrame();
this.setTitle("Systeme d'enrolement biometrique de l'ETAT");
this.setSize(800, 400);
//Nous demandons maintenant à notre objet de se positionner au centre
this.setLocationRelativeTo(null);
this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
this.setContentPane(new PanelPrincipal());

this.test1.add(item3);
this.test1.add(item2);

this.test2.add(item1);
//this.test2.add(item4);

this.test3.add(item5);
this.test3.add(item6);

this.menuBar.add(test1);
this.menuBar.add(test3);
//this.menuBar.add(test2);
this.menuBar.add(test4);
this.menuBar.add(parametre);

parametre.add(utilisateur);
//this.menuBar.add(utilisateur);
utilisateur.add(listeUtilisateur);
utilisateur.add(creer);

this.setJMenuBar(menuBar);


        item5.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
               new EnrollementUI();
            }
        });

        creer.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
               new CreationUtilisateurUI().setVisible(true);
            }
        });
         listeUtilisateur.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
              //****************  new ListeUserUI().setVisible(true);
            }
        });


this.setVisible(true);
    }
    
}
