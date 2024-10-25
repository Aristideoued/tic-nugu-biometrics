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
    private JLabel imageLabel;
    private JButton ChangeButton;
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

        // Create the login form panel
        JPanel formPanel = new JPanel(new GridBagLayout());
        formPanel.setBackground(Color.WHITE);
        formPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 2, 10, 10);

        // Add password label and text field
        gbc.gridx = 0;
        gbc.gridy = 0;
        formPanel.add(new JLabel("Mot de passe actuel:"), gbc);
        passwordField = new JTextField(15);
        gbc.gridx = 1;
        formPanel.add(passwordField, gbc);

        // Add password label and password field
        gbc.gridx = 0;
        gbc.gridy++;
        formPanel.add(new JLabel("Nouveau Mot de passe:"), gbc);
        newPasswordField = new JPasswordField(15);
        gbc.gridx = 1;
        formPanel.add(newPasswordField, gbc);

        // Add password label and password field
        gbc.gridx = 0;
        gbc.gridy++;
        formPanel.add(new JLabel("Confirmer le nouveau Mot de passe:"), gbc);
        newPasswordConfirmesField = new JPasswordField(15);
        gbc.gridx = 1;
        formPanel.add(newPasswordConfirmesField, gbc);

        // Add connection button
        ChangeButton = new JButton("Valider");
        ChangeButton.setBackground(new Color(10, 125, 239));
        ChangeButton.setForeground(Color.BLUE);
        ChangeButton.setBorder(BorderFactory.createRaisedBevelBorder());
        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 1;
        formPanel.add(ChangeButton, gbc);

        cancelButton.setBackground(new Color(239, 71, 10));
        cancelButton.setForeground(Color.BLUE);
        cancelButton.setBorder(BorderFactory.createRaisedBevelBorder());
        gbc.gridx = 0;
        gbc.gridy++;
        gbc.gridwidth = 1;
        formPanel.add(cancelButton, gbc);

        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();

            }
        });

        // Add form panel to main panel
        mainPanel.add(formPanel, BorderLayout.CENTER);
        add(mainPanel);
    }


}
