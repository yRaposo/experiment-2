package com.raposo.experiment.model;

import java.util.List;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.OneToMany;
@Entity
public class Dendro {
    @Id
    private String id;

    private String name;
    private double temperature;
    private int luminosity;
    
    @OneToMany(mappedBy = "dendro")
    private List<Modulo> modules;

    // Constructors
    public Dendro() {
    }

    public Dendro(String id, String name, double temperature, int luminosity) {
        this.id = id;
        this.name = name;
        this.temperature = temperature;
        this.luminosity = luminosity;
        this.modules = modules;
    }

    // Getters and Setters
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getTemperature() {
        return temperature;
    }

    public void setTemperature(double temperature) {
        this.temperature = temperature;
    }

    public int getLuminosity() {
        return luminosity;
    }

    public void setLuminosity(int luminosity) {
        this.luminosity = luminosity;
    }

    public List<Modulo> getModules() {
        return modules;
    }

    public void setModules(List<Modulo> modules) {
        this.modules = modules;
    }
}