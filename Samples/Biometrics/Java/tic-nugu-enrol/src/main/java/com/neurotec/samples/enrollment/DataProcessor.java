package com.neurotec.samples.enrollment;

import java.awt.Frame;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFileChooser;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NFAttributes;
import com.neurotec.biometrics.NFinger;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplate;
import com.neurotec.images.NImage;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NFile;
import com.neurotec.samples.Utilities;
import com.neurotec.samples.util.Utils;

import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

public final class DataProcessor {

	// ==============================================
	// Private static fields
	// ==============================================

	private static DataProcessor instance;

	private static final String ROOT_ELEMENT = "EnrollmentResult";
	private static final String INFORMATION_ELEMENT = "Information";
	private static final String INFO_FIELD_ELEMENT = "Info";
	private static final String DATA_ELEMENT = "Data";
	private static final String TEMPLATE_ATTRIBUTE = "Template";
	private static final String DATA_FIELD_ELEMENT = "DataField";
	private static final String POSITION_ATTRIBUTE = "Position";
	private static final String IMPRESSION_ATTRIBUTE = "Impression";
	private static final String CREATE_STRING_ATTRIBUTE = "CreateString";
	private static final String FILE_ATTRIBUTE = "File";

	private static final String TEMPLATE_NAME = "template.data";

	// ==============================================
	// Public static methods
	// ==============================================

	public static DataProcessor getInstance() {
		synchronized (DataProcessor.class) {
			if (instance == null) {
				instance = new DataProcessor();
			}
			return instance;
		}
	}

	// ==============================================
	// Private fields
	// ==============================================

	private final EnrollmentDataModel dataModel = EnrollmentDataModel.getInstance();
	private final EnrollmentSettings settings = EnrollmentSettings.getInstance();

	// ==============================================
	// Private method
	// ==============================================

	private void writeDataField(Document doc, Element dataElement, String dir, NFinger finger) throws IOException {
		Element dataFieldElement = doc.createElement(DATA_FIELD_ELEMENT);
		dataElement.appendChild(dataFieldElement);

		Attr positionAttr = doc.createAttribute(POSITION_ATTRIBUTE);
		positionAttr.setValue(finger.getPosition().toString());
		dataFieldElement.setAttributeNode(positionAttr);
		Attr impressionAttr = doc.createAttribute(IMPRESSION_ATTRIBUTE);
		impressionAttr.setValue(finger.getImpressionType().toString());
		dataFieldElement.setAttributeNode(impressionAttr);

		String name = Utilities.convertNFPositionNameToCamelCase(finger.getPosition());
		String type = finger.getImpressionType().isRolled() ? "Rolled" : "";
		name = name.concat(type);
		name = name.concat(".png");
		String imagePath = dir + Utils.FILE_SEPARATOR + name;
		finger.getImage().save(imagePath);

		Attr fileAttr = doc.createAttribute(FILE_ATTRIBUTE);
		fileAttr.setValue(name);
		dataFieldElement.setAttributeNode(fileAttr);

		for (NFAttributes item : finger.getObjects()) {
			if (item != null && item.getChild() instanceof NFinger) {
				writeDataField(doc, dataFieldElement, dir, (NFinger) item.getChild());
			}
		}

	}

	// ==============================================
	// Public methods
	// ==============================================

	public void save(String dir, String dirName) throws IOException, ParserConfigurationException, TransformerException {

		DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder docBuilder = docFactory.newDocumentBuilder();

		Document doc = docBuilder.newDocument();
		Element rootElement = doc.createElement(ROOT_ELEMENT);
		doc.appendChild(rootElement);

		Element information = doc.createElement(INFORMATION_ELEMENT);
		rootElement.appendChild(information);

		for (InfoField inf : dataModel.getInfo()) {
			if (inf.getKey().equals("Template") || inf.getKey().equals("HashName")) {
				continue;
			}
			Element infoField = doc.createElement(INFO_FIELD_ELEMENT);
			information.appendChild(infoField);

			Attr infAttr = doc.createAttribute(CREATE_STRING_ATTRIBUTE);
			infAttr.setValue(inf.toString());
			infoField.setAttributeNode(infAttr);

			if (inf.getValue() != null) {
				if (inf.getValue() instanceof NImage) {
					String name = inf.getKey() + ".png";
					Attr fileAttr = doc.createAttribute(FILE_ATTRIBUTE);
					fileAttr.setValue(name);
					infoField.setAttributeNode(fileAttr);
					((NImage) inf.getValue()).save(dir + Utils.FILE_SEPARATOR + name);
				} else {
					infoField.appendChild(doc.createTextNode(inf.getValue().toString()));
				}
			}
		}

		if (dataModel.getSubject() != null) {
			Element data = doc.createElement(DATA_ELEMENT);
			rootElement.appendChild(data);
			NBuffer template = null;
			try {
				template = dataModel.getSubject().getTemplateBuffer();
				NFile.writeAllBytes((dir + Utils.FILE_SEPARATOR + TEMPLATE_NAME), template);
				Attr templateAttr = doc.createAttribute(TEMPLATE_ATTRIBUTE);
				templateAttr.setValue(TEMPLATE_NAME);
				data.setAttributeNode(templateAttr);

				for (NFinger finger : dataModel.getSubject().getFingers()) {
					if (finger.getStatus() == NBiometricStatus.OK && finger.getParentObject() == null) {
						writeDataField(doc, data, dir, finger);
					}
				}

			} finally {
				if (template != null) {
					template.dispose();
				}
			}
		}

		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		DOMSource source = new DOMSource(doc);
		StreamResult result = new StreamResult(new File(dir + Utils.FILE_SEPARATOR + dirName + ".xml"));

		transformer.transform(source, result);
	}

