package com.example.pokesearch;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.drawable.Drawable;
import android.media.AudioAttributes;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class Pokemon extends AppCompatActivity {

    ImageView img;
    MediaPlayer mediaPlayer;
    TextView textView; // Declare here

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.pokemon);

        // Find UI elements on the main thread
        img = findViewById(R.id.pokeSprite);
        textView = findViewById(R.id.pokeName);

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.pokemonSprite), (v,
                                                                                     insets) -> {
            Insets systemBars =
                    insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right,
                    systemBars.bottom);
            return insets;
        });

        Thread getter = new Thread(() -> {
            try {
                Context context = getApplicationContext();
                SharedPreferences sp = getSharedPreferences("data", MODE_PRIVATE);
                String imageUrlString = sp.getString("img", "1");

                // Download the image
                URL imageUrl = new URL(imageUrlString);
                InputStream inputStream = (InputStream) imageUrl.getContent();
                Drawable pokemonDrawable = Drawable.createFromStream(inputStream, "pokemon_sprite");

                String criesUrl = sp.getString("cries", "1");
                // Prepare the sound
                mediaPlayer = new MediaPlayer();
                mediaPlayer.setAudioAttributes(
                        new AudioAttributes.Builder()
                                .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
                                .setUsage(AudioAttributes.USAGE_MEDIA)
                                .build()
                );
                mediaPlayer.setDataSource(criesUrl);
                mediaPlayer.prepare(); 


                String name = sp.getString("name", "1");

                //I learned this runOnUiThread from AI I asked If I can return a drawable or String from the run() function in a thread it told me to run this in the thread
                runOnUiThread(() -> {
                    // Set the image and text
                    img.setImageDrawable(pokemonDrawable);
                    textView.setText(name);

                    // Play the sound
                    mediaPlayer.start();
                });

            }catch (Exception e){
                e.printStackTrace();
            }
        });

        // Start the thread
        getter.start();

        Button returnButton = findViewById(R.id.returnmain);
        returnButton.setOnClickListener(v -> {
            finish();
        });

    }

}
