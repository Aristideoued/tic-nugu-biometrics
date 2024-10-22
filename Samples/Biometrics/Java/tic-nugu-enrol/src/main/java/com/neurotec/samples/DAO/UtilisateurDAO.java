package com.neurotec.samples.DAO;


import com.neurotec.samples.model.Utilisateur;

import java.sql.*;
import java.time.LocalDateTime;

public class UtilisateurDAO {
    private final String DB_URL = "jdbc:mysql://localhost:3306/votre_base_de_donnees";
    private final String USER = "root";  // Remplacez par votre utilisateur de base de données
    private final String PASS = "mot_de_passe";  // Remplacez par votre mot de passe

    public long save(Connection conn, Utilisateur utilisateur) throws SQLException {
        String query = "INSERT INTO Utilisateur (matricule, nom, prenom, telephone, email, createAt, createBy) VALUES (?, ?, ?, ?, ?, ?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            pstmt.setString(1, utilisateur.getMatricule());
            pstmt.setString(2, utilisateur.getNom());
            pstmt.setString(3, utilisateur.getPrenom());
            pstmt.setString(4, utilisateur.getTelephone());
            pstmt.setString(5, utilisateur.getEmail());
            pstmt.setTimestamp(6, utilisateur.getCreateAt());
            pstmt.setString(7, utilisateur.getCreateBy());

            pstmt.executeUpdate();

            try (ResultSet rs = pstmt.getGeneratedKeys()) {
                if (rs.next()) {
                    return rs.getLong(1); // Retourne l'ID généré
                }
            }
        }
        return -1;  // Échec
    }
}
