package com.neurotec.samples.swing.controls;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.Base64;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JToolBar;

import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.neurotec.biometrics.NFRecord;
import com.neurotec.biometrics.NFinger;
import com.neurotec.images.NImage;
import com.neurotec.images.NImageFormat;
import com.neurotec.images.NImages;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.samples.Domain.MongoDBConnection;
import com.neurotec.samples.Utilities;
import com.neurotec.samples.enrollment.EnrollmentSettings;
import com.neurotec.samples.util.Utils;
import org.bson.Document;

public final class FingersViewToolBar extends JToolBar implements ActionListener {

	// ==============================================
	// Private static fields
	// ==============================================

	private static final long serialVersionUID = 1L;

	// ==============================================
	// Private fields
	// ==============================================

	private JButton btnSaveImage;
	private JButton btnSaveRecord;
	private final EnrollmentSettings settings = EnrollmentSettings.getInstance();
	private MongoCollection<Document> fingerprintsCollection;



	// ==============================================
	// Public constructor
	// ==============================================

	public FingersViewToolBar() {
		initializeComponents();
		initializeMongoDB();  // Initialize MongoDB connection using MongoDBConnection

	}

	//////////////////////////////////Méthode d'initialisation de mongoBD/////////////////////////////////////////////

	private void initializeMongoDB() {
		// We use the MongoDBConnection class to get the MongoDB instance and the collection
		MongoDatabase database = MongoDBConnection.getDatabase();
		fingerprintsCollection = database.getCollection("fingerprints");
	}
	// ==============================================
	// Private methods
	// ==============================================

	private void initializeComponents() {
		setFloatable(true);

		btnSaveImage = new JButton("Save Image");
		btnSaveImage.setIcon(Utils.createIcon("images/Save.png"));
		btnSaveImage.addActionListener(this);

		btnSaveRecord = new JButton("Save Record");
		btnSaveRecord.setIcon(Utils.createIcon("images/Save.png"));
		btnSaveRecord.addActionListener(this);




		add(btnSaveImage);
		add(btnSaveRecord);
	}

	private void saveImage() {
		String fileName;
		NImage image;
		NFinger finger = (NFinger) getClientProperty("TAG");
		if (finger != null) {
			boolean originalImage = EnrollmentSettings.getInstance().isShowOriginal() && finger.getPosition().isSingleFinger();
			boolean isRolled = finger.getImpressionType().isRolled();
			image = originalImage ? finger.getImage(false) : finger.getBinarizedImage(false);
			fileName = String.format("%s%s%s", Utilities.convertNFPositionNameToCamelCase(finger.getPosition()), isRolled ? "Rolled" : "", originalImage ? "" : "Binarized");

			JFileChooser saveFileDialog = new JFileChooser();
			saveFileDialog.addChoosableFileFilter(new Utils.ImageFileFilter(NImages.getSaveFileFilterString()));
			saveFileDialog.setSelectedFile(new File(fileName));
			if (settings.getLastDirectory() != null) {
				saveFileDialog.setCurrentDirectory(new File(settings.getLastDirectory()));
			}
			if (saveFileDialog.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
				try {
					String savePath = saveFileDialog.getSelectedFile().getPath();
					settings.setLastDirectory(saveFileDialog.getSelectedFile().getParent().toString());
					if (saveFileDialog.getSelectedFile().getName().lastIndexOf(".") == -1) {
						savePath = savePath + "." + NImageFormat.getJPEG().getDefaultFileExtension();
					}
					image.save(savePath);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}


	public void enregistrerToutesLesEmpreintes(List<NFinger> fingers) {
		for (NFinger finger : fingers) {
			NFRecord record = finger.getObjects().get(0).getTemplate();
			String fingerPosition = Utilities.convertNFPositionNameToCamelCase(finger.getPosition());

			System.out.println("Enregistrement de l'empreinte pour la position: " + fingerPosition);
			System.out.println("Type d'impression: " + finger.getImpressionType().toString());

			saveRecordToMongoDB(record, fingerPosition);
		}
		System.out.println("Toutes les empreintes ont été enregistrées avec succès.");
	}



	// Method to save fingerprint record to MongoDB

	private void saveRecordToMongoDB(NFRecord record, String fingerPosition) {
		NBuffer buffer = record.save();
		byte[] fingerprintData = buffer.toByteArray();
		String fingerprintBase64 = Base64.getEncoder().encodeToString(fingerprintData);

		Document fingerprintDocument = new Document("fingerPosition", fingerPosition)
				.append("fingerprintData", fingerprintBase64);

		fingerprintsCollection.insertOne(fingerprintDocument);
		System.out.println("Fingerprint for position '" + fingerPosition + "' saved to MongoDB successfully.");
	}

	private void saveRecord() {
		NFinger finger = (NFinger) getClientProperty("TAG");
		if (finger != null) {
			NFRecord record = finger.getObjects().get(0).getTemplate();
			String fingerPosition = Utilities.convertNFPositionNameToCamelCase(finger.getPosition());

			System.out.println("Saving fingerprint for finger position: " + fingerPosition);
			System.out.println("Impression type: " + finger.getImpressionType().toString());

			saveRecordToMongoDB(record, fingerPosition);
		} else {
			System.out.println("No fingerprint data available to save.");
		}
	}
	/*private void saveRecord() {
		NFinger finger = (NFinger) getClientProperty("TAG");
		JFileChooser saveFileDialog = new JFileChooser();
		if (finger != null) {
			boolean isRolled = finger.getImpressionType().isRolled();
			saveFileDialog.setSelectedFile(new File(String.format("%s%s", Utilities.convertNFPositionNameToCamelCase(finger.getPosition()), isRolled ? "Rolled" : "")));
			if (settings.getLastDirectory() != null) {
				saveFileDialog.setCurrentDirectory(new File(settings.getLastDirectory()));
			}
			if (saveFileDialog.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
				NFRecord record = finger.getObjects().get(0).getTemplate();
				NBuffer buffer = record.save();
				settings.setLastDirectory(saveFileDialog.getSelectedFile().getParent().toString());
				try {
					NFile.writeAllBytes(saveFileDialog.getSelectedFile().getPath(), buffer);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}*/

//////////////////////////////////////////////////////////////////////////////////////////////
// Modified saveRecord method to save fingerprint in MongoDB
/*private void saveRecord() {
	NFinger finger = (NFinger) getClientProperty("TAG");
	if (finger != null) {
		NFRecord record = finger.getObjects().get(0).getTemplate();
		String fingerPosition = Utilities.convertNFPositionNameToCamelCase(finger.getPosition());

		// Log the fingerprint information
		System.out.println("Saving fingerprint for finger position: " + fingerPosition);
		System.out.println("Impression type: " + finger.getImpressionType().toString());

		// Save the fingerprint record to MongoDB
		saveRecordToMongoDB(record, fingerPosition);
	} else {
		System.out.println("No fingerprint data available to save.");
	}
}*/
/////////////////////////////////////////////////////////////////////////////////////////////////
	// ==============================================
	// Public methods
	// ==============================================


	private List<NFinger> getAllFingers() {
		// Cette méthode doit récupérer toutes les empreintes à partir du composant client
		// Par exemple, cela peut être une liste de NFinger récupérée depuis une source spécifique
		return (List<NFinger>) getClientProperty("TAG");
	}

	public void setSaveRecordVisible(boolean visible) {
		btnSaveRecord.setVisible(visible);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		if (source == btnSaveImage) {
			saveImage();
		} else if (source == btnSaveRecord) {
			saveRecord();
		}
	}



}
