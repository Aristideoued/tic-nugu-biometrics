package com.neurotec.samples.utils;

public class ValidateFieldForm {
    // Validation du téléphone : doit contenir exactement 8 chiffres
    public static boolean validateTelephone(String telephone) {
        return telephone != null && telephone.matches("\\d{8}");
    }

    // Validation de l'email : vérifier le format de l'email
    public static boolean validateEmail(String email) {
        if (email == null || email.isEmpty()) {
            return false; // Si l'email est vide ou null
        }
        String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@[a-zA-Z0-9-]+(?:\\.[a-zA-Z0-9-]+)*$";
        return email.matches(emailRegex);
    }

    // Validation d'un champ requis (non vide)
    public static boolean validateRequiredField(String field) {
        return field != null && !field.trim().isEmpty(); // Vérifie si le champ n'est pas vide
    }

    // Validation d'un mot de passe fort : minimum 8 caractères, au moins une lettre, un chiffre, un caractère spécial
    public static boolean validatePassword(String password) {
        if (password == null || password.length() < 8) {
            return false; // Longueur minimale de 8 caractères
        }
        // Au moins une lettre, un chiffre et un caractère spécial
        String passwordRegex = "^(?=.*[A-Za-z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$";
        return password.matches(passwordRegex);
    }

    // Validation d'un nom d'utilisateur : seulement des lettres et des chiffres, minimum 3 caractères
    public static boolean validateUsername(String username) {
        if (username == null || username.length() < 3) {
            return false;
        }
        return true;
    }

    public static boolean validateNom(String nom) {
        if (nom == null || nom.length() < 3) {
            return false;
        }
        return true;
    }

    public static boolean validatePrenom(String nom) {
        if (nom == null || nom.length() < 3) {
            return false;
        }
        return true;
    }

    // Validation d'un âge (optionnel, si requis)
    public static boolean validateAge(int age) {
        return age >= 18 && age <= 120; // Vérifie si l'âge est dans une fourchette valide
    }

    public static boolean validateMatricule(String matricule) {
        if (matricule == null || matricule.length() < 5) {
            return false;
        }

        return true;
    }

    // Validation d'un identifiant unique (ex: ID utilisateur)
    public static boolean validateUserId(Long id) {
        return id != null && id > 0; // Vérifie que l'identifiant est positif et non nul
    }
}
