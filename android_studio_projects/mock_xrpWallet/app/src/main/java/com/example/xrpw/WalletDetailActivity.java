package com.example.xrpw;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class WalletDetailActivity extends AppCompatActivity {

    public static final String EXTRA_WALLET = "extra_wallet";

    private TextView tvWalletTitle;
    private TextView tvWalletKeys;
    private EditText etRenameWallet;
    private Button btnRenameWallet;
    private Button btnDeleteWallet;
    private Button btnAddPayment;
    private RecyclerView rvPayments;

    private Wallet wallet;
    private PaymentAdapter paymentAdapter;
    private PaymentDao paymentDao;
    private WalletDao walletDao;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.wallet_detail);

        // From included wallet card
        tvWalletTitle = findViewById(R.id.tvWalletTitle);
        tvWalletKeys = findViewById(R.id.tvWalletKeys);

        etRenameWallet = findViewById(R.id.etRenameWallet);
        btnRenameWallet = findViewById(R.id.btnRenameWallet);
        btnDeleteWallet = findViewById(R.id.btnDeleteWallet);
        btnAddPayment = findViewById(R.id.btnAddPayment);
        rvPayments = findViewById(R.id.rvPayments);

        wallet = (Wallet) getIntent().getSerializableExtra(EXTRA_WALLET);
        if (wallet == null) {
            Toast.makeText(this, "Wallet not found", Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        tvWalletTitle.setText(wallet.getName());
        tvWalletKeys.setText(wallet.getKeys());

        AppDatabase database = AppDatabase.getInstance(getApplicationContext());
        paymentDao = database.paymentDao();
        walletDao = database.walletDao();

        paymentAdapter = new PaymentAdapter(this::deletePayment);
        rvPayments.setLayoutManager(new LinearLayoutManager(this));
        rvPayments.setAdapter(paymentAdapter);

        paymentDao.getPaymentsForWallet(wallet.getId()).observe(this, payments ->
                paymentAdapter.submitList(payments));

        btnRenameWallet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                renameWallet();
            }
        });

        btnDeleteWallet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                deleteWallet();
            }
        });

        btnAddPayment.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(WalletDetailActivity.this, TransactionActivity.class);
                i.putExtra(TransactionActivity.EXTRA_WALLET_ID, wallet.getId());
                startActivity(i);
            }
        });
    }

    private void deletePayment(Payment payment) {
        AppDatabase.databaseWriteExecutor.execute(() -> {
            paymentDao.deletePayment(payment.getId());
            runOnUiThread(() -> Toast.makeText(this,
                    "Transaction deleted", Toast.LENGTH_SHORT).show());
        });
    }

    private void renameWallet() {
        String newName = etRenameWallet.getText().toString().trim();
        if (TextUtils.isEmpty(newName)) {
            Toast.makeText(this, "Enter new wallet name", Toast.LENGTH_SHORT).show();
            return;
        }
        wallet.setName(newName);
        tvWalletTitle.setText(newName);

        AppDatabase.databaseWriteExecutor.execute(() -> walletDao.update(wallet));
        Toast.makeText(this, "Wallet renamed", Toast.LENGTH_SHORT).show();
    }

    private void deleteWallet() {
        AppDatabase.databaseWriteExecutor.execute(() -> {
            paymentDao.deletePaymentsForWallet(wallet.getId());
            walletDao.delete(wallet);
            runOnUiThread(this::finish);
        });
    }
}
