package com.example.xrpw;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.util.UUID;

public class CreateAddWalletActivity extends AppCompatActivity {

    private Button btnAddExistingWallet;
    private Button btnGenerateNewWallet;
    private EditText etSecretKey;
    private EditText etSecretSeed;
    private WalletDao walletDao;
    private EditText initalWalletName;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.create_add_wallet);

        initalWalletName = findViewById(R.id.initalWalletName);
        btnAddExistingWallet = findViewById(R.id.btnAddExistingWallet);
        btnGenerateNewWallet = findViewById(R.id.btnGenerateNewWallet);
        etSecretKey = findViewById(R.id.etSecretKey);
        etSecretSeed = findViewById(R.id.etSecretSeed);

        walletDao = AppDatabase.getInstance(getApplicationContext()).walletDao();

        btnAddExistingWallet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                addExistingWallet();
            }
        });

        btnGenerateNewWallet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                generateNewWallet();
            }
        });
    }

    private void addExistingWallet() {
        String key = etSecretKey.getText().toString().trim();
        String seed = etSecretSeed.getText().toString().trim();

        if (TextUtils.isEmpty(key) || TextUtils.isEmpty(seed)) {
            Toast.makeText(this, "Enter secret key and seed", Toast.LENGTH_SHORT).show();
            return;
        }
        String name;
        if(String.valueOf(initalWalletName.getText()).isEmpty()){
            name = "Wallet " + key.substring(0, 4);
        }else {
            name = String.valueOf(initalWalletName.getText());
        }

        Wallet wallet = new Wallet(name, key + "\n" + seed);
        AppDatabase.databaseWriteExecutor.execute(() -> {
            walletDao.insert(wallet);
            runOnUiThread(() -> {
                Toast.makeText(this, "Existing wallet added", Toast.LENGTH_SHORT).show();
                finish();
            });
        });
    }

    private void generateNewWallet() {

        String key = UUID.randomUUID().toString();
        String seed = UUID.randomUUID().toString();
        String keys = "r" + key.substring(0, 8) + "...\nPUBKEY: " + key + "\nSEED: " + seed;
        String name;
        if(String.valueOf(initalWalletName.getText()).isEmpty()){
            name = "Wallet " + key.substring(0, 4);
        }else {
            name = String.valueOf(initalWalletName.getText());
        }


        Wallet wallet = new Wallet(name, keys);
        AppDatabase.databaseWriteExecutor.execute(() -> {
            walletDao.insert(wallet);
            runOnUiThread(() -> {
                Toast.makeText(this, "New wallet generated", Toast.LENGTH_SHORT).show();
                finish();
            });
        });
    }
}
