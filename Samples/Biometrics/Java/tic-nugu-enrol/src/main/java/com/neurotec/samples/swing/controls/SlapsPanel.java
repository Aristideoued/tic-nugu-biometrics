package com.neurotec.samples.swing.controls;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;
import java.util.Random;

import javax.imageio.ImageIO;
import javax.swing.*;

import com.neurotec.biometrics.NFPosition;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.swing.NFingerView;
import com.neurotec.samples.Utilities;
import com.neurotec.samples.swing.FingerCaptureFrame;
import com.neurotec.samples.swing.GridBagUtils;
import com.neurotec.samples.swing.Missing;
import com.neurotec.samples.swing.Mongo;

public final class SlapsPanel extends JPanel {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================
	private NFingerView nfvLeftFour;
	private NFingerView nfvRightFour;
	private NFingerView nfvThumbs;

	private String directory;


	// ==============================================
	// Public constructor
	// ==============================================

	public SlapsPanel() {
		initializeComponents();
	}

	// ==============================================
	// Private methods
	// ==============================================

	private void initializeComponents() {
		GridBagLayout slapsPanelLayout = new GridBagLayout();
		slapsPanelLayout.rowHeights = new int[] {20, 365};
		setLayout(slapsPanelLayout);

		nfvLeftFour = new NFingerView();
		nfvLeftFour.setAutofit(true);
		JPanel leftPanel = new JPanel(new BorderLayout());
		leftPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		leftPanel.add(nfvLeftFour, BorderLayout.CENTER);
		leftPanel.setPreferredSize(leftPanel.getPreferredSize());
		JScrollPane leftScrollPane = new JScrollPane(leftPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		nfvThumbs = new NFingerView();
		nfvThumbs.setAutofit(true);
		JPanel thumbsPanel = new JPanel(new BorderLayout());
		thumbsPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		thumbsPanel.add(nfvThumbs, BorderLayout.CENTER);
		thumbsPanel.setPreferredSize(thumbsPanel.getPreferredSize());
		JScrollPane thumbScrollPane = new JScrollPane(thumbsPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		nfvRightFour = new NFingerView();
		nfvRightFour.setAutofit(true);
		JPanel rightPanel = new JPanel(new BorderLayout());
		rightPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		rightPanel.add(nfvRightFour, BorderLayout.CENTER);
		rightPanel.setPreferredSize(rightPanel.getPreferredSize());
		JScrollPane rightScrollPane = new JScrollPane(rightPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		GridBagUtils gridBagUtils = new GridBagUtils(GridBagConstraints.BOTH);
		gridBagUtils.setInsets(new Insets(1, 1, 1, 1));

		gridBagUtils.addToGridBagLayout(0, 0, 1, 1, 0.3, 0, this, new JLabel("Quatre doigts de la main gauche"));
		gridBagUtils.addToGridBagLayout(1, 0, this, new JLabel("Pouces"));
		gridBagUtils.addToGridBagLayout(2, 0, this, new JLabel("Quatre doigts de la main droite"));
		gridBagUtils.addToGridBagLayout(0, 1, 1, 1, 0.3, 1, this, leftScrollPane);
		gridBagUtils.addToGridBagLayout(1, 1, this, thumbScrollPane);
		gridBagUtils.addToGridBagLayout(2, 1, this, rightScrollPane);



		JButton saveAllButton = new JButton("Enregistrer toutes les empreintes");
		saveAllButton.setPreferredSize(new Dimension(50, 40));  // Largeur 150, Hauteur 40
	//	saveAllButton.setBackground(Color.LIGHT_GRAY);


	//	saveAllButton.setForeground(Color.WHITE);  // Texte en blanc
		saveAllButton.setEnabled(true);
		saveAllButton.setBackground(new Color(0, 128, 255));  // Bleu clair
		// Créer des contraintes spécifiques pour le bouton
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = 1;  // Colonne
		gbc.gridy = 2;  // Ligne
		gbc.gridwidth = 1;  // Largeur sur une colonne
		gbc.gridheight = 1;  // Hauteur sur une ligne
		gbc.anchor = GridBagConstraints.CENTER;  // Centre le bouton
		gbc.fill = GridBagConstraints.HORIZONTAL;  // Le bouton s'étend horizontalement
		gbc.weightx = 1.0;  // Permet au bouton de s'étendre horizontalement en fonction de l'espace disponible
		gbc.insets = new Insets(10, 10, 10, 10);  // Marges autour du bouton

		add(saveAllButton, gbc);  // Ajout du bouton avec les nouvelles contraintes

		saveAllButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				saveAllFingerprints();
			}
		});
		//gridBagUtils.addToGridBagLayout(1, 2, this, saveAllButton);
	}

	public String getDirectory(){
		return  this.directory;
	}

