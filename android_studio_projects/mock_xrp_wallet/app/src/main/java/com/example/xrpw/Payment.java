package com.example.xrpw;

import androidx.room.Entity;
import androidx.room.ForeignKey;
import androidx.room.Index;
import androidx.room.PrimaryKey;

@Entity(tableName = "payment",
        foreignKeys = @ForeignKey(entity = Wallet.class,
                parentColumns = "id",
                childColumns = "walletOwnerId",
                onDelete = ForeignKey.CASCADE),
        indices = {@Index("walletOwnerId")})
public class Payment {

    @PrimaryKey(autoGenerate = true)
    private int id;
    private int walletOwnerId;
    private String amountText;
    private String destinationText;
    private String dateText;

    public Payment(int walletOwnerId, String amountText, String destinationText, String dateText) {
        this.walletOwnerId = walletOwnerId;
        this.amountText = amountText;
        this.destinationText = destinationText;
        this.dateText = dateText;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getWalletOwnerId() {
        return walletOwnerId;
    }

    public void setWalletOwnerId(int walletOwnerId) {
        this.walletOwnerId = walletOwnerId;
    }

    public String getAmountText() {
        return amountText;
    }

    public void setAmountText(String amountText) {
        this.amountText = amountText;
    }

    public String getDestinationText() {
        return destinationText;
    }

    public void setDestinationText(String destinationText) {
        this.destinationText = destinationText;
    }

    public String getDateText() {
        return dateText;
    }

    public void setDateText(String dateText) {
        this.dateText = dateText;
    }
}
