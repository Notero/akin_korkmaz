package com.example.guiweb;

import jakarta.persistence.*;

@Entity
@Table(name = "elements")
public class element {

    @Id
    @GeneratedValue
    private Long id;

    @Column
    private String name;

    @Column
    private Integer atomicNumber;

    @Column
    private Integer dateOfDiscovery;

    @Column
    private String nameOfFounder;

    @Column
    private String color;

    @Column
    private String related_Industries;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getAtomicNumber() {
        return atomicNumber;
    }

    public void setAtomicNumber(Integer atomicNumber) {
        this.atomicNumber = atomicNumber;
    }

    public Integer getDateOfDiscovery() {
        return dateOfDiscovery;
    }

    public void setDateOfDiscovery(Integer dateOfDiscovery) {
        this.dateOfDiscovery = dateOfDiscovery;
    }

    public String getNameOfFounder() {
        return nameOfFounder;
    }

    public void setNameOfFounder(String nameOfFounder) {
        this.nameOfFounder = nameOfFounder;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public String getRelated_Industries() {
        return related_Industries;
    }

    public void setRelated_Industries(String related_Industries) {
        this.related_Industries = related_Industries;
    }

    @Override
    public String toString() {
        return "element{" +
                "name='" + name + '\'' +
                ", atomicNumber=" + atomicNumber +
                ", dateOfDiscovery=" + dateOfDiscovery +
                ", nameOfFounder='" + nameOfFounder + '\'' +
                ", color='" + color + '\'' +
                ", related_Industries='" + related_Industries + '\'' +
                '}';
    }
}
