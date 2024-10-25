package com.neurotec.samples.DAO;


import com.neurotec.samples.config.ChainCon;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
public class ProfilDao {
    private Connection connect() {
        // Remplacez par votre URL de base de données, utilisateur et mot de passe
        String url = "jdbc:postgresql://localhost:5432/votre_base_de_donnees";
        String user = "votre_utilisateur";
        String password = "votre_mot_de_passe";
       //// Connection conn = ChainCon.getConnection();
        Connection conn = null;
        try {
            conn = ChainCon.getConnection();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return conn;
    }

    public List<String> getAllProfils() {
        List<String> profils = new ArrayList<>();
        String sql = "SELECT libelle FROM profil";

        try (Connection conn = connect();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                profils.add(rs.getString("libelle"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return profils;
    }

    public int getProfilIdByLibelle(String libelleProfil) {
        int profilId = -1;
        String query = "SELECT id FROM Profil WHERE libelle = ?";
        try (Connection conn = ChainCon.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, libelleProfil);

            // Exécuter la requête
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    profilId = rs.getInt("id"); // Récupérer l'ID du profil
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return profilId;
    }
}
