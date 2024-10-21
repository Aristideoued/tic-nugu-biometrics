package com.neurotec.samples.swing;

public class Missing {
    private int missingSize;
    private int nbTemplate;

    public int getMissingSize() {
        return missingSize;
    }

    public void setMissingSize(int missingSize) {
        this.missingSize = missingSize;
    }


    public int getNbTemplate() {
        return nbTemplate;
    }

    public void setNbTemplate(int nbt) {
        this.nbTemplate = nbt;
    }
    public  boolean activate(){
       int  nbFinger=10;
       boolean ok=false;
        if((nbFinger-this.missingSize)== this.nbTemplate){
            ok=  true;
        }
        return  ok;
    }
}
