package com.neurotec.samples.ui;

//import com.topaz.sigplus.SigPlus;
import com.neurotec.samples.controller.UtilisateurController;
import com.topaz.sigplus.SigPlusEvent0;
import com.topaz.sigplus.SigPlusListener;
import com.topaz.sigplus.SigPlus;
import lombok.Data;
//import org.springframework.stereotype.Component;
import javax.annotation.PostConstruct;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.beans.Beans;
import java.io.ByteArrayOutputStream;
import java.io.IOException;

@Data
@org.springframework.stereotype.Component
public class SignatureUI extends JFrame {

    SigPlus sigObj = null;
    Thread eventThread;

    private UtilisateurController utilisateurController;

    @PostConstruct
    public void SignatureUI() {
        GridBagLayout gbl = new GridBagLayout();
        GridBagConstraints gc = new GridBagConstraints();
        setLayout(gbl);
        JPanel controlPanel = new JPanel();
        setConstraints(controlPanel, gbl, gc, 0, 0,
                GridBagConstraints.REMAINDER, 1, 0, 0,
                GridBagConstraints.CENTER,
                GridBagConstraints.NONE,0, 0, 0, 0);
        add(controlPanel, gc);



        controlPanel.add(connectionChoice);
        controlPanel.add(connectionTablet);

        Button startButton = new Button("COMMENCER");
        controlPanel.add(startButton);

        Button stopButton = new Button("ARRETER");
        controlPanel.add(stopButton);

        Button clearButton = new Button("EFFACER");
        controlPanel.add(clearButton);

        Button saveSigButton = new Button("ENREGISTRER");
        controlPanel.add(saveSigButton);

        Button loadSigButton = new Button("CHARGER");
        controlPanel.add(loadSigButton);

        controlPanel.add(txtPath);

        Button okButton = new Button("QUITTER");
        controlPanel.add(okButton);

        initConnection();

        try
        {
            ClassLoader cl = (com.topaz.sigplus.SigPlus.class).getClassLoader();
            sigObj = (SigPlus) Beans.instantiate( cl, "com.topaz.sigplus.SigPlus" );




            setConstraints(sigObj, gbl, gc, 0, 1,
                    GridBagConstraints.REMAINDER, 1, 1, 1,
                    GridBagConstraints.CENTER,
                    GridBagConstraints.BOTH, 5, 0, 5, 0);
            add(sigObj, gc);
            sigObj.setSize(100,100);
            sigObj.clearTablet();
            setTitle( "Apposez votre signature" );

            okButton.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    sigObj.setTabletState(0);
                    System.exit(0);
                }
            });

            startButton.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    sigObj.setTabletState(0);
                    sigObj.setTabletState(1);
                }
            });

            stopButton.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    sigObj.setTabletState(0);
                }
            });

            clearButton.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    sigObj.clearTablet();
                }
            });

//	  saveSigButton.addActionListener(new ActionListener(){
//	     public void actionPerformed(ActionEvent e){
//	        boolean blnExport=false;
//	        String path=txtPath.getText();
//                int pathlength=path.length();
//                if(pathlength!=0)
//                {
//		   sigObj.autoKeyStart();
//		   sigObj.setAutoKeyData("Sample Encryption Data");
//		   sigObj.autoKeyFinish();
//                   sigObj.setEncryptionMode(1);
//
////					sigObj.importSigFile("signature.sig");
//
//	           blnExport = sigObj.exportSigFile(txtPath.getText());
//                   if (blnExport==false)
//                     {
//                        System.out.println("Error writing SIG file");
//                     }
//                 }
//                 else
//                 {
//                    System.out.println("Please type in full path information to save file");
//		 }
//              }
//	  });


            saveSigButton.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    String path = txtPath.getText();

                    if (path.isEmpty()) {
                        System.out.println("Please type in full path information to save the file");
                        return;
                    }

                    // Exporter au format binaire (bytes)
                    try {
                        sigObj.autoKeyStart();
                        sigObj.setAutoKeyData("Sample Encryption Data");
                        sigObj.autoKeyFinish();
                        sigObj.setEncryptionMode(1);

                        // Récupérer les données binaires au lieu de les exporter vers un fichier
                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
                        boolean blnExport = sigObj.exportSigFile(String.valueOf(byteStream));

                        if (!blnExport) {
                            System.out.println("Error exporting SIG file in bytes");
                        } else {
                            byte[] binaryData = byteStream.toByteArray();

//                            saveToDatabase(binaryData, "SIG"); // Enregistrer les bytes du fichier SIG dans la BD
                            System.out.println("Signature saved successfully in binary format.");
                        }
                    } catch (Exception ex) {
                        System.out.println("An error occurred while exporting SIG: " + ex.getMessage());
                    }

                    // Exporter au format PNG en bytes
