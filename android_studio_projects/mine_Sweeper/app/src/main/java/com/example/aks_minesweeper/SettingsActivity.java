package com.example.aks_minesweeper;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.SeekBar;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.chip.Chip;
import com.google.android.material.chip.ChipGroup;

public class SettingsActivity extends AppCompatActivity {

    private EditText rowCount, colCount;
    private SeekBar seekRows, seekCols;
    private RadioGroup minePercentageGroup;
    private ChipGroup colorGroup1, colorGroup2, colorGroup3, colorGroup4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        seekRows = findViewById(R.id.seekrows);
        rowCount = findViewById(R.id.rowCount);
        seekCols = findViewById(R.id.seekcols);
        colCount = findViewById(R.id.colCount);
        minePercentageGroup = findViewById(R.id.minePercentage);
        colorGroup1 = findViewById(R.id.colorGroup);
        colorGroup2 = findViewById(R.id.colorGroup2);
        colorGroup3 = findViewById(R.id.colorGroup3);
        colorGroup4 = findViewById(R.id.colorGroup4);
        Button saveButton = findViewById(R.id.save_exit);

        setupSeekBarListeners();
        saveButton.setOnClickListener(v -> saveSettingsAndExit());

        loadAndApplySettings();
    }

    private void setupSeekBarListeners() {
        seekRows.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                rowCount.setText(String.valueOf(progress));
            }
            @Override public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        seekCols.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                colCount.setText(String.valueOf(progress));
            }
            @Override public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override public void onStopTrackingTouch(SeekBar seekBar) {}
        });
    }

    private void loadAndApplySettings() {
        SharedPreferences p = getSharedPreferences("settings", MODE_PRIVATE);
        int savedRows = p.getInt("rows", 5);
        int savedCols = p.getInt("cols", 5);
        int savedMines = p.getInt("mines", 10);
        String savedOpt1 = p.getString("opt1", "#FF3B30");
        String savedOpt2 = p.getString("opt2", "#00BCD4");
        String savedOpt3 = p.getString("opt3", "#A0522D");
        String savedOpt4 = p.getString("opt4", "#708090");

        // Apply grid settings
        rowCount.setText(String.valueOf(savedRows));
        seekRows.setProgress(savedRows);
        colCount.setText(String.valueOf(savedCols));
        seekCols.setProgress(savedCols);

        // Apply mine percentage
        if (savedMines == 15) {
            minePercentageGroup.check(R.id.p15);
        } else if (savedMines == 20) {
            minePercentageGroup.check(R.id.p20);
        } else {
            minePercentageGroup.check(R.id.p10);
        }

        // Apply color selections
        checkChipByTag(colorGroup1, savedOpt1);
        checkChipByTag(colorGroup2, savedOpt2);
        checkChipByTag(colorGroup3, savedOpt3);
        checkChipByTag(colorGroup4, savedOpt4);
    }

    private void saveSettingsAndExit() {
        int rows = safeInt(rowCount.getText().toString(), 5);
        int cols = safeInt(colCount.getText().toString(), 5);

        // Get selected mine percentage
        int checkedId = minePercentageGroup.getCheckedRadioButtonId();
        RadioButton checkedRadioButton = findViewById(checkedId);
        int minePercent = Integer.parseInt(checkedRadioButton.getTag().toString());

        // Get selected colors, falling back to defaults if none are selected
        SharedPreferences prefs = getSharedPreferences("settings", MODE_PRIVATE);
        String opt1 = getCheckedChipValue(colorGroup1, prefs.getString("opt1", "#FF3B30"));
        String opt2 = getCheckedChipValue(colorGroup2, prefs.getString("opt2", "#00BCD4"));
        String opt3 = getCheckedChipValue(colorGroup3, prefs.getString("opt3", "#A0522D"));
        String opt4 = getCheckedChipValue(colorGroup4, prefs.getString("opt4", "#708090"));

        // Persist all settings
        prefs.edit()
                .putInt("rows", rows)
                .putInt("cols", cols)
                .putInt("mines", minePercent)
                .putString("opt1", opt1)
                .putString("opt2", opt2)
                .putString("opt3", opt3)
                .putString("opt4", opt4)
                .apply();

        finish(); // Close the activity
    }


    private int safeInt(String s, int defVal) {
        try {
            return Integer.parseInt(s);
        } catch (NumberFormatException e) {
            return defVal;
        }
    }

    private String getCheckedChipValue(ChipGroup group, String defaultValue) {
        int id = group.getCheckedChipId();
        if (id == View.NO_ID) {
            return defaultValue;
        }
        Chip c = findViewById(id);
        return c.getTag().toString();
    }

    private void checkChipByTag(ChipGroup chipGroup, String tag) {
        if (tag == null) return;
        for (int i = 0; i < chipGroup.getChildCount(); i++) {
            Chip chip = (Chip) chipGroup.getChildAt(i);
            if (tag.equals(chip.getTag())) {
                chip.setChecked(true);
                return;
            }
        }
    }
}
