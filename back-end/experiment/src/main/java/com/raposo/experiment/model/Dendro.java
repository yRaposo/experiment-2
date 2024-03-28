package com.raposo.experiment.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;

@Entity
public class Dendro {
    @Id
    private Long id;

    private String name;
    private int position;

    public Dendro() {
    }

    public Dendro(Long id, String name, int position) {
        this.id = id;
        this.name = name;
        this.position = position;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPosition() {
        return position;
    }

    public void setPosition(int position) {
        this.position = position;
    }
}
