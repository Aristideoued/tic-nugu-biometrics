package com.neurotec.samples.ui;
import lombok.Data;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;


import javax.annotation.PostConstruct;
import javax.swing.*;
import java.awt.*;
import java.util.Objects;



/**
 * UI class for user login.
 *
 * @author hp ZINA
 */


@Component
@Data
public class ConnexionUI extends JFrame {

    private JTextField matriculeField;
    private JPasswordField passwordField;
    private JLabel imageLabel;
    private JButton connexionButton;

    @PostConstruct
    public void initUI() {
        setTitle("Login");
        setSize(500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Initialize main panel
        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.setBackground(Color.WHITE);

        // Add image at the top
        imageLabel = new JLabel(new ImageIcon("src/main/resources/logo.PNG"), JLabel.CENTER);
        mainPanel.add(imageLabel, BorderLayout.NORTH);

        // Create the login form panel
        JPanel formPanel = new JPanel(new GridBagLayout());
        formPanel.setBackground(Color.WHITE);
        formPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);

        // Add matricule label and text field
        gbc.gridx = 0;
        gbc.gridy = 0;
        formPanel.add(new JLabel("Nom d'utilisateur:"), gbc);

        matriculeField = new JTextField(15);
        gbc.gridx = 1;
        formPanel.add(matriculeField, gbc);

        // Add password label and password field
        gbc.gridx = 0;
        gbc.gridy++;
        formPanel.add(new JLabel("Mot de passe:"), gbc);

        passwordField = new JPasswordField(15);
        gbc.gridx = 1;
        formPanel.add(passwordField, gbc);

        // Add connection button
        connexionButton = new JButton("Se connecter");
        ///connexionButton.setBackground(new Color(100, 149, 237));
        //connexionButton.setForeground(Color.BLUE);
        //connexionButton.setBorder(BorderFactory.createRaisedBevelBorder());
        connexionButton.setBackground(new Color(0, 123, 255)); // Couleur gris Bootstrap
        connexionButton.setForeground(Color.WHITE); // Texte blanc (ou noir si vous préférez)
        connexionButton.setFocusPainted(false);
        connexionButton.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20)); // Même bordure interne
        connexionButton.setOpaque(true);
        connexionButton.setBorder(BorderFactory.createLineBorder(new Color(0, 123, 255), 3)); // Bordure gris foncé

        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 2;
        formPanel.add(connexionButton, gbc);

        // Add form panel to main panel
        mainPanel.add(formPanel, BorderLayout.CENTER);

        // Add action listener for login button
        ///connexionButton.addActionListener(e -> handleLogin());

        // Add main panel to the frame
        add(mainPanel);
    }
    public void resetForm() {
        matriculeField.setText("");  // Réinitialiser le champ du nom d'utilisateur
        passwordField.setText("");  // Réinitialiser le champ du mot de passe
    }

}

