package com.neurotec.samples.repository;

import com.neurotec.samples.model.Profil;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

@Repository
public interface ProfilRepository extends JpaRepository<Profil, Long>, JpaSpecificationExecutor<Profil> {
    Profil getProfilByLibelle(String libelle);
}
