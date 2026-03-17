package com.example.xrpw;

import androidx.lifecycle.LiveData;
import androidx.room.Dao;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;

import java.util.List;

@Dao
public interface PaymentDao {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    long insert(Payment payment);

    @Query("SELECT * FROM payment WHERE walletOwnerId = :walletId ORDER BY id DESC")
    LiveData<List<Payment>> getPaymentsForWallet(int walletId);

    @Query("DELETE FROM payment WHERE walletOwnerId = :walletId")
    void deletePaymentsForWallet(int walletId);

    @Query("DELETE FROM payment WHERE id = :paymentId")
    void deletePayment(int paymentId);
}
