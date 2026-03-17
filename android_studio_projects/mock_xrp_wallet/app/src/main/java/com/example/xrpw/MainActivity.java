package com.example.xrpw;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.LiveData;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class MainActivity extends AppCompatActivity implements WalletAdapter.OnWalletClickListener {

    private RecyclerView rvWallets;
    private Button btnAddWallet;
    private Button btnMakePayment;
    private WalletAdapter walletAdapter;
    private WalletDao walletDao;
    private PaymentDao paymentDao;
    private Wallet selectedWallet;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        rvWallets = findViewById(R.id.rvWallets);
        btnAddWallet = findViewById(R.id.btnAddWallet);

        AppDatabase database = AppDatabase.getInstance(getApplicationContext());
        walletDao = database.walletDao();
        paymentDao = database.paymentDao();

        walletAdapter = new WalletAdapter(this);
        rvWallets.setLayoutManager(new LinearLayoutManager(this));
        rvWallets.setAdapter(walletAdapter);

        final long startTime = System.currentTimeMillis();
        LiveData<List<Wallet>> walletLiveData = walletDao.getAllWallets();
        walletLiveData.observe(this, wallets -> {
            walletAdapter.submitList(wallets);
            if (wallets != null && !wallets.isEmpty()) {
                selectedWallet = wallets.get(0);
            }
            long endTime = System.currentTimeMillis();
            Log.d("Performance", "Wallet fetch time: " + (endTime - startTime) + "ms");
        });

        btnAddWallet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this, CreateAddWalletActivity.class);
                startActivity(i);
            }
        });
    }

    @Override
    public void onWalletClick(Wallet wallet) {
        selectedWallet = wallet;
        Intent i = new Intent(this, WalletDetailActivity.class);
        i.putExtra(WalletDetailActivity.EXTRA_WALLET, wallet);
        startActivity(i);
    }

    @Override
    public void onWalletLongClick(Wallet wallet) {
        AppDatabase.databaseWriteExecutor.execute(() -> {
            paymentDao.deletePaymentsForWallet(wallet.getId());
            walletDao.delete(wallet);
        });
        Toast.makeText(this, "Wallet deleted", Toast.LENGTH_SHORT).show();
    }
}
