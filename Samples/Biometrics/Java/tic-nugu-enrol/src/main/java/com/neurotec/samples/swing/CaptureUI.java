/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.neurotec.samples.swing;

import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;
import org.opencv.videoio.VideoCapture;

/**
 *
 * @author hp
 */
public class CaptureUI extends JFrame {

    private VideoCapture videoCapture;
    private JLabel videoLabel;
    private JButton captureButton;
    private JButton viewImageButton;
    private JButton continueButton; // Nouveau bouton pour continuer
    private String imagePath;
    private int imageCounter = 0;

    public CaptureUI() {
        // Chargement de la bibliothèque OpenCV
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);

        // Initialisation du JFrame
        setTitle("Video Capture");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Création du JLabel pour afficher la vidéo
        videoLabel = new JLabel();
        add(videoLabel, BorderLayout.CENTER);

        // Création du bouton de capture
        captureButton = new JButton("Capture Image");
        add(captureButton, BorderLayout.SOUTH);

        // Création du bouton pour voir la photo capturée
        viewImageButton = new JButton("Voir la Photo");
        add(viewImageButton, BorderLayout.NORTH);
        viewImageButton.setEnabled(false);  // Désactiver le bouton tant qu'il n'y a pas de photo

        // Nouveau bouton pour continuer après capture
        continueButton = new JButton("Continuer");
        add(continueButton, BorderLayout.EAST);
        continueButton.setEnabled(false); // Désactivé jusqu'à la capture de l'image

        // Initialisation du flux vidéo
        videoCapture = new VideoCapture(0);  // Capture depuis la caméra par défaut

        // Action sur le clic du bouton pour capturer l'image
        captureButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                captureImage();
            }
        });

        // Action sur le clic du bouton pour voir la photo
        viewImageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewCapturedImage();
            }
        });

        // Action sur le bouton Continuer
       continueButton.addActionListener(new ActionListener() {
    @Override
    public void actionPerformed(ActionEvent e) {
        // Arrêter la capture vidéo
        if (videoCapture.isOpened()) {
            videoCapture.release();  // Libérer la caméra
        }

        // Fermer la fenêtre actuelle
        dispose();
        
        // Ouvrir une nouvelle fenêtre ou un autre écran
        //openNextScreen();
        new MainFrame().setVisible(true);
    }
});

        // Thread pour afficher la vidéo en continu
        new Thread(() -> {
            while (true) {
                Mat frame = new Mat();
                if (videoCapture.read(frame)) {
                    ImageIcon icon = new ImageIcon(matToBufferedImage(frame));
                    videoLabel.setIcon(icon);
                }
            }
        }).start();
    }

    // Méthode pour capturer l'image et l'enregistrer dans un dossier
    private void captureImage() {
        Mat frame = new Mat();
        if (videoCapture.read(frame)) {
            // Créer le dossier "captured_images" s'il n'existe pas
            File directory = new File("captured_images");
            if (!directory.exists()) {
                directory.mkdir();
            }

            // Incrémenter le compteur et générer le nom du fichier
            imageCounter++;
            imagePath = "captured_images/captured_image_" + imageCounter + ".jpg";

            // Conversion en RGB pour l'enregistrement
            Imgproc.cvtColor(frame, frame, Imgproc.COLOR_BGR2RGB);

            // Enregistrement de l'image capturée
            Imgcodecs.imwrite(imagePath, frame);

            JOptionPane.showMessageDialog(this, "Image capturée et sauvegardée sous le nom : " + imagePath);
            viewImageButton.setEnabled(true);  // Activer le bouton pour voir l'image
            continueButton.setEnabled(true);  // Activer le bouton pour continuer
        }
    }

    // Méthode pour afficher l'image capturée dans une nouvelle fenêtre
    private void viewCapturedImage() {
        JFrame imageFrame = new JFrame("Image Capturée");
        imageFrame.setSize(600, 400);

        // Charger l'image capturée
        try {
            BufferedImage capturedImage = ImageIO.read(new File(imagePath));
            JLabel imageLabel = new JLabel(new ImageIcon(capturedImage));
            imageFrame.add(imageLabel);
            imageFrame.setVisible(true);
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(this, "Erreur lors du chargement de l'image !");
        }
    }

    // Méthode pour ouvrir un autre écran
   
   private void openNextScreen() {
    JFrame nextFrame = new JFrame("Nouvel Écran");
    nextFrame.setSize(800, 500);  // Taille de la fenêtre
    nextFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    // Utilisation d'un GridBagLayout pour centrer le bouton
    nextFrame.setLayout(new GridBagLayout());
    GridBagConstraints gbc = new GridBagConstraints();
    gbc.gridx = 0;
    gbc.gridy = 0;
    gbc.anchor = GridBagConstraints.CENTER;  // Centrer le bouton

    // Création d'un bouton centré
    JButton nextButton = new JButton("Passer à l'écran suivant");
    nextFrame.add(nextButton, gbc);

    // Action sur le bouton pour ouvrir une nouvelle fenêtre
    nextButton.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
            // Fermer la fenêtre actuelle
            nextFrame.dispose();
            

          //*************** new SigPlusTopaz().setVisible(true);
            new MainFrame().setVisible(true);
        }
    });

    // Rendre la fenêtre visible
    nextFrame.setVisible(true);
}

    // Conversion d'une Mat en BufferedImage pour l'affichage
    private BufferedImage matToBufferedImage(Mat mat) {
        int width = mat.width();
        int height = mat.height();
        int channels = mat.channels();
        byte[] sourcePixels = new byte[width * height * channels];
        mat.get(0, 0, sourcePixels);
        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_3BYTE_BGR);
        final byte[] targetPixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
        System.arraycopy(sourcePixels, 0, targetPixels, 0, sourcePixels.length);
        return image;
    }

   
}
