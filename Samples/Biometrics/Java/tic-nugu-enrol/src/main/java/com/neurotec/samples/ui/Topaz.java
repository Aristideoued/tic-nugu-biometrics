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
import javax.swing.*;

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
    private JButton captureWithoutFaceButton;
    private JButton viewImageButton;
    private JButton closeButton;
    private String imagePath;
    private int imageCounter = 0;
    private CascadeClassifier faceDetector;
    private boolean faceDetected = false;
    private int noFaceCounter = 0;
    private static final int MAX_NO_FACE_FRAMES = 30;
    private Rect lastFace;

    public Topaz() {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);

        setTitle("Video Capture avec Détection de Visage");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        videoLabel = new JLabel();
        add(videoLabel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout());

        captureButton = new JButton("Capture reconnaissance faciale");
        buttonPanel.add(captureButton);
        captureButton.setEnabled(false);

        captureWithoutFaceButton = new JButton("Capture Image Simple");
        buttonPanel.add(captureWithoutFaceButton);

        viewImageButton = new JButton("Voir la Photo");
        buttonPanel.add(viewImageButton);
        viewImageButton.setEnabled(false);

        closeButton = new JButton("Fermer");
        add(closeButton, BorderLayout.EAST);

        add(buttonPanel, BorderLayout.SOUTH);

        videoCapture = new VideoCapture(0);
        faceDetector = new CascadeClassifier("haarcascade_frontalface_default.xml");

        captureButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                captureImageWithFace();
            }
        });

        captureWithoutFaceButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                captureImageWithoutFace();
            }
        });

        viewImageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewCapturedImage();
            }
        });

        closeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                releaseCamera();  // Libérer la caméra
                dispose();
                new MainFrame().setVisible(true);
            }
        });

        new Thread(() -> {
            while (true) {
                Mat frame = new Mat();
                if (videoCapture.read(frame)) {
                    faceDetected = detectAndDisplay(frame);

                    if (faceDetected) {
                        captureButton.setEnabled(true);
                        noFaceCounter = 0;
                    } else {
                        noFaceCounter++;
                        if (noFaceCounter >= MAX_NO_FACE_FRAMES) {
                            captureButton.setEnabled(false);
                        }
                    }
                }
            }
        }).start();
    }
    // Méthode pour libérer la caméra
    private void releaseCamera() {
        if (videoCapture.isOpened()) {
            videoCapture.release();
        }
    }
    private boolean detectAndDisplay(Mat frame) {
        MatOfRect faceDetections = new MatOfRect();
        faceDetector.detectMultiScale(frame, faceDetections, 1.1, 5, 0,
                new Size(30, 30), new Size());

        boolean detected = false;

        if (faceDetections.toArray().length > 0) {
            lastFace = faceDetections.toArray()[0];
            for (Rect rect : faceDetections.toArray()) {
                Imgproc.rectangle(frame,
                        new org.opencv.core.Point(rect.x, rect.y),
                        new org.opencv.core.Point(rect.x + rect.width, rect.y + rect.height),
                        new Scalar(0, 255, 0));
            }
            detected = true;
        } else if (noFaceCounter < MAX_NO_FACE_FRAMES && lastFace != null) {
            Imgproc.rectangle(frame,
                    new org.opencv.core.Point(lastFace.x, lastFace.y),
                    new org.opencv.core.Point(lastFace.x + lastFace.width, lastFace.y + lastFace.height),
                    new Scalar(0, 255, 0));
        }

        ImageIcon icon = new ImageIcon(matToBufferedImage(frame));
        videoLabel.setIcon(icon);

        return detected;
    }

    private void captureImageWithFace() {
        Mat frame = new Mat();
        if (videoCapture.read(frame)) {
            MatOfRect faceDetections = new MatOfRect();
            faceDetector.detectMultiScale(frame, faceDetections);

            if (faceDetections.toArray().length > 0) {
                Rect faceRect = faceDetections.toArray()[0];
                Mat face = new Mat(frame, faceRect);

                File directory = new File("captured_images");
                if (!directory.exists()) {
                    directory.mkdir();
                }

                imageCounter++;
                imagePath = "captured_images/captured_face_" + imageCounter + ".jpg";
                Imgproc.cvtColor(face, face, Imgproc.COLOR_BGR2RGB);
                Imgcodecs.imwrite(imagePath, face);

                JOptionPane.showMessageDialog(this, "Image capturée avec visage : " + imagePath);
                viewImageButton.setEnabled(true);
            } else {
                JOptionPane.showMessageDialog(this, "Aucun visage détecté.");
            }
        }
    }

    private void captureImageWithoutFace() {
        Mat frame = new Mat();
        if (videoCapture.read(frame)) {
            File directory = new File("captured_images");
            if (!directory.exists()) {
                directory.mkdir();
            }

            imageCounter++;
            imagePath = "captured_images/captured_image_" + imageCounter + ".jpg";
            Imgproc.cvtColor(frame, frame, Imgproc.COLOR_BGR2RGB);
            Imgcodecs.imwrite(imagePath, frame);

            JOptionPane.showMessageDialog(this, "Image simple capturée : " + imagePath);
            viewImageButton.setEnabled(true);
        }
    }

    private void viewCapturedImage() {
        JFrame imageFrame = new JFrame("Image Capturée");
        imageFrame.setSize(600, 400);

        try {
            BufferedImage capturedImage = ImageIO.read(new File(imagePath));
            JLabel imageLabel = new JLabel(new ImageIcon(capturedImage));
            imageFrame.add(imageLabel);
            imageFrame.setVisible(true);
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(this, "Erreur lors du chargement de l'image !");
        }
    }

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
