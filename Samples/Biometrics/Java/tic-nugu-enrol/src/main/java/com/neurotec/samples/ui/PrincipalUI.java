
package com.neurotec.samples.ui;

import javax.imageio.ImageIO;
import javax.swing.*;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.Objects;
import java.util.logging.Level;
import java.util.logging.Logger;

import static com.neurotec.samples.ui.RecepisseGenerator.generateReceiptPDF;
import static com.neurotec.samples.utils.SvgUtil.*;

import org.springframework.stereotype.Component;

@Component
@AllArgsConstructor
@Data
public class PrincipalUI extends JFrame {

    Container c ;
    JMenuItem creer = new JMenuItem("nouvel utilisateur");
    JMenuItem utilisateurs = new JMenuItem("Consulter");
    JLabel titleLabel = new JLabel("TicNugu");
    JLabel appNameLabel = new JLabel("Système d'enrôlement biométrique");
    // ImageIcon bfLogo = new ImageIcon("path/to/sync/icon.png");

    JButton exportButton = new JButton("Exporter");
    JButton syncButton = new JButton("Synchroniser");
    JMenuItem aProposItem = new JMenuItem("A propos");
    JMenuItem manuelItem = new JMenuItem("Manuel");
    JMenuItem lancerItem = new JMenuItem("Lancer");
    JMenuItem arretItem = new JMenuItem("Arrêter");

    JMenuItem fonctionnaireItem = new JMenuItem("Fonctionnaire");
    JMenuItem nonfonctionnaireItem = new JMenuItem("Non fonctionnaire");
    JMenuItem regionItem = new JMenuItem("Région");
    JMenuItem provinceItem = new JMenuItem("Province");
    //JMenuItem compteItem = new JMenuItem("Compte");
    JMenuItem ecolItem = new JMenuItem("Ecole");
    JMenuItem newKitItem = new JMenuItem("Créer un kit");

    JMenuItem recepisseItem = new JMenuItem("Générer un récépissé");
    JMenu initialiserMenu = new JMenu("Initialiser");
    JMenu helpMenu = new JMenu("Aide");
    JMenu enrolerMenu = new JMenu("Enrôler");
    JMenu consulterMenu = new JMenu("Consulter");
    JMenu utilisateurMenu = new JMenu("Utilisateur");
    JMenu parametreMenu = new JMenu("Paramètre");
    JMenu rapportMenu = new JMenu("Rapport");

    JButton profilButton = new JButton("Profil");

    JMenuItem monprofil;
    JMenuItem changepassword;
    JMenuItem logout;

    ImageIcon exportButtonIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/file_export.svg")), 15, 15 ));
    ImageIcon syncButtonIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/cloud_sync.svg")), 15, 15 ));

    // declaration du Panel courant pour pouvoir redessiner le contenu du centre (ce panel contiendra l'ecran à afficher)
    JPanel currentPanel;
    JPopupMenu popupMenu;

    public PrincipalUI() {
        monprofil = new JMenuItem("Mon profil");
        changepassword = new JMenuItem("Changer de mot de passe");
        logout = new JMenuItem("Se deconnecter");
        // Création du menu contextuel (popup menu)
        popupMenu = new JPopupMenu();

        // Ajout des éléments au menu contextuel
        popupMenu.add(monprofil);
        popupMenu.add(changepassword);
        popupMenu.add(logout);
    }

//    public JMenuItem getCreer() {
//        return creer;
//    }
//    public JMenuItem getChangepassword() {
//        return changepassword;
//    }
//
//    public JMenuItem getUtilisateurs() {
//        return utilisateurs;
//    }
//
//    public JMenuItem getMonprofil() {
//        return monprofil;
//    }
//
//    public JMenuItem getLogout() {
//        return logout;
//    }
//
//    public void setProfilButton(JButton profilButton) {
//        this.profilButton = profilButton;
//    }
//    public void setTextProfilButton(String libelle) {
//        this.profilButton.setText(libelle);
//    }
//
//    public JButton getProfilButton() {
//        return profilButton;
//    }

