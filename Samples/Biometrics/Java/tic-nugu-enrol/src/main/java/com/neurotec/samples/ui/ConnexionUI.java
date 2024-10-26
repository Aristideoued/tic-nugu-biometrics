package com.neurotec.samples.ui;

import lombok.Data;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.swing.*;
import java.awt.*;

@Component
@Data
public class ConnexionUI extends JFrame {

    private JTextField matriculeField;
    private JPasswordField passwordField;
    private JLabel imageLabel;
    private JButton connexionButton;

    @PostConstruct
    public void initUI() {
        setTitle("Connexion");
        setSize(500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Initialize main panel
        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.setBackground(Color.WHITE);

        // Header with logo and title
        JPanel headerPanel = new JPanel(new BorderLayout());
        headerPanel.setBackground(new Color(0, 151, 57)); // Bootstrap blue
        headerPanel.setBorder(BorderFactory.createEmptyBorder(20, 0, 20, 0));

        // Resize the logo image
        ImageIcon originalIcon = new ImageIcon("src/main/resources/logo.PNG");
        Image scaledImage = originalIcon.getImage().getScaledInstance(100, 100, Image.SCALE_SMOOTH); // Adjust width and height as needed
        ImageIcon resizedIcon = new ImageIcon(scaledImage);

        // Logo
        imageLabel = new JLabel(resizedIcon, JLabel.CENTER);
        headerPanel.add(imageLabel, BorderLayout.NORTH);

        // Title
        JLabel titleLabel = new JLabel("Connexion", JLabel.CENTER);
        titleLabel.setForeground(Color.WHITE);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 26));
        headerPanel.add(titleLabel, BorderLayout.CENTER);

        mainPanel.add(headerPanel, BorderLayout.NORTH);

        // Form Panel
        JPanel formPanel = new JPanel(new GridBagLayout());
        formPanel.setBackground(Color.WHITE);
        formPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);

        // Username field
        gbc.gridx = 0;
        gbc.gridy = 0;
        formPanel.add(new JLabel("Nom d'utilisateur:"), gbc);

        matriculeField = new JTextField(15);
        styleTextField(matriculeField);
        gbc.gridx = 1;
        formPanel.add(matriculeField, gbc);

        // Password field
        gbc.gridx = 0;
        gbc.gridy++;
        formPanel.add(new JLabel("Mot de passe:"), gbc);

        passwordField = new JPasswordField(15);
        styleTextField(passwordField);
        gbc.gridx = 1;
        formPanel.add(passwordField, gbc);

        // Login Button
        connexionButton = new JButton("Se connecter");
        connexionButton.setBackground(new Color(0, 123, 255)); // Couleur gris Bootstrap
        connexionButton.setForeground(Color.WHITE); // Texte blanc (ou noir si vous préférez)
        connexionButton.setFocusPainted(false);
        connexionButton.setOpaque(true);
        connexionButton.setFocusPainted(false);
        connexionButton.setBorder(BorderFactory.createEmptyBorder(10, 25, 10, 25));
        connexionButton.setFont(new Font("Arial", Font.BOLD, 14));
        connexionButton.setCursor(new Cursor(Cursor.HAND_CURSOR));

        //styleButton(connexionButton);
        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 2;
        formPanel.add(connexionButton, gbc);

        // Add form panel to main panel
        mainPanel.add(formPanel, BorderLayout.CENTER);

        // Add main panel to frame
        add(mainPanel);
    }

    private void styleTextField(JTextField textField) {
        textField.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(new Color(0, 123, 255), 1),
                BorderFactory.createEmptyBorder(5, 5, 5, 5)
        ));
        textField.setFont(new Font("Arial", Font.PLAIN, 14));
        textField.setForeground(Color.DARK_GRAY);
    }

    private void styleButton(JButton button) {
        button.setBackground(new Color(10, 125, 239));
        button.setForeground(Color.WHITE);
        button.setFocusPainted(false);
        button.setBorder(BorderFactory.createEmptyBorder(10, 25, 10, 25));
        button.setFont(new Font("Arial", Font.BOLD, 14));
        button.setCursor(new Cursor(Cursor.HAND_CURSOR));
    }



    public void resetForm() {
        matriculeField.setText("");
        passwordField.setText("");
    }
}
