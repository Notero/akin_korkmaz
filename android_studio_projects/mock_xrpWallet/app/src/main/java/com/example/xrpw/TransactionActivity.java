package com.example.xrpw;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class TransactionActivity extends AppCompatActivity {

    public static final String EXTRA_WALLET_ID = "extra_wallet_id";

    private TextView tvWalletName;
    private EditText etAmount;
    private EditText etDestination;
    private EditText etMemo;
    private Button btnSubmitTransaction;
    private PaymentDao paymentDao;
    private WalletDao walletDao;
    private int walletId = -1;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.transaction);

        tvWalletName = findViewById(R.id.tvWalletName);
        etAmount = findViewById(R.id.etAmount);
        etDestination = findViewById(R.id.etDestination);
        etMemo = findViewById(R.id.etMemo);
        btnSubmitTransaction = findViewById(R.id.btnSubmitTransaction);

        AppDatabase database = AppDatabase.getInstance(getApplicationContext());
        paymentDao = database.paymentDao();
        walletDao = database.walletDao();

        walletId = getIntent().getIntExtra(EXTRA_WALLET_ID, -1);
        loadWalletLabel();

        btnSubmitTransaction.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                submitTransaction();
            }
        });
    }

    private void submitTransaction() {
        String amount = etAmount.getText().toString().trim();
        String dest = etDestination.getText().toString().trim();
        String memo = etMemo.getText().toString().trim();

        if (TextUtils.isEmpty(amount) || TextUtils.isEmpty(dest)) {
            Toast.makeText(this, "Amount and destination required", Toast.LENGTH_SHORT).show();
            return;
        }

        if (walletId == -1) {
            Toast.makeText(this, "Select a wallet before sending", Toast.LENGTH_SHORT).show();
            return;
        }

        String amountText = amount + " XRP";
        String destinationText = "To: " + dest;
        String date = new SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.getDefault()).format(new Date());
        String dateText = TextUtils.isEmpty(memo) ? date : date + " · " + memo;

        Payment payment = new Payment(walletId, amountText, destinationText, dateText);
        AppDatabase.databaseWriteExecutor.execute(() -> {
            paymentDao.insert(payment);
            runOnUiThread(() -> {
                Toast.makeText(this,
                        "Transaction saved locally", Toast.LENGTH_SHORT).show();
                finish();
            });
        });
    }

    private void loadWalletLabel() {
        if (walletId == -1) {
            tvWalletName.setText("No wallet selected");
            return;
        }

        AppDatabase.databaseWriteExecutor.execute(() -> {
            Wallet wallet = walletDao.getWalletById(walletId);
            runOnUiThread(() -> {
                if (wallet != null) {
                    tvWalletName.setText("Using: " + wallet.getName());
                } else {
                    tvWalletName.setText("Wallet unavailable");
                    walletId = -1;
                }
            });
        });
    }
}
