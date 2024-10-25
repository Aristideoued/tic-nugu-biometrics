package com.neurotec.samples.utils;

import org.apache.batik.transcoder.TranscoderInput;
import org.apache.batik.transcoder.TranscoderOutput;
import org.apache.batik.transcoder.image.PNGTranscoder;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;

public class SvgUtil {

    // Méthode pour convertir un SVG en PNG
    public static BufferedImage convertSvgToPng(String svgFilePath) {
        try {
            File svgFile = new File(svgFilePath);
            PNGTranscoder transcoder = new PNGTranscoder();
            TranscoderInput input = new TranscoderInput(svgFile.toURI().toString());

            // Utiliser un ByteArrayOutputStream pour capturer la sortie PNG
            ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
            TranscoderOutput output = new TranscoderOutput(byteStream);

            // Transcoder le SVG en PNG
            transcoder.transcode(input, output);

            // Convertir le flux en BufferedImage
            byte[] imageBytes = byteStream.toByteArray();
            ByteArrayInputStream inputStream = new ByteArrayInputStream(imageBytes);
            BufferedImage bufferedImage = ImageIO.read(inputStream);

            return bufferedImage;
        } catch (IOException | org.apache.batik.transcoder.TranscoderException e) {
            e.printStackTrace();
            return null;
        }
    }

    // Méthode pour redimensionner une image
    public static Image resizeImage(BufferedImage originalImage, int targetWidth, int targetHeight) {
        Image resultingImage = originalImage.getScaledInstance(targetWidth, targetHeight, Image.SCALE_SMOOTH);
        BufferedImage outputImage = new BufferedImage(targetWidth, targetHeight, BufferedImage.TYPE_INT_ARGB);

        Graphics2D g2d = outputImage.createGraphics();
        g2d.drawImage(resultingImage, 0, 0, null);
        g2d.dispose();

        return outputImage;
    }

    // Méthode pour appliquer une teinte de couleur sur l'ImageIcon
    public static ImageIcon colorizeIcon(ImageIcon icon, Color color) {
        // Convertir l'ImageIcon en BufferedImage
        Image img = icon.getImage();
        BufferedImage bufferedImage = new BufferedImage(img.getWidth(null), img.getHeight(null), BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = bufferedImage.createGraphics();
        g2d.drawImage(img, 0, 0, null);

        // Appliquer la couleur
        g2d.setComposite(AlphaComposite.SrcAtop);
        g2d.setColor(color);
        g2d.fillRect(0, 0, bufferedImage.getWidth(), bufferedImage.getHeight());
        g2d.dispose();

        // Retourner l'image recolorée en tant qu'ImageIcon
        return new ImageIcon(bufferedImage);
    }
}