	public void saveTemplate(Frame owner) {
		JFileChooser saveFileDialog = new JFileChooser();
		if (dataModel.getSubject() == null) {
			Utilities.showWarning(owner, "Nothing to save");
		} else {
			if (settings.getLastDirectory() != null) {
				saveFileDialog.setCurrentDirectory(new File(settings.getLastDirectory()));
			}
			NTemplate template = dataModel.getSubject().getTemplate();
			if (template.getFingers() == null) {
				Utilities.showWarning(owner, "Nothing to save");
			} else if (saveFileDialog.showSaveDialog(owner) == JFileChooser.APPROVE_OPTION) {
				settings.setLastDirectory(saveFileDialog.getSelectedFile().getParent().toString());
				String savePath = saveFileDialog.getSelectedFile().getPath();
				if (savePath.lastIndexOf(".") == -1) {
					savePath = savePath + ".data";
				}
				NBuffer buffer = template.save();
				try {
					NFile.writeAllBytes(savePath, buffer);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}

	}

	public void saveImages(Frame owner) {
		if (dataModel.getSubject() != null) {
			NSubject subject = dataModel.getSubject();
			List<NFinger> fingers = new ArrayList<NFinger>();
			for (NFinger finger : subject.getFingers()) {
				if (finger.getStatus() == NBiometricStatus.OK) {
					fingers.add(finger);
				}
			}

			if (fingers.size() > 0) {
				JFileChooser folderBrowserDialog = new JFileChooser();
				folderBrowserDialog.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				if (settings.getLastDirectory() != null) {
					folderBrowserDialog.setCurrentDirectory(new File(settings.getLastDirectory()));
				}
				if (folderBrowserDialog.showSaveDialog(owner) != JFileChooser.APPROVE_OPTION) {
					return;
				}
				try {
					String dir = folderBrowserDialog.getSelectedFile().getPath();
					settings.setLastDirectory(dir);
					for (NFinger item : fingers) {
						boolean isRolled = item.getImpressionType().isRolled();
						String name = String.format("%s%s.png", Utilities.convertNFPositionNameToCamelCase(item.getPosition()), isRolled ? "Rolled" : "");
						item.getImage().save(dir + Utils.FILE_SEPARATOR + name);
					}
				} catch (Exception ex) {
					Utilities.showError(owner, ex);
				}
			} else {
				Utilities.showWarning(owner, "Nothing to save");
			}
		} else {
			Utilities.showWarning(owner, "Nothing to save");
		}
	}

	public void saveAll(Frame owner) {
		JFileChooser folderBrowserDialog = new JFileChooser();
		folderBrowserDialog.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		if (settings.getLastDirectory() != null) {
			folderBrowserDialog.setCurrentDirectory(new File(settings.getLastDirectory()));
		}
		if (folderBrowserDialog.showSaveDialog(owner) == JFileChooser.APPROVE_OPTION) {
			File selectedFolder = folderBrowserDialog.getSelectedFile();
			settings.setLastDirectory(selectedFolder.getPath());
			try {
				save(selectedFolder.getPath(), selectedFolder.getName());
			} catch (IOException e) {
				e.printStackTrace();
			} catch (ParserConfigurationException e) {
				e.printStackTrace();
			} catch (TransformerException e) {
				e.printStackTrace();
			}
		}
	}

}
