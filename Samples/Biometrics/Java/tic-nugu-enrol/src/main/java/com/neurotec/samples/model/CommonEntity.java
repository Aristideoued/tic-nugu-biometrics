package com.neurotec.samples.model;



import org.springframework.data.jpa.domain.support.AuditingEntityListener;

import javax.persistence.Column;
import javax.persistence.EntityListeners;
import javax.persistence.MappedSuperclass;
import javax.persistence.PrePersist;
import java.io.Serializable;
import java.time.Instant;
import java.util.Date;


@MappedSuperclass
@EntityListeners(AuditingEntityListener.class)
public abstract class CommonEntity implements Serializable {

    private static final long serialVersionUID = 1L;

    @Column(name = "created_by", nullable = false, length = 50, updatable = false)
    private String createdBy;

    @Column(name = "created_date", updatable = false)
    private Instant createdDate = Instant.now();

    @Column(name = "last_modified_by", length = 50)
    private String lastModifiedBy;

    @Column(name = "last_modified_date")
    private Instant lastModifiedDate = Instant.now();

    private boolean deleted = false;

    public String getCreatedBy() {
        return createdBy;
    }

    public void setCreatedBy(String createdBy) {
       if(createdBy==null){
        this.createdBy = "system";
       }else{
        this.createdBy = createdBy;
       }
       
    }

    public Instant getCreatedDate() {
        return createdDate;
    }

    public void setCreatedDate(Instant createdDate) {
       if(createdDate==null){
        this.createdDate = new Date().toInstant();
       }else{
        this.createdDate = createdDate;
       }
    }

    public String getLastModifiedBy() {
        return lastModifiedBy;
    }

    public void setLastModifiedBy(String lastModifiedBy) {
        this.lastModifiedBy = lastModifiedBy;
    }

    public Instant getLastModifiedDate() {
        return lastModifiedDate;
    }

    public void setLastModifiedDate(Instant lastModifiedDate) {
        this.lastModifiedDate = lastModifiedDate;
    }

    public boolean isDeleted() {
        return deleted;
    }

    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }

    @PrePersist
    void preInsert(){
        if(this.createdBy==null){
            this.createdBy="system";
        }
        if(this.createdDate==null){
            this.createdDate= new Date().toInstant();
        }
    }
    
}

