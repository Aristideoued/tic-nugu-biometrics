package com.neurotec.samples.DAO;


import com.neurotec.samples.model.Compte;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

import java.sql.*;
public class CompteDAO {
    BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
    public void save(Connection conn, Compte compte) throws SQLException {
        String query = "INSERT INTO Compte (pro_id, uti_id, username, password, createAt, createBy, flActivated) VALUES (?, ?, ?, ?, ?, ?, ?)";

        try (PreparedStatement pstmt = conn.prepareStatement(query)) {
            BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
            String hashedPassword = passwordEncoder.encode(compte.getPassword());

            pstmt.setLong(1, compte.getProfil().getId());
            pstmt.setLong(2, compte.getUtilisateur().getId());
            pstmt.setString(3, compte.getUsername());
            pstmt.setString(4, hashedPassword);
            pstmt.setTimestamp(5, compte.getCreateAt());
            pstmt.setString(6, compte.getCreateBy());
            pstmt.setBoolean(7, true);

            pstmt.executeUpdate();
        }
    }
}
