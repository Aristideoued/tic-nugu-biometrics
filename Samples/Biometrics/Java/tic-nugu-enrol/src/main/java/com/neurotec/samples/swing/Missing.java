package com.neurotec.samples.swing;

public class Missing {
    private int missingSize;

    public int getMissingSize() {
        return missingSize;
    }

    public void setMissingSize(int missingSize) {
        this.missingSize = missingSize;
    }
    public  boolean activate(int nbTemplate){
       int  nbFinger=10;
       boolean ok=false;
        if((nbFinger-this.missingSize)== nbTemplate){
            ok=  true;
        }
        return  ok;
    }
}
