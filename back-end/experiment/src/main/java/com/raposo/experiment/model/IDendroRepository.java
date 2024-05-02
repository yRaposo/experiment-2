package com.raposo.experiment.model;

import org.springframework.data.jpa.repository.JpaRepository;
import java.util.List;
import java.util.Optional;


public interface IDendroRepository extends JpaRepository<Dendro, String>{
    public Optional<Dendro> findById(String id);
    
    public List<Dendro> findByName(String name);
}
