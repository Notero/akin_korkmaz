package com.example.pokesearch;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.StrictMode;
import android.provider.MediaStore;
import android.util.Log;
import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.material.textfield.TextInputEditText;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
public class MainActivity extends AppCompatActivity {

    TextInputEditText textInputEditText;
    AppCompatButton sB;
    MediaPlayer mediaPlayer;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v,
                                                                            insets) -> {
            Insets systemBars =
                    insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right,
                    systemBars.bottom);
            return insets;
        });


        sB = findViewById(R.id.searchButton);
        sB.setOnClickListener(v -> {
            textInputEditText = findViewById(R.id.pokemonId);

            String Id = textInputEditText.getText().toString();

            String url = "https://pokeapi.co/api/v2/pokemon/" + Id;



            try {
                URL realURL = new URL(url);
                ApiCall apiCall = new ApiCall(realURL, this);
                apiCall.start();
                apiCall.join();

            } catch (MalformedURLException e) {
                throw new RuntimeException(e);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            SharedPreferences sp = getSharedPreferences("data", MODE_PRIVATE);

            Intent i = new Intent(MainActivity.this, Pokemon.class);
            startActivity(i);



        });

    }

}