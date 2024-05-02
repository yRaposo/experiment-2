package com.raposo.experiment.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;

@Entity
public class Dendro {
    @Id
    private String id;

    private String name;
    private double temperature;
    private double humidity;
    private double light;

    public Dendro() {
    }

    public Dendro(String id, String name, double temperature, double humidity, double light) {
        this.id = id;
        this.name = name;
        this.temperature = temperature;
        this.humidity = humidity;
        this.light = light;
        
    }

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

    public double getHumidity() {
        return humidity;
    }

    public void setHumidity(double humidity) {
        this.humidity = humidity;
    }

    public double getLight() {
        return light;
    }

    public void setLight(double light) {
        this.light = light;
    }
}
