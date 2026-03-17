package com.example.aks_minesweeper;


import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class MainMenuActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_menu);

        Button start = findViewById(R.id.start_button);
        start.setOnClickListener(v -> {
            Intent i = new Intent(MainMenuActivity.this, MainActivity.class);
            startActivity(i);
        });

        Button settings = findViewById(R.id.settings_button);
        settings.setOnClickListener(v -> {
            Intent i = new Intent(MainMenuActivity.this, SettingsActivity.class);
            startActivity(i);
        });


    }
}

