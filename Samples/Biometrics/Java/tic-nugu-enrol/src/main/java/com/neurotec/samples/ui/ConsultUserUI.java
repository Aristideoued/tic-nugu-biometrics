package com.neurotec.samples.ui;


import com.neurotec.samples.Services.CompteService;
import com.neurotec.samples.controller.UtilisateurController;
import com.neurotec.samples.model.Compte;
import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import org.springframework.stereotype.Component;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableRowSorter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import lombok.Data;
@Data

@Component
@NoArgsConstructor(force = true)
@AllArgsConstructor
public class ConsultUserUI  extends JFrame {


    private JTable table;
    private DefaultTableModel tableModel;
    private JTextField searchField;
//    private Connection connection;
    private TableRowSorter<DefaultTableModel> sorter;
    JButton modifyButton = new JButton("Modifier");
    JButton deleteButton = new JButton("Supprimer");
    JButton annulerButton = new JButton("Fermer");
    JButton actdesacButton = new JButton("Activer/desactiver");
    JButton reinitialiser = new JButton("Reinitialiser");

    private UtilisateurController utilisateurController ;
    private final CompteService compteService ;



    public ConsultUserUI(CompteService compteService) {
        this.compteService = compteService;

        setTitle("Gestion des Informations depuis PostgreSQL");
        setSize(600, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        //.revalidate();
       // consultUserUI.repaint();

        // Colonnes du tableau
      String[] columns = { "ID","Profil", "Username", "Matricule", "Nom", "Prenom", "Tel", "Email"};
        tableModel = new DefaultTableModel(columns, 0);
        tableModel.fireTableDataChanged();
        table = new JTable(tableModel);
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        // Appliquer un TableRowSorter pour permettre le filtrage
        sorter = new TableRowSorter<>(tableModel);
        table.setRowSorter(sorter);
        //this.loadAll();
       this.refreshTable();
        // Charger les données depuis la base de données
       // loadDataFromDatabase();

        // Barre de recherche
        searchField = new JTextField(15);

        // Ajout d'un DocumentListener pour filtrer en temps réel
        searchField.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                filterTable();
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                filterTable();
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                filterTable();
            }

            // Filtrer les résultats du tableau
            private void filterTable() {
                String searchText = searchField.getText().trim().toLowerCase();
                if (searchText.length() == 0) {
                    sorter.setRowFilter(null); // Affiche tout si la barre de recherche est vide
                } else {
                    sorter.setRowFilter(RowFilter.regexFilter("(?i)" + searchText, 2)); // Filtrer sur la colonne Username (index 2)
                }
            }
        });

        JPanel searchPanel = new JPanel();
        searchPanel.add(new JLabel("Rechercher par username :"));
        searchPanel.add(searchField);

        // Boutons de modification et de suppression
        modifyButton.addActionListener(new ModifyListener());

        deleteButton.addActionListener(new DeleteListener());
        actdesacButton.addActionListener(new ActiverdesactiverListener());
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(modifyButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(annulerButton);
        buttonPanel.add(actdesacButton);
        buttonPanel.add(reinitialiser);
        annulerButton.addActionListener(e -> dispose()); // Fermer la fenêtre


        add(new JScrollPane(table), BorderLayout.CENTER);
        add(searchPanel, BorderLayout.NORTH);
        add(buttonPanel, BorderLayout.SOUTH);
       // loadAll();
    }

    // Charger les données depuis PostgreSQL
  /*  private void loadDataFromDatabase() {
        try {
            String query = "SELECT compte.id as compte_id, utilisateur.id as utilisateur_id, username, matricule, nom, prenom, telephone, email " +
                    "FROM compte JOIN utilisateur ON compte.uti_id = utilisateur.id;";
            Statement stmt = connection.createStatement();
            ResultSet rs = stmt.executeQuery(query);

            while (rs.next()) {
                int compteId = rs.getInt("compte_id");
                int utilisateurId = rs.getInt("utilisateur_id");
                String username = rs.getString("username");
                String matricule = rs.getString("matricule");
                String nom = rs.getString("nom");
                String prenom = rs.getString("prenom");
                String tel = rs.getString("telephone");
                String email = rs.getString("email");

                tableModel.addRow(new Object[]{compteId, utilisateurId, username, matricule, nom, prenom, tel, email});
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }*/


    /*public void loadAll(){
        String[] columns = {"ID Compte", "ID Utilisateur", "Username", "Matricule", "Nom", "Prenom", "Tel", "Email"};
        tableModel = new DefaultTableModel(columns, 0);
        table = new JTable(tableModel);
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        // Appliquer un TableRowSorter pour permettre le filtrage
        sorter = new TableRowSorter<>(tableModel);
        table.setRowSorter(sorter);
        List<Compte> compteAll=utilisateurController.loadAll();

        for(Compte compte : compteAll){
            tableModel.addRow(new Object[]{compte.getId(), compte.getUtilisateur().getId(), compte.getUsername(), compte.getUtilisateur().getMatricule(), compte.getUtilisateur().getNom(), compte.getUtilisateur().getPrenom(), compte.getUtilisateur().getTelephone(), compte.getUtilisateur().getEmail()});

        }
    }*/
    public void refreshTable() {
        // Effacer les anciennes données du modèle de la table
        tableModel.setRowCount(0);

        // Recharger toutes les données depuis la base de données
        List<Compte> compteAll = compteService.findAllCompte();
        for (Compte compte : compteAll) {
            tableModel.addRow(new Object[]{compte.getId(), compte.getProfil().getLibelle(), compte.getUsername(), compte.getUtilisateur().getMatricule(), compte.getUtilisateur().getNom(), compte.getUtilisateur().getPrenom(), compte.getUtilisateur().getTelephone(), compte.getUtilisateur().getEmail()});
        }
    }
    public void loadAll(){
       /* String[] columns = {"ID Compte", "ID Utilisateur", "Username", "Matricule", "Nom", "Prenom", "Tel", "Email"};
        tableModel = new DefaultTableModel(columns, 0);
         table = new JTable(tableModel);
        //consultUserUI.getTable().setTableHeader();
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        // Appliquer un TableRowSorter pour permettre le filtrage
        sorter = new TableRowSorter<>(tableModel);
        table.setRowSorter(sorter);*/

        List<Compte> compteAll=compteService.findAllCompte();

        for(Compte compte : compteAll){
            tableModel.addRow(new Object[]{compte.getId(),compte.getProfil().getLibelle(), compte.getUsername(), compte.getUtilisateur().getMatricule(), compte.getUtilisateur().getNom(), compte.getUtilisateur().getPrenom(), compte.getUtilisateur().getTelephone(), compte.getUtilisateur().getEmail()});

        }
    }

    private void supprimer(Long id){
        compteService.delete(id);
    }
    // Listener pour la modification
    private class ModifyListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            int selectedRow = table.getSelectedRow();
            if (selectedRow != -1) {
                // Récupérer les valeurs de la ligne sélectionnée
                Long compteId = (Long) tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 0);
               // int utilisateurId = (int) tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 1);
                String username = tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 2).toString();
                String matricule = tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 3).toString();
                String nom = tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 4).toString();
                String prenom = tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 5).toString();
                String tel = tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 6).toString();
                String email = tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 7).toString();

                // Afficher la fenêtre de modification
                showModifyDialog(compteId, username, matricule, nom, prenom, tel, email);
            } else {
                JOptionPane.showMessageDialog(null, "Veuillez sélectionner une ligne à modifier.");
            }
        }
    }

    // Fenêtre de modification
    private void showModifyDialog(Long compteId, String username, String matricule, String nom, String prenom, String tel, String email) {
        JDialog modifyDialog = new JDialog(this, "Modifier les informations", true);
        modifyDialog.setSize(400, 300);
        modifyDialog.setLayout(new GridLayout(8, 2));

        JTextField usernameField = new JTextField(username);
        JTextField matriculeField = new JTextField(matricule);
        JTextField nomField = new JTextField(nom);
        JTextField prenomField = new JTextField(prenom);
        JTextField telField = new JTextField(tel);
        JTextField emailField = new JTextField(email);

        modifyDialog.add(new JLabel("Username:"));
        modifyDialog.add(usernameField);
        modifyDialog.add(new JLabel("Matricule:"));
        modifyDialog.add(matriculeField);
        modifyDialog.add(new JLabel("Nom:"));
        modifyDialog.add(nomField);
        modifyDialog.add(new JLabel("Prenom:"));
        modifyDialog.add(prenomField);
        modifyDialog.add(new JLabel("Téléphone:"));
        modifyDialog.add(telField);
        modifyDialog.add(new JLabel("Email:"));
        modifyDialog.add(emailField);

        JButton saveButton = new JButton("Enregistrer");
        modifyDialog.add(saveButton);

        saveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Mettre à jour les informations dans la base de données
                updateDatabase(compteId, usernameField.getText(), matriculeField.getText(), nomField.getText(), prenomField.getText(), telField.getText(), emailField.getText());
                // Mettre à jour le modèle de la table
                tableModel.setValueAt(usernameField.getText(), table.convertRowIndexToModel(table.getSelectedRow()), 2);
                tableModel.setValueAt(matriculeField.getText(), table.convertRowIndexToModel(table.getSelectedRow()), 3);
                tableModel.setValueAt(nomField.getText(), table.convertRowIndexToModel(table.getSelectedRow()), 4);
                tableModel.setValueAt(prenomField.getText(), table.convertRowIndexToModel(table.getSelectedRow()), 5);
                tableModel.setValueAt(telField.getText(), table.convertRowIndexToModel(table.getSelectedRow()), 6);
                tableModel.setValueAt(emailField.getText(), table.convertRowIndexToModel(table.getSelectedRow()), 7);
                modifyDialog.dispose();
            }
        });

        modifyDialog.setVisible(true);
    }

    // Mettre à jour la base de données
    private void updateDatabase(Long compteId, String username, String matricule, String nom, String prenom, String tel, String email) {
    //mise a jour de compte
    Compte compte =compteService.findById(compteId);
    compte.setUsername(username);
    compte.getUtilisateur().setMatricule(matricule);
    compte.getUtilisateur().setNom(nom);
    compte.getUtilisateur().setPrenom(prenom);
    compte.getUtilisateur().setTelephone(tel);
    compte.getUtilisateur().setEmail(email);
    Compte compte1=compteService.update(compte);
    //mise a jour de utilisateur





    }

    // Listener pour la suppression
   private class DeleteListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            int selectedRow = table.getSelectedRow();
            if (selectedRow != -1) {
                Long compteId = (Long) tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 0);
               // int utilisateurId = (int) tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 1);
               // deleteFromDatabase(compteId, utilisateurId);
                //Long longTen = Long. valueOf(compteId);
                supprimer(compteId);
                tableModel.removeRow(table.convertRowIndexToModel(selectedRow));
            } else {
                JOptionPane.showMessageDialog(null, "Veuillez sélectionner une ligne à supprimer.");
            }
        }

        // Supprimer de la base de données
    /*   private void deleteFromDatabase(int compteId, int utilisateurId) {
            try {
                // Suppression de la table compte
                String deleteCompteQuery = "DELETE FROM compte WHERE id = ?";
                PreparedStatement pstmtCompte = connection.prepareStatement(deleteCompteQuery);
                pstmtCompte.setInt(1, compteId);
                pstmtCompte.executeUpdate();

                // Suppression de la table utilisateur
                String deleteUtilisateurQuery = "DELETE FROM utilisateur WHERE id = ?";
                PreparedStatement pstmtUtilisateur = connection.prepareStatement(deleteUtilisateurQuery);
                pstmtUtilisateur.setInt(1, utilisateurId);
                pstmtUtilisateur.executeUpdate();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }*/
}

    private class ActiverdesactiverListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            int selectedRow = table.getSelectedRow();
            if (selectedRow != -1) {
                Long compteId = (Long) tableModel.getValueAt(table.convertRowIndexToModel(selectedRow), 0);
                Compte compte=compteService.findById(compteId);
                 if(compte.isFlActivated()){
                     compte.setFlActivated(false);
                     compteService.update(compte);
                     JOptionPane.showMessageDialog(null, "Le compte a été désactiver.");

                 }else {
                     compte.setFlActivated(true);
                     compteService.update(compte);
                     JOptionPane.showMessageDialog(null, "Le compte a été activer.");

                 }

                //supprimer(compteId);
                //tableModel.removeRow(table.convertRowIndexToModel(selectedRow));
            } else {
                JOptionPane.showMessageDialog(null, "Veuillez sélectionner une ligne à supprimer.");
            }
        }


    }
}