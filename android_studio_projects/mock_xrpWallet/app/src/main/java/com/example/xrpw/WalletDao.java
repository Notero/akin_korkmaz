package com.example.xrpw;

import androidx.lifecycle.LiveData;
import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;
import androidx.room.Update;

import java.util.List;

@Dao
public interface WalletDao {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    long insert(Wallet wallet);

    @Update
    void update(Wallet wallet);

    @Delete
    void delete(Wallet wallet);

    @Query("SELECT * FROM wallet ORDER BY id DESC")
    LiveData<List<Wallet>> getAllWallets();

    @Query("SELECT * FROM wallet WHERE id = :id LIMIT 1")
    Wallet getWalletById(int id);
}
