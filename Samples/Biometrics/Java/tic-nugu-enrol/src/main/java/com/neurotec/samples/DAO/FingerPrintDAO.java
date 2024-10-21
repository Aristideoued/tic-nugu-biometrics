package com.neurotec.samples.DAO;

import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.neurotec.samples.Domain.FingerPrint;
import com.neurotec.samples.Domain.MongoDBConnection;
import org.bson.Document;  // Correction : utilisation de l'import approprié pour MongoDB

public class FingerPrintDAO {
    private MongoDatabase database;

    // Constructeur pour initialiser la connexion à la base MongoDB
    public FingerPrintDAO() {
        this.database = MongoDBConnection.getDatabase();
    }

    // Méthode pour sauvegarder une empreinte digitale dans MongoDB
    public void saveFingerPrint(FingerPrint fingerPrint) {
        // Récupération de la collection MongoDB où les empreintes seront stockées
        MongoCollection<Document> collection = database.getCollection("fingerprints");

        // Création d'un document BSON à partir de l'objet FingerPrint
        Document doc = new Document("_id", fingerPrint.getId())  // Utilisation de l'ID de l'empreinte
                .append("main", fingerPrint.getMain())            // Enregistrement de la main (droite/gauche)
                .append("digit", fingerPrint.getDigit())          // Enregistrement du doigt (index, majeur, etc.)
                .append("commentaire", fingerPrint.getCommentaire()) // Commentaire sur l'empreinte
                .append("remoteID", fingerPrint.getRemoteID());   // Identifiant distant (optionnel)

        // Insertion du document dans la collection MongoDB
        collection.insertOne(doc);
    }
}
