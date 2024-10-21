package com.neurotec.samples.swing;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoCollection;
import org.bson.Document;
import org.bson.types.Binary;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Base64;

public class Mongo {


    public  byte[] convertToByteArray(BufferedImage image) {
        try (ByteArrayOutputStream baos = new ByteArrayOutputStream()) {
            ImageIO.write(image, "png", baos); // ou "jpg" selon votre format
            return baos.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public  BufferedImage convert(String base64Str) {
        // Decode the Base64 string to byte array
        byte[] decodedBytes = Base64.getDecoder().decode(base64Str);

        try (ByteArrayInputStream bais = new ByteArrayInputStream(decodedBytes)) {
            // Convert byte array to BufferedImage
            return ImageIO.read(bais);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void insertImageToMongoDB(byte[] imageBytes, String doigt) {
        // Connexion à la base de données MongoDB
        String main="";
       String x =doigt.split("_")[0];
       if(x.equals("LEFT")){
           main="Gauche";
       }
       else {
           main="Droite";
       }

       String dg=doigt.split("_")[1];
       if(dg.equals("LITTLE")){
           doigt="Auriculaire";
       }
       else if(dg.equals("RING")){
           doigt="Annulaire";
       }
       else if(dg.equals("MIDDLE")){
           doigt="Majeure";
       }
       else if(dg.equals("INDEX")){
           doigt="Index";
       }
       else if(dg.equals("THUMB")){
           doigt="Pouce";
       }

        try (MongoClient mongoClient = MongoClients.create("mongodb://localhost:27017")) {
            MongoDatabase database = mongoClient.getDatabase("tic-nugu");
            MongoCollection<Document> collection = database.getCollection("fingerprints");

            // Créer un document avec l'image en tant que binaire et son nom
            Document document = new Document("doigt", doigt)
                    .append("main", main)
                    .append("imageData", imageBytes)

                    .append("remoteId", "1");

            // Insérer le document dans la collection
            collection.insertOne(document);
            System.out.println("Image '" + doigt + "' insérée avec succès !");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void insertMunitieToMongoDB(int x,int y, String doigt) {
        // Connexion à la base de données MongoDB
        String main="";
        String x1 =doigt.split("_")[0];
        if(x1.equals("LEFT")){
            main="Gauche";
        }
        else {
            main="Droite";
        }

        String dg=doigt.split("_")[1];
        if(dg.equals("LITTLE")){
            doigt="Auriculaire";
        }
        else if(dg.equals("RING")){
            doigt="Annulaire";
        }
        else if(dg.equals("MIDDLE")){
            doigt="Majeure";
        }
        else if(dg.equals("INDEX")){
            doigt="Index";
        }
        else if(dg.equals("THUMB")){
            doigt="Pouce";
        }

        try (MongoClient mongoClient = MongoClients.create("mongodb://localhost:27017")) {
            MongoDatabase database = mongoClient.getDatabase("tic-nugu");
            MongoCollection<Document> collection = database.getCollection("munities");

            // Créer un document avec l'image en tant que binaire et son nom
            Document document = new Document("doigt", doigt)
                    .append("main", main)
                    .append("x", x)
                    .append("y", y)

                    .append("remoteId", "1");

            // Insérer le document dans la collection
            collection.insertOne(document);
          //  System.out.println("Image '" + doigt + "' insérée avec succès !");
        } catch (Exception e) {
            e.printStackTrace();
        }

}
}