//                    try {
//                        // Suppose que votre signature est dessinée dans un JPanel appelé signaturePanel
//                        BufferedImage signatureImage = new BufferedImage(signaturePanel.getWidth(), signaturePanel.getHeight(), BufferedImage.TYPE_INT_ARGB);
//                        Graphics2D g2d = signatureImage.createGraphics();
//
//                        // Dessiner le contenu du JPanel dans l'image
//                        signaturePanel.paint(g2d);
//                        g2d.dispose();
//
//                        // Convertir l'image en bytes (PNG)
//                        ByteArrayOutputStream pngStream = new ByteArrayOutputStream();
//                        boolean isPngSaved = ImageIO.write(signatureImage, "png", pngStream);
//
//                        if (!isPngSaved) {
//                            System.out.println("Error converting PNG image to bytes");
//                        } else {
//                            byte[] pngData = pngStream.toByteArray();
//                            saveToDatabase(pngData, "PNG"); // Enregistrer les bytes du PNG dans la BD
//                            System.out.println("Signature saved successfully in PNG format.");
//                        }
//                    } catch (IOException ioEx) {
//                        System.out.println("An error occurred while converting PNG: " + ioEx.getMessage());
//                    }
                }
            });


            loadSigButton.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    boolean blnImport=false;
                    String path=txtPath.getText();
                    int pathlength=path.length();
                    if(pathlength!=0)
                    {
                        sigObj.autoKeyStart();
                        sigObj.setAutoKeyData("Sample Encryption Data");
                        sigObj.autoKeyFinish();
                        sigObj.setEncryptionMode(1);
                        blnImport = sigObj.importSigFile(txtPath.getText());
                        if (blnImport==false)
                        {
                            System.out.println("Error reading SIG file");
                        }
                    }
                    else
                    {
                        System.out.println("Please type in full path information to load file");
                    }
                }
            });


            //txtPath.addTextListener(new TextListener(){
            //public void textValueChanged(TextEvent e){
            //System.out.println(txtPath.getText());
            //}
            //});



            connectionTablet.addItemListener(new ItemListener(){
                public void itemStateChanged(ItemEvent e){

                    if(connectionTablet.getSelectedItem() != "SignatureGemLCD4X3"){
                        sigObj.setTabletModel(connectionTablet.getSelectedItem());
                    }
                    else{
                        sigObj.setTabletModel("SignatureGemLCD4X3New"); //properly set up LCD4X3
                    }

                }
            });


            connectionChoice.addItemListener(new ItemListener(){
                public void itemStateChanged(ItemEvent e){

                    if(connectionChoice.getSelectedItem() != "HSB"){
                        sigObj.setTabletComPort(connectionChoice.getSelectedItem());
                    }
                    else{
                        sigObj.setTabletComPort("HID1"); //properly set up HSB tablet
                    }

                }
            });

            addWindowListener( new WindowAdapter()
            {
                public void windowClosing( WindowEvent we )
                {
                    sigObj.setTabletState( 0 );
                    System.exit( 0 );
                }

                public void windowClosed( WindowEvent we )
                {
                    System.exit( 0 );
                }
            } );

            sigObj.addSigPlusListener( new SigPlusListener()
            {
                public void handleTabletTimerEvent( SigPlusEvent0 evt )
                {
                }

                public void handleNewTabletData( SigPlusEvent0 evt )
                {
                }

                public void handleKeyPadData( SigPlusEvent0 evt )
                {
                }
            } );

            setVisible(true);

            sigObj.setTabletModel("SignatureGem1X5");
            sigObj.setTabletComPort("COM1");


        }
        catch ( Exception e )
        {
            return;
        }

    }


    TextField txtPath = new TextField("C:\\Users\\hamid\\Documents\\test.png", 30);

    Choice connectionChoice = new Choice();   protected String[] connections =
            {
                    "COM1",
                    "COM2",
                    "COM3",
                    "COM4",
                    "USB",
                    "HSB",
            };


    Choice connectionTablet = new Choice();   protected String[] tablets =
            {
                    "SignatureGem1X5",
                    "SignatureGem4X5",
                    "SignatureGemLCD1X5",
                    "SignatureGemLCD4X3",
                    "ClipGem",
                    "ClipGemLGL",
            };


    private void initConnection()
    {
        for(int i = 0; i < connections.length; i++)
        {
            connectionChoice.add(connections[i]);
        }

        for(int i = 0; i < tablets.length; i++)
        {
            connectionTablet.add(tablets[i]);
        }

    }

    //Convenience method for GridBagLayout
    private void setConstraints(Component comp, GridBagLayout gbl, GridBagConstraints gc,
            int gridx, int gridy, int gridwidth, int gridheight, int weightx, int weighty,
            int anchor, int fill, int top, int left, int bottom, int right) {
        gc.gridx = gridx;
        gc.gridy = gridy;
        gc.gridwidth = gridwidth;
        gc.gridheight = gridheight;
        gc.weightx = weightx;
        gc.weighty = weighty;
        gc.anchor = anchor;
        gc.fill = fill;
        gc.insets = new Insets(top, left, bottom, right);
        gbl.setConstraints(comp, gc);
    }

}