	public  void setDirectory(String d){
		this.directory=d;
	}
	private void saveAllFingerprints() {


		Missing mss=new Missing();
		FingerCaptureFrame fgf =new FingerCaptureFrame(new Frame());




        if(fgf.getSubject() !=null && fgf.getSubject().getTemplate().getFingers()!=null){


			if((10-fgf.getSubject().getMissingFingers().size())==fgf.getSubject().getTemplate().getFingers().getRecords().size()){
				Mongo mg=new Mongo();
				setDirectory(createRandomDirectory());


				fgf.getSubject().getTemplate().getFingers().getRecords().forEach(element -> {
					System.out.println("<=======================Nombre de munities par doigt="+element.getMinutiae().size());

					for (int i=0;i<element.getMinutiae().size();i++){
						mg.insertMunitieToMongoDB(element.getMinutiae().get(i).x,element.getMinutiae().get(i).y,element.getPosition().toString());

					}

				});

				System.out.println("<=======================Nombre de doigt="+fgf.getSubject().getFingers().size());


				for (int i=0;i<fgf.getSubject().getFingers().size();i++){
					System.out.println("<=======================Nom de doigt="+fgf.getSubject().getFingers().get(i).getPosition().toString());

					if(fgf.getSubject().getFingers().get(i).getBinarizedImage(true)!=null){
						try {
							convertBase64ToPNG(convertToBase64(fgf.getSubject().getFingers().get(i).getImage().toImage(),"png"),fgf.getSubject().getFingers().get(i).getPosition().toString());
						} catch (IOException e) {
							throw new RuntimeException(e);
						}
						mg.insertImageToMongoDB(mg.convertToByteArray(mg.convert(convertToBase64(fgf.getSubject().getFingers().get(i).getImage().toImage(),"png"))),fgf.getSubject().getFingers().get(i).getPosition().toString());

					}
				}
				Utilities.showWarning(this, "Sauvegarde effectuée avec succès");

			//	System.out.println( "Nombre de doigts manquants dans save all: "+fgf.getSubject().getMissingFingers().size());

			//	System.out.println( "Nombre de doigts enregistrés  dans save all: "+fgf.getSubject().getTemplate().getFingers().getRecords().size());



			}
			else {
				Utilities.showWarning(this, "Veuillez prendre les empreintes de tous les doigts disponibles");

			}

		}
		else{
			Utilities.showWarning(this, "Veuillez prendre les empreintes de tous les doigts disponibles");


		}





	}

	public  void convertBase64ToPNG(String base64String, String fileName) throws IOException {
		// Retirer le préfixe si présent (par exemple, "data:image/png;base64,")
		if (base64String.startsWith("data:image/png;base64,")) {
			base64String = base64String.substring("data:image/png;base64,".length());
		}

		String main;
		String nomFichier="";
		String x1 =fileName.split("_")[0];
		if(x1.equals("LEFT")){
			main="Gauche"+".png";
		}
		else {
			main="Droite"+".png";
		}

		String dg=fileName.split("_")[1];
		if(dg.equals("LITTLE")){
			nomFichier="Auriculaire_"+main;
		}
		else if(dg.equals("RING")){
			nomFichier="Annulaire_"+main;
		}
		else if(dg.equals("MIDDLE")){
			nomFichier="Majeure_"+main;
		}
		else if(dg.equals("INDEX")){
			nomFichier="Index_"+main;
		}
		else if(dg.equals("THUMB")){
			nomFichier="Pouce_"+main;
		}

		// Décoder la chaîne Base64
		byte[] imageBytes = Base64.getDecoder().decode(base64String);

		File dir = new File(getDirectory());
		// Écrire les octets dans un fichier
		/*try (FileOutputStream fos = new FileOutputStream(getDirectory()+fileName)) {
			fos.write(imageBytes);
		}*/
		try (FileOutputStream fos = new FileOutputStream(new File(dir, nomFichier))) {
			fos.write(imageBytes);
		}
	}

	public  String convertToBase64(Image img, String formatName) {
		// Convert Image to BufferedImage
		BufferedImage bufferedImage = new BufferedImage(img.getWidth(null), img.getHeight(null), BufferedImage.TYPE_INT_ARGB);
		bufferedImage.getGraphics().drawImage(img, 0, 0, null);

		// Convert BufferedImage to Base64
		try (ByteArrayOutputStream baos = new ByteArrayOutputStream()) {
			ImageIO.write(bufferedImage, formatName, baos);
			byte[] imageBytes = baos.toByteArray();
			return Base64.getEncoder().encodeToString(imageBytes);
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}


	public static String createRandomDirectory() {
		// Générer un Long aléatoire
		Random random = new Random();
		long randomLong = Math.abs(random.nextLong());

		// Créer le nom du dossier
		String directoryName = String.valueOf(randomLong);

		// Créer le dossier
		File directory = new File(directoryName);
		if (!directory.exists()) {
			if (directory.mkdir()) {
				System.out.println("Dossier créé : " + directoryName);
			} else {
				System.out.println("Échec de la création du dossier : " + directoryName);
			}
		} else {
			System.out.println("Le dossier existe déjà : " + directoryName);
		}

		return directoryName; // Retourne le nom du dossier
	}
	// ==============================================
	// Public methods
	// ==============================================
////////////////////////////Ajout de boutton EnregistrerTout/////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
	public NFingerView getView(NFPosition position) {
		if (position == NFPosition.PLAIN_LEFT_FOUR_FINGERS) {
			return nfvLeftFour;
		} else if (position == NFPosition.PLAIN_RIGHT_FOUR_FINGERS) {
			return nfvRightFour;
		} else if (position == NFPosition.PLAIN_THUMBS) {
			return nfvThumbs;
		} else {
			return null;
		}
	}

}
