package com.neurotec.samples.ui;

import java.awt.*;
//import java.awt.Point;
import com.neurotec.samples.swing.MainFrame;
import org.opencv.core.Point;
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
import javax.swing.SwingUtilities;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;
import org.opencv.objdetect.CascadeClassifier;
import org.opencv.videoio.VideoCapture;


public class Topaz extends JFrame {



    private VideoCapture videoCapture;
    private JLabel videoLabel;
    private JButton captureButton;
    private JButton viewImageButton;
    private String imagePath;
    private int imageCounter = 0;
    private CascadeClassifier faceDetector;
    private boolean faceDetected = false;
    private int noFaceCounter = 0;
    private static final int MAX_NO_FACE_FRAMES = 30;  // Garder le rectangle affiché pendant 30 frames après la dernière détection
    private Rect lastFace;  // Dernière position du visage détecté

    public Topaz() {
        // Chargement de la bibliothèque OpenCV
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);

        // Initialisation du JFrame
        setTitle("Video Capture avec Détection de Visage");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Création du JLabel pour afficher la vidéo
        videoLabel = new JLabel();
        add(videoLabel, BorderLayout.CENTER);

        // Création du bouton de capture
        captureButton = new JButton("Capture Image");
        add(captureButton, BorderLayout.SOUTH);
        captureButton.setEnabled(false);  // Désactiver jusqu'à ce qu'un visage soit détecté

        // Création du bouton pour voir la photo capturée
        viewImageButton = new JButton("Voir la Photo");
        add(viewImageButton, BorderLayout.NORTH);
        viewImageButton.setEnabled(false);  // Désactiver le bouton tant qu'il n'y a pas de photo

        // Initialisation du flux vidéo
        videoCapture = new VideoCapture(0);  // Capture depuis la caméra par défaut

        // Chargement du classificateur en cascade pour la détection de visages
        faceDetector = new CascadeClassifier("haarcascade_frontalface_default.xml");

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

        // Thread pour afficher la vidéo en continu avec détection de visage
        new Thread(() -> {
            while (true) {
                Mat frame = new Mat();
                if (videoCapture.read(frame)) {
                    faceDetected = detectAndDisplay(frame);  // Détecter et afficher les visages

                    // Si un visage est détecté, activer le bouton de capture et réinitialiser le compteur
                    if (faceDetected) {
                        captureButton.setEnabled(true);
                        noFaceCounter = 0;  // Réinitialiser le compteur si un visage est détecté
                    } else {
                        // Incrémenter le compteur si aucun visage n'est détecté
                        noFaceCounter++;
                        if (noFaceCounter >= MAX_NO_FACE_FRAMES) {
                            captureButton.setEnabled(false);  // Désactiver après plusieurs frames sans visage
                        }
                    }
                }
            }
        }).start();
    }

    // Méthode pour détecter les visages et afficher le flux vidéo
    private boolean detectAndDisplay(Mat frame) {
        MatOfRect faceDetections = new MatOfRect();
        // Ajustement des paramètres de detectMultiScale pour une meilleure précision
        faceDetector.detectMultiScale(frame, faceDetections, 1.1, 5, 0,
                new Size(30, 30), new Size());  // Ajustez ces valeurs selon votre besoin

        boolean detected = false;

        // Dessiner des rectangles autour des visages détectés
        if (faceDetections.toArray().length > 0) {
            lastFace = faceDetections.toArray()[0];  // Mémoriser la dernière détection
            for (Rect rect : faceDetections.toArray()) {
                Imgproc.rectangle(frame,
                        new Point(rect.x, rect.y),
                        new Point(rect.x + rect.width, rect.y + rect.height),
                        new Scalar(0, 255, 0)); // Couleur verte
            }
            detected = true;  // Un visage a été détecté
        } else {
            // Si aucun visage n'est détecté, laisser le dernier rectangle affiché
            if (noFaceCounter < MAX_NO_FACE_FRAMES && lastFace != null) {
                Imgproc.rectangle(frame,
                        new Point(lastFace.x, lastFace.y),
                        new Point(lastFace.x + lastFace.width, lastFace.y + lastFace.height),
                        new Scalar(0, 255, 0)); // Couleur verte
            }
        }

        // Affichage du flux vidéo avec ou sans rectangles
        ImageIcon icon = new ImageIcon(matToBufferedImage(frame));
        videoLabel.setIcon(icon);

        return detected;  // Retourne si un visage est détecté ou non
    }

    // Méthode pour capturer l'image du visage seulement et l'enregistrer dans un dossier
    private void captureImage() {
        Mat frame = new Mat();
        if (videoCapture.read(frame)) {
            MatOfRect faceDetections = new MatOfRect();
            faceDetector.detectMultiScale(frame, faceDetections);

            if (faceDetections.toArray().length > 0) {
                // Prendre la première détection de visage
                Rect faceRect = faceDetections.toArray()[0];

                // Découper uniquement la région correspondant au visage
                Mat face = new Mat(frame, faceRect);

                // Créer le dossier "captured_images" s'il n'existe pas
                File directory = new File("captured_images");
                if (!directory.exists()) {
                    directory.mkdir();
                }

                // Incrémenter le compteur et générer le nom du fichier
                imageCounter++;
                imagePath = "captured_images/captured_face_" + imageCounter + ".jpg";

                // Conversion en RGB pour l'enregistrement
                Imgproc.cvtColor(face, face, Imgproc.COLOR_BGR2RGB);

                // Enregistrement de l'image du visage capturé
                Imgcodecs.imwrite(imagePath, face);

                JOptionPane.showMessageDialog(this, "Image du visage capturée et sauvegardée sous le nom : " + imagePath);
                viewImageButton.setEnabled(true);
                dispose();
                MainFrame mainFrame = new MainFrame();


                Dimension d = new Dimension(1600, 800);
                mainFrame.setSize(d);
                mainFrame.setMinimumSize(new Dimension(300, 200));
                mainFrame.setPreferredSize(d);

                mainFrame.setResizable(true); // Optionnel, si tu veux empêcher le redimensionnement
                mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                mainFrame.setTitle("Tic-nugu");
                mainFrame.setLocationRelativeTo(null);
                mainFrame.setVisible(true);


                // Activer le bouton pour voir l'image
            } else {
                JOptionPane.showMessageDialog(this, "Image sauvegardee !");
            }
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
