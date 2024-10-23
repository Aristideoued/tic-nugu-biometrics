package com.neurotec.samples.swing;

import com.neurotec.samples.util.Utils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginFrame extends JFrame {
    public LoginFrame() {
        // Configurer le cadre
        setTitle("Login");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 200);
        setLocationRelativeTo(null); // Centre le cadre à l'écran

        // Créer le panneau principal
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());

        // Ajouter le logo
        JLabel logoLabel = new JLabel(new ImageIcon("resources/images/Logo1.png")); // Remplace par le chemin de ton logo
        logoLabel.setHorizontalAlignment(SwingConstants.CENTER);
        panel.add(logoLabel, BorderLayout.CENTER);

        JPanel inputPanel = new JPanel(new GridLayout(2, 2));
        inputPanel.add(new JLabel("Nom d'utilisateur:"));
        JTextField usernameField = new JTextField();
        usernameField.setPreferredSize(new Dimension(150, 30)); // Ajuste la taille du champ
        inputPanel.add(usernameField);
        inputPanel.add(new JLabel("Mot de passe:"));
        JPasswordField passwordField = new JPasswordField();
        passwordField.setPreferredSize(new Dimension(150, 30)); // Ajuste la taille du champ
        inputPanel.add(passwordField);

        panel.add(inputPanel, BorderLayout.CENTER);

        // Ajouter le bouton de connexion
        JButton loginButton = new JButton("Se connecter");
        loginButton.setBackground(Color.BLUE); // Définit la couleur de fond à bleu clair
        loginButton.setForeground(Color.WHITE);
        loginButton.setPreferredSize(new Dimension(150, 40)); // Augmente la hauteur du bouton
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(loginButton);
        panel.add(buttonPanel, BorderLayout.SOUTH);

        // Action pour le bouton de connexion
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Créer et afficher le MainFrame
                MainFrame mainFrame = new MainFrame();


                Dimension d = new Dimension(1600, 800);
                mainFrame.setSize(d);
                mainFrame.setMinimumSize(new Dimension(300, 200));
                mainFrame.setPreferredSize(d);

                mainFrame.setResizable(true); // Optionnel, si tu veux empêcher le redimensionnement
                mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                mainFrame.setTitle("Tic-nugu - Login");
                mainFrame.setLocationRelativeTo(null);
                mainFrame.setVisible(true);
                mainFrame.setVisible(true);
                dispose(); // Ferme le LoginFrame
            }
        });

        // Ajouter le panneau principal au cadre
        add(panel);
        setIconImage(Utils.createIconImage("images/Logo16x16.png"));

    }

    public static void main(String[] args) {
        // Créer et afficher le cadre de connexion
        SwingUtilities.invokeLater(() -> {
            LoginFrame loginFrame = new LoginFrame();
            loginFrame.setVisible(true);
        });
    }
}
