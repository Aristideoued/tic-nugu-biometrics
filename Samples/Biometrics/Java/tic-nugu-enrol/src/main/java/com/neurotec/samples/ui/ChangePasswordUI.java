package com.neurotec.samples.ui;

import lombok.Data;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

@Data
@Component
public class ChangePasswordUI extends JFrame {
    private JTextField passwordField;
    private JPasswordField newPasswordField;
    private JPasswordField newPasswordConfirmesField;
    private JLabel errorMessageLabel;
    private JButton changeButton;
    private JButton cancelButton = new JButton("Annuler");

    @PostConstruct
    public void ChangePasswordUI() {
        setTitle("Changer de mot de passe");
        setSize(500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Initialize main panel
        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.setBackground(Color.WHITE);

        // Header Panel with title
        JPanel headerPanel = new JPanel();
        headerPanel.setBackground(new Color(0, 151, 57));
        JLabel headerLabel = new JLabel("Changer de Mot de Passe", JLabel.CENTER);
        headerLabel.setForeground(Color.WHITE);
        headerLabel.setFont(new Font("Arial", Font.BOLD, 24));
        headerPanel.add(headerLabel);

        // Form Panel
        JPanel formPanel = new JPanel(new GridBagLayout());
        formPanel.setBackground(Color.WHITE);
        formPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 2, 10, 10);

        // Password label and text field
        gbc.gridx = 0;
        gbc.gridy = 0;
        formPanel.add(new JLabel("Mot de passe actuel:"), gbc);
        passwordField = new JTextField(15);
        gbc.gridx = 1;
        formPanel.add(passwordField, gbc);

        // New password label and password field
        gbc.gridx = 0;
        gbc.gridy++;
        formPanel.add(new JLabel("Nouveau Mot de passe:"), gbc);
        newPasswordField = new JPasswordField(15);
        gbc.gridx = 1;
        formPanel.add(newPasswordField, gbc);

        // Confirm new password label and password field
        gbc.gridx = 0;
        gbc.gridy++;
        formPanel.add(new JLabel("Confirmer le nouveau Mot de passe:"), gbc);
        newPasswordConfirmesField = new JPasswordField(15);
        gbc.gridx = 1;
        formPanel.add(newPasswordConfirmesField, gbc);

        // Error message label
        errorMessageLabel = new JLabel("Les mots de passe ne correspondent pas");
        errorMessageLabel.setForeground(Color.RED);
        errorMessageLabel.setVisible(false);  // Masquer par défaut
        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 2;
        formPanel.add(errorMessageLabel, gbc);

        // Buttons panel
        JPanel buttonsPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 10, 10));
        changeButton = new JButton("Valider");
        changeButton.setBackground(new Color(10, 125, 239));
        changeButton.setForeground(Color.WHITE);
        changeButton.setBorder(BorderFactory.createRaisedBevelBorder());
        changeButton.setOpaque(true);
        changeButton.setFocusPainted(false);
        changeButton.setBorder(BorderFactory.createEmptyBorder(10, 25, 10, 25));
        changeButton.setFont(new Font("Arial", Font.BOLD, 14));
        changeButton.setCursor(new Cursor(Cursor.HAND_CURSOR));

        cancelButton.setBackground(new Color(239, 71, 10));
        cancelButton.setForeground(Color.WHITE);
        cancelButton.setBorder(BorderFactory.createRaisedBevelBorder());
        cancelButton.setOpaque(true);
        cancelButton.setFocusPainted(false);
        cancelButton.setBorder(BorderFactory.createEmptyBorder(10, 25, 10, 25));
        cancelButton.setFont(new Font("Arial", Font.BOLD, 14));
        cancelButton.setCursor(new Cursor(Cursor.HAND_CURSOR));

        buttonsPanel.add(changeButton);
        buttonsPanel.add(cancelButton);

        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();

            }
        });

        // Add panels to main panel
        mainPanel.add(headerPanel, BorderLayout.NORTH);
        mainPanel.add(formPanel, BorderLayout.CENTER);
        mainPanel.add(buttonsPanel, BorderLayout.SOUTH);

        // Add main panel to frame
        add(mainPanel);
    }


}
