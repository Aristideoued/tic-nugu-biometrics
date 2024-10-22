/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.neurotec.samples.Panel;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.JPanel;

/**
 *
 * @author hp ZINA
 */
public class PanelPrincipal extends JPanel {
    
    
    
    private Image backgroundImage;

    // Constructeur pour charger l'image de fond
    public PanelPrincipal() {
        try {
            // Charge l'image depuis le fichier
            backgroundImage = ImageIO.read(new File("assets/biometrie.jpg"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
    // Appel à la méthode parent pour nettoyer le fond
        super.paintComponent(g);  

        // Définir un fond uni (par exemple, blanc ou une couleur similaire à celle de l'image)
        g.setColor(Color.WHITE);  
        g.fillRect(0, 0, getWidth(), getHeight());  

        // Dessine l'image de fond étendue pour couvrir tout le panneau
        if (backgroundImage != null) {
            g.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), this);
        }

        // Dessine du texte par-dessus l'image de fond
        Font font = new Font("Courier", Font.BOLD, 20);
        g.setFont(font);
        g.setColor(Color.WHITE);
        g.drawString("SYSTEME D'ENROLEMENT BIOMETRIQUE", 190, 20);
    }
}
