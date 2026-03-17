package com.example.xrpw;

import androidx.room.Entity;
import androidx.room.PrimaryKey;

import java.io.Serializable;

@Entity(tableName = "wallet")
public class Wallet implements Serializable {

    @PrimaryKey(autoGenerate = true)
    private int id;
    private String name;
    private String keys; // could hold address / pubkey / seed in simple multiline text

    public Wallet(String name, String keys) {
        this.name = name;
        this.keys = keys;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public String getKeys() {
        return keys;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setKeys(String keys) {
        this.keys = keys;
    }
}
