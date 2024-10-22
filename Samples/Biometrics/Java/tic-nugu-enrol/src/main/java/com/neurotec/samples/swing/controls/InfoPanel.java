package com.neurotec.samples.swing.controls;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.text.SimpleDateFormat;
import java.util.Base64;
import java.util.Date;
import java.util.logging.Logger;
import javax.swing.*;
import javax.swing.border.TitledBorder;

import com.toedter.calendar.JCalendar;
import com.neurotec.biometrics.NFace;
import com.neurotec.biometrics.swing.NFaceView;
import com.neurotec.images.NImage;
import com.neurotec.samples.Utilities;
import com.neurotec.samples.enrollment.EnrollmentDataModel;
import com.neurotec.samples.swing.PictureCapturingDialog;

public final class InfoPanel extends JPanel {

    private static final long serialVersionUID = 1L;
    private static final Logger logger = Logger.getLogger(InfoPanel.class.getName());

    private NFaceView thumbnailImageView;
    private String base64Image;

    // Champs du formulaire
    private JTextField txtNip, txtRefPiece, txtTypePiece, txtMatricule, txtNom, txtPrenom, txtNomJF;
    private JTextField txtTelephone, txtMail, txtLieuNaissance;
    private JCalendar calendar; // JCalendar pour la date
    private JComboBox<String> cmbSexe;
    private JButton btnSave;

    private Frame owner;

    public InfoPanel(Frame owner) {
        this.owner = owner;
        initializeComponents();
        onModelChanged();
    }

