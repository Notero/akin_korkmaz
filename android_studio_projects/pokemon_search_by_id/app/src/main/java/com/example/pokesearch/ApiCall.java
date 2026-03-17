package com.example.pokesearch;

import static android.content.Context.MODE_PRIVATE;
import static androidx.core.content.ContextCompat.startActivity;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class ApiCall extends Thread{

    private URL url;
    private Context context;

    public ApiCall(URL url, Context context){
        this.url = url;
        this.context = context;
    }

    public void run() {
        try {
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setConnectTimeout(5000);
            connection.setReadTimeout(5000);
            connection.connect();

            BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));

            StringBuilder sb = new StringBuilder();
            String line;
            while ((line = br.readLine()) != null) {
                sb.append(line);
            }

            String data = sb.toString();
            JSONObject jo = new JSONObject(data);

            String img = jo.getJSONObject("sprites").getString("front_default");
            String cries = jo.getJSONObject("cries").getString("latest");
            if (cries.isEmpty()){
                cries = jo.getJSONObject("cries").getString("legacy");
            }
            String name = jo.getString("name");

            SharedPreferences sp = context.getSharedPreferences("data", MODE_PRIVATE);
            SharedPreferences.Editor editor = sp.edit();
            editor.putString("img", img);
            editor.putString("cries", cries);
            editor.putString("name",name);
            editor.apply();


        } catch (Exception e) {
            e.printStackTrace();
        }
    }



}