    public void principal(){
        setTitle("TicNugu");

        // Obtenir la taille de l'écran
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

        // Appliquer la taille de l'écran à la fenêtre
        setSize(screenSize.width, screenSize.height);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        c = getContentPane(); // récupération du conteneur principal
        c.setLayout(new BorderLayout());

        JPanel nord = new JPanel();
        JPanel centre = new JPanel();
        JPanel sud = new JPanel();
        currentPanel = new JPanel(new BorderLayout()){
            // Surcharge de la méthode paintComponent pour dessiner une image de fond
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                try {
                    Image backgroundImage = ImageIO.read(new File("src/main/resources/biometrie_background_1.jpg"));
                    g.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), this);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        };
        c.add(nord,BorderLayout.NORTH);
        c.add(centre,BorderLayout.CENTER);
        c.add(sud,BorderLayout.SOUTH);

        nord.setLayout(new BorderLayout());

        JPanel appTitleCentre = new JPanel(); // pour le titre et les logos de l'application
        JPanel appTitleSud = new JPanel(); // bande verte
        appTitleCentre.setLayout(new GridLayout(1, 3));
        appTitleCentre.setPreferredSize(new Dimension(nord.getWidth(), 50));
        JPanel appTitleCentreWest = new JPanel();
        appTitleCentreWest.setLayout(new FlowLayout(FlowLayout.LEADING));
        titleLabel.setFont(new Font("Serif", Font.BOLD, 30));
        appTitleCentreWest.add(titleLabel);
        JPanel appTitleCentreCentre = new JPanel();
        appNameLabel.setFont(new Font("Serif", Font.BOLD, 30));
        appTitleCentreCentre.add(appNameLabel);
        JPanel appTitleCentreEst = new JPanel();
        appTitleCentreEst.setLayout(new FlowLayout(FlowLayout.TRAILING));
        JLabel drapeaubf = new JLabel(new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/drapeaubf.svg")), 50, 40 )));
        appTitleCentreEst.add(drapeaubf, CENTER_ALIGNMENT);
        appTitleCentre.add(appTitleCentreWest);
        appTitleCentre.add(appTitleCentreCentre);
        appTitleCentre.add(appTitleCentreEst);
        appTitleSud.setBackground(new Color(239, 51, 64)); // couleur de la bande rouge
        appTitleSud.setPreferredSize(new Dimension(nord.getWidth(), 8));
        nord.add(appTitleCentre, BorderLayout.CENTER);
        nord.add(appTitleSud, BorderLayout.SOUTH);

        sud.setLayout(new FlowLayout(FlowLayout.TRAILING));
        syncButton.setIcon(colorizeIcon(syncButtonIcon, Color.WHITE));
        exportButton.setIcon(colorizeIcon(exportButtonIcon, Color.WHITE));
        syncButton.setBackground(new Color(0, 151, 57));
        exportButton.setBackground(new Color(0, 151, 57));
        syncButton.setForeground(Color.WHITE);
        exportButton.setForeground(Color.WHITE);
        sud.add(syncButton);
        sud.add(exportButton);

        centre.setLayout(new BorderLayout());
        JMenuBar menuBar = new JMenuBar();
        menuBar.setBackground(new Color(0, 151, 57));

        profilButton.setBorder(null);
        profilButton.setBackground(null);
        profilButton.setFocusPainted(false);

        // Charger l'icône SVG
        ImageIcon initialiserIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/handyman.svg")), 20, 20 ));
        ImageIcon enrolerIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/save.svg")), 20, 20 ));
        ImageIcon consulterIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/solid/eye.svg")), 20, 20 ));
        ImageIcon rapportIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/solid/file.svg")), 20, 20 ));
        ImageIcon utilisateurIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/handyman.svg")), 20, 20 ));
        ImageIcon parametreIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/settings.svg")), 20, 20 ));
        ImageIcon helpIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/help.svg")), 20, 20 ));
        ImageIcon profilIcon = new ImageIcon(resizeImage(Objects.requireNonNull(convertSvgToPng("src/main/resources/svgs/solid/user.svg")), 20, 20 ));

        initialiserMenu.setIcon(colorizeIcon(initialiserIcon, Color.WHITE));
        initialiserMenu.setForeground(Color.WHITE);
        enrolerMenu.setIcon(colorizeIcon(enrolerIcon, Color.WHITE));
        enrolerMenu.setForeground(Color.WHITE);
        consulterMenu.setIcon(colorizeIcon(consulterIcon, Color.WHITE));
        consulterMenu.setForeground(Color.WHITE);
        rapportMenu.setIcon(colorizeIcon(rapportIcon, Color.WHITE));
        rapportMenu.setForeground(Color.WHITE);
        utilisateurMenu.setIcon(colorizeIcon(utilisateurIcon, Color.WHITE));
        utilisateurMenu.setForeground(Color.WHITE);
        parametreMenu.setIcon(colorizeIcon(parametreIcon, Color.WHITE));
        parametreMenu.setForeground(Color.WHITE);
        helpMenu.setIcon(colorizeIcon(helpIcon, Color.WHITE));
        helpMenu.setForeground(Color.WHITE);
        profilButton.setIcon(colorizeIcon(profilIcon, Color.WHITE));
        profilButton.setForeground(Color.WHITE);

        initialiserMenu.add(lancerItem);
        initialiserMenu.add(arretItem);

        helpMenu.add(aProposItem);
        helpMenu.add(manuelItem);

        enrolerMenu.add(fonctionnaireItem);
        enrolerMenu.add(nonfonctionnaireItem);

        parametreMenu.add(regionItem);
        parametreMenu.add(provinceItem);
        parametreMenu.add(ecolItem);
        parametreMenu.add(newKitItem);

        utilisateurMenu.add(creer);
        utilisateurMenu.add(utilisateurs);

        rapportMenu.add(recepisseItem);

        menuBar.add(initialiserMenu);
        menuBar.add(enrolerMenu);
        menuBar.add(consulterMenu);
        menuBar.add(rapportMenu);
        menuBar.add(utilisateurMenu);
        menuBar.add(parametreMenu);
        menuBar.add(helpMenu);

        menuBar.setPreferredSize(new Dimension(nord.getWidth(), 50));
        menuBar.setBorder(null);

        JPanel centreNord = new JPanel(new BorderLayout());
        centreNord.setBackground(new Color(0, 151, 57));
        centreNord.add(menuBar, BorderLayout.CENTER);
        centreNord.add(profilButton, BorderLayout.EAST);
        profilButton.setPreferredSize(new Dimension(90, menuBar.getHeight()));


        centre.add(centreNord, BorderLayout.NORTH);

        JPanel centreCentre = new JPanel(new BorderLayout());

        //Ajout du panel courant au panel Central
        centreCentre.add(this.currentPanel);

        centre.add(centreCentre, BorderLayout.CENTER);

//        fonctionnaireItem.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                repaintPanel(new EnrolementUI());
//            }
//        });

         regionItem.addActionListener(new ActionListener() {
             @Override
             public void actionPerformed(ActionEvent e) {
                 new RegionUI();
             }
         });
        provinceItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                repaintPanel(new Province());
            }
        });
        ecolItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                repaintPanel(new Ecole());
            }
        });

        newKitItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                repaintPanel(new Kite());
            }
        });
        //action a executer lors du clic du buttonGenRecepisse
        recepisseItem.addActionListener(e -> {
            try {
                generateReceiptPDF(5L);
            } catch (IOException ex) {
                Logger.getLogger(RecepisseGenerator.class.getName()).log(Level.SEVERE, null, ex);
            }
        });

        profilButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                popupMenu.show(profilButton, profilButton.getWidth() / 2, profilButton.getHeight() / 2);
            }
        });

        this.setVisible(true);
    }

    public void repaintPanel(JPanel panel) {
        currentPanel.removeAll();  // Retirer les composants actuels
//        currentPanel.setOpaque(false); // Assurez-vous que le nouveau panneau est aussi transparent
//        currentPanel.add(panel, BorderLayout.CENTER);
//        currentPanel.revalidate();  // Revalider pour mettre à jour l'affichage
//        currentPanel.repaint();

        JPanel overlayPanel = new JPanel(new BorderLayout()) {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                try {
                    Image backgroundImage = ImageIO.read(new File("src/main/resources/biometrie_background_1.jpg"));
                    g.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), this);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        };

        overlayPanel.add(panel, BorderLayout.CENTER); // Ajout du nouveau contenu par-dessus l'image de fond
        currentPanel.add(overlayPanel, BorderLayout.CENTER);
        currentPanel.setOpaque(false);
        currentPanel.revalidate();  // Revalider pour mettre à jour l'affichage
        currentPanel.repaint();
    }

}