    private void initializeComponents() {
        setLayout(new BorderLayout());
        setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        // Panes pour séparer la partie formulaire et photo
        JPanel formPanel = createFormPanel();
        JPanel imagePanel = createImagePanel();

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, formPanel, imagePanel);
        splitPane.setDividerLocation(600);
        splitPane.setDividerSize(10);
        add(splitPane, BorderLayout.CENTER);
    }

    private JPanel createFormPanel() {
        JPanel panel = new JPanel(new GridLayout(0, 2, 10, 10));
        panel.setBorder(BorderFactory.createTitledBorder("Informations Personnelles"));

        // Champs avec labels
        panel.add(new JLabel("NIP:"));
        txtNip = new JTextField();
        panel.add(txtNip);

        panel.add(new JLabel("Référence de la pièce:"));
        txtRefPiece = new JTextField();
        panel.add(txtRefPiece);

        panel.add(new JLabel("Type de pièce:"));
        txtTypePiece = new JTextField();
        panel.add(txtTypePiece);

        panel.add(new JLabel("Matricule:"));
        txtMatricule = new JTextField();
        panel.add(txtMatricule);

        panel.add(new JLabel("Nom:"));
        txtNom = new JTextField();
        panel.add(txtNom);

        panel.add(new JLabel("Prénom:"));
        txtPrenom = new JTextField();
        panel.add(txtPrenom);

        panel.add(new JLabel("Nom de jeune fille:"));
        txtNomJF = new JTextField();
        panel.add(txtNomJF);

        panel.add(new JLabel("Téléphone:"));
        txtTelephone = new JTextField();
        panel.add(txtTelephone);

        panel.add(new JLabel("Email:"));
        txtMail = new JTextField();
        panel.add(txtMail);

        panel.add(new JLabel("Date de naissance:"));
        calendar = new JCalendar();
        panel.add(calendar);

        panel.add(new JLabel("Lieu de naissance:"));
        txtLieuNaissance = new JTextField();
        panel.add(txtLieuNaissance);

        panel.add(new JLabel("Sexe:"));
        cmbSexe = new JComboBox<>(new String[]{"Homme", "Femme"});
        panel.add(cmbSexe);

        // Bouton "Enregistrer"
        btnSave = createCustomButton("Enregistrer", "Enregistrer les informations");
        btnSave.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                saveInformationToDatabase();
            }
        });
        panel.add(btnSave);

        return panel;
    }

    private JPanel createImagePanel() {
        JPanel panel = new JPanel(new BorderLayout());
        panel.setBorder(BorderFactory.createTitledBorder("Photo de Profil"));

        thumbnailImageView = new NFaceView();
        thumbnailImageView.setAutofit(true); // S'assurer que l'image s'adapte bien
        panel.add(thumbnailImageView, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        JButton btnCapture = createCustomButton("Capture Photo", "Capture une photo");
        btnCapture.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                btnCaptureClick();
            }
        });
        buttonPanel.add(btnCapture);
        panel.add(buttonPanel, BorderLayout.SOUTH);

        return panel;
    }

    private void btnCaptureClick() {
        if (EnrollmentDataModel.getInstance().getBiometricClient().getFaceCaptureDevice() == null) {
            Utilities.showInformation(this, "Aucune caméra détectée. Connectez une caméra et réessayez.");
            return;
        }

        PictureCapturingDialog form = new PictureCapturingDialog(owner);
        form.setVisible(true);

        // Mettre à jour le visage capturé
        NFace capturedFace = EnrollmentDataModel.getInstance().getThumbFace();
        if (capturedFace != null) {
            logger.info("Captured face: not null");
            thumbnailImageView.setFace(capturedFace); // Prévisualiser l'image capturée

            // Convertir l'image capturée en Base64
            NImage image = capturedFace.getImage();
            base64Image = convertImageToBase64(image);
            logger.info("Captured image converted to Base64: " + base64Image);

            // Repeindre le composant pour assurer que l'image s'affiche
            thumbnailImageView.repaint();
            thumbnailImageView.revalidate();
        } else {
            logger.warning("Aucun visage capturé.");
        }
    }

    private String convertImageToBase64(NImage image) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        try {
            java.awt.Image awtImage = image.toImage();
            java.awt.image.BufferedImage bufferedImage = new java.awt.image.BufferedImage(
                    awtImage.getWidth(null),
                    awtImage.getHeight(null),
                    java.awt.image.BufferedImage.TYPE_INT_ARGB
            );

            java.awt.Graphics2D g2d = bufferedImage.createGraphics();
            g2d.drawImage(awtImage, 0, 0, null);
            g2d.dispose();

            logger.info("Attempting to write image to ByteArrayOutputStream.");
            boolean writeSuccess = javax.imageio.ImageIO.write(bufferedImage, "PNG", baos);
            if (!writeSuccess) {
                logger.warning("ImageIO.write returned false.");
            }

            byte[] imageBytes = baos.toByteArray();
            logger.info("Image converted to byte array of length: " + imageBytes.length);
            return Base64.getEncoder().encodeToString(imageBytes);
        } catch (IOException e) {
            logger.severe("Exception occurred while converting image to Base64: " + e.getMessage());
            return null;
        }
    }

    private void saveInformationToDatabase() {
        // Récupérer les valeurs des champs
        String nip = txtNip.getText().trim();
        String refPiece = txtRefPiece.getText().trim();
        String typePiece = txtTypePiece.getText().trim();
        String matriculeStr = txtMatricule.getText().trim();
        String nom = txtNom.getText().trim();
        String prenom = txtPrenom.getText().trim();
        String nomJF = txtNomJF.getText().trim();
        String telephone = txtTelephone.getText().trim();
        String mail = txtMail.getText().trim();
        Date dateNaissance = calendar.getDate(); // Obtenir la date sélectionnée
        String lieuNaissance = txtLieuNaissance.getText().trim();
        String sexe = (String) cmbSexe.getSelectedItem();

        // Vérifications des champs obligatoires
        if (nip.isEmpty()) {
            Utilities.showError(this, "Le NIP est obligatoire !");
            return;
        }
        if (matriculeStr.isEmpty()) {
            Utilities.showError(this, "Le matricule est obligatoire !");
            return;
        }
        if (base64Image == null || base64Image.isEmpty()) {
            Utilities.showError(this, "Veuillez capturer une image avant d'enregistrer !");
            return;
        }

        // Convertir le matricule en entier
        int matricule;
        try {
            matricule = Integer.parseInt(matriculeStr);
        } catch (NumberFormatException e) {
            Utilities.showError(this, "Le matricule doit être un nombre valide !");
            return;
        }

        // Connexion à la base de données
        String dbUrl = "jdbc:postgresql://localhost:5432/enrolDB";
        String dbUser = "postgres";
        String dbPassword = "admin";

        try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
            String sql = "INSERT INTO utilisateur_info (nip, refPiece, typePiece, matricule, nom, prenom, nomJF, " +
                    "telephone, mail, dateNaissance, lieuNaissance, sexe, photo) " +
                    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, nip);
                stmt.setString(2, refPiece);
                stmt.setString(3, typePiece);
                stmt.setInt(4, matricule);
                stmt.setString(5, nom);
                stmt.setString(6, prenom);
                stmt.setString(7, nomJF);
                stmt.setString(8, telephone);
                stmt.setString(9, mail);
                SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd"); // Format de la date
                stmt.setString(10, sdf.format(dateNaissance)); // Formater la date
                stmt.setString(11, lieuNaissance);
                stmt.setString(12, sexe);
                stmt.setString(13, base64Image); // Stocker l'image en base64

                stmt.executeUpdate();
                logger.info("User info saved successfully!");
                Utilities.showInformation(this, "Informations enregistrées avec succès !");
            }
        } catch (Exception e) {
            logger.severe("Error while saving information to database: " + e.getMessage());
            Utilities.showError(this, "Erreur lors de l'enregistrement des informations !");
        }
    }

    private JButton createCustomButton(String text, String toolTipText) {
        JButton btn = new JButton(text);
        btn.setFont(new Font("Arial", Font.PLAIN, 12));
        btn.setPreferredSize(new Dimension(150, 35));
        btn.setBackground(Color.BLUE); // Set button color to blue
        btn.setForeground(Color.WHITE);
        btn.setToolTipText(toolTipText);
        return btn;
    }

    public void onModelChanged() {
        NFace thumbFace = EnrollmentDataModel.getInstance().getThumbFace();
        if (thumbFace != null) {
            thumbnailImageView.setFace(thumbFace);
            base64Image = convertImageToBase64(thumbFace.getImage());
            logger.info("Thumbnail image updated from model.");
        }
    }
}
