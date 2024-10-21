package com.neurotec.samples.Domain;

public class FingerPrint {
    private String id;           // Identifiant unique de l'empreinte (généré ou récupéré)
    private String main;         // Main (droite ou gauche)
    private String digit;        // Doigt (index, majeur, etc.)
    private String commentaire;  // Commentaire ou description (facultatif)
    private String remoteID;     // ID distant (pour la synchronisation avec des systèmes externes)

    // Constructeur par défaut
    public FingerPrint() {}

    // Constructeur avec paramètres
    public FingerPrint(String id, String main, String digit, String commentaire, String remoteID) {
        this.id = id;
        this.main = main;
        this.digit = digit;
        this.commentaire = commentaire;
        this.remoteID = remoteID;
    }

    // Getters et Setters
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getMain() {
        return main;
    }

    public void setMain(String main) {
        this.main = main;
    }

    public String getDigit() {
        return digit;
    }

    public void setDigit(String digit) {
        this.digit = digit;
    }

    public String getCommentaire() {
        return commentaire;
    }

    public void setCommentaire(String commentaire) {
        this.commentaire = commentaire;
    }

    public String getRemoteID() {
        return remoteID;
    }

    public void setRemoteID(String remoteID) {
        this.remoteID = remoteID;
    }

    // Méthode toString pour afficher les informations d'une empreinte
    @Override
    public String toString() {
        return "FingerPrint{" +
                "id='" + id + '\'' +
                ", main='" + main + '\'' +
                ", digit='" + digit + '\'' +
                ", commentaire='" + commentaire + '\'' +
                ", remoteID='" + remoteID + '\'' +
                '}';
    }
}
