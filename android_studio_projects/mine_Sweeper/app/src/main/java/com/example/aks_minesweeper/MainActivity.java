package com.example.aks_minesweeper;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {
    GameLogic gameLogic;
    private int rows;
    private int cols;
    private int coveredCellColor;
    private int uncoveredCellColor;
    private int flagColor;
    private int mineColor;
    private AppCompatButton[] gameBoard;
    private boolean gameOver = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });


        //get settings
        SharedPreferences p = getSharedPreferences("settings", MODE_PRIVATE);
        rows = p.getInt("rows", 5);
        cols = p.getInt("cols", 5);
        double mineper = p.getInt("mines", 10) / 100.0;
        coveredCellColor = Color.parseColor(p.getString("opt1", "#FF3B30"));
        uncoveredCellColor = Color.parseColor(p.getString("opt2", "#00BCD4"));
        flagColor = Color.parseColor(p.getString("opt3", "#A0522D"));
        mineColor = Color.parseColor(p.getString("opt4", "#708090"));

        //Game Logic
        gameLogic = new GameLogic(rows, cols, (int) (rows * cols * mineper));

        //Init Board
        androidx.gridlayout.widget.GridLayout grid = findViewById(R.id.board);
        grid.setRowCount(rows);
        grid.setColumnCount(cols);
        grid.removeAllViews();

        gameBoard = new AppCompatButton[rows * cols];

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                final int row = r;
                final int col = c;

                AppCompatButton cell = new AppCompatButton(this);
                cell.setBackgroundColor(coveredCellColor);

                cell.setOnClickListener(view -> {
                    if (gameOver) return;
                    int result = gameLogic.reveal(row, col);
                    if (result == -1) {
                        // Game Over
                        gameOver = true;
                        gameLogic.revealAllMines();
                        Toast.makeText(this, "Game Over!", Toast.LENGTH_SHORT).show();

                            AppCompatButton a = findViewById(R.id.Restart);
                            a.setVisibility(View.VISIBLE);

                            a.setOnClickListener(v -> {
                                Intent i = new Intent(MainActivity.this, MainActivity.class);
                                startActivity(i);
                                finish();
                            });
                    }
                    updateBoard();
                    if (!gameOver && gameLogic.isWin()) {
                        gameOver = true;
                        Toast.makeText(this, "You Win!", Toast.LENGTH_SHORT).show();
                        AppCompatButton a = findViewById(R.id.Restart);
                        a.setVisibility(View.VISIBLE);

                        a.setOnClickListener(v -> {
                            Intent i = new Intent(MainActivity.this, MainActivity.class);
                            startActivity(i);
                            finish();
                        });
                    }
                });

                cell.setOnLongClickListener(view -> {
                    if (gameOver) return true;
                    gameLogic.toggleFlag(row, col);
                    updateBoard();
                    return true;
                });

                androidx.gridlayout.widget.GridLayout.LayoutParams lp =
                        new androidx.gridlayout.widget.GridLayout.LayoutParams(
                                androidx.gridlayout.widget.GridLayout.spec(r, 1f),
                                androidx.gridlayout.widget.GridLayout.spec(c, 1f)
                        );
                lp.width = 0;
                lp.height = 0;

                lp.setMargins(1, 1, 1, 1); // Left, Top, Right, Bottom margins in pixels

                grid.addView(cell, lp);

                int idx = r * cols + c;
                gameBoard[idx] = cell;
            }
        }
    }

    private void updateBoard() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int idx = r * cols + c;
                AppCompatButton cell = gameBoard[idx];

                if (gameLogic.isRevealed(r, c)) {
                    cell.setBackgroundColor(uncoveredCellColor);
                    if (gameLogic.isMine(r, c)) {
                        cell.setText("M");
                        cell.setTextColor(mineColor);
                    } else {
                        int adjMines = gameLogic.getAdj(r, c);
                        if (adjMines > 0) {
                            cell.setText(String.valueOf(adjMines));
                        } else {
                            cell.setText("");
                        }
                    }
                } else if (gameLogic.isFlagged(r, c)) {
                    cell.setBackgroundColor(flagColor);
                    cell.setText("F");
                } else {
                    cell.setBackgroundColor(coveredCellColor);
                    cell.setText("");
                }
            }
        }
    }
}
