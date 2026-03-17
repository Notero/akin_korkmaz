package com.example.aks_minesweeper;

public class GameLogic {

    private int rows;
    private int cols;
    private int numMines;
    private boolean[][] mines;
    private boolean[][] revealed;
    private boolean[][] flagged;
    private int[][] adjacentMines;

    public GameLogic(int rows, int cols, int numMines) {
        this.rows = rows;
        this.cols = cols;
        this.numMines = numMines;
        mines = new boolean[rows][cols];
        revealed = new boolean[rows][cols];
        adjacentMines = new int[rows][cols];
        flagged = new boolean[rows][cols];

        placeMines();
        computeAdj();
    }

    public int getRows() { return rows; }
    public int getCols() { return cols; }
    public boolean isMine(int r, int c) { return mines[r][c]; }
    public boolean isRevealed(int r, int c) { return revealed[r][c]; }
    public boolean isFlagged(int r, int c) { return flagged[r][c]; }
    public int getAdj(int r, int c) { return adjacentMines[r][c]; }

    public void placeMines() {

        int minesPlaced = 0;
        while (minesPlaced < numMines) {
            int row = (int) (Math.random() * rows);
            int col = (int) (Math.random() * cols);

            if (!mines[row][col]) {
                mines[row][col] = true;
                minesPlaced++;
            }
        }
    }

    private void computeAdj() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (mines[r][c]) { adjacentMines[r][c] = -1; continue; }
                int cnt = 0;
                for (int dr = -1; dr <= 1; dr++)
                    for (int dc = -1; dc <= 1; dc++) {
                        if (dr == 0 && dc == 0) continue;
                        int nr = r + dr, nc = c + dc;
                        if (inBounds(nr, nc) && mines[nr][nc]) cnt++;
                    }
                adjacentMines[r][c] = cnt;
            }
        }
    }

    private boolean inBounds(int r, int c) {
        return r >= 0 && r < rows && c >= 0 && c < cols;
    }


    public int reveal(int r, int c) {
        if (!inBounds(r, c)) return -2;
        if (flagged[r][c])   return -3;          // block flagged cells
        if (revealed[r][c])  return 0;           // no-op

        if (mines[r][c]) {                        // only true on user tap
            revealed[r][c] = true;
            return -1;                            // hit mine
        }

        revealed[r][c] = true;                    // safe cell

        if (adjacentMines[r][c] == 0) {
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr, nc = c + dc;
                    if (inBounds(nr, nc) && !flagged[nr][nc] && !revealed[nr][nc]) reveal(nr, nc);
                }
            }
            return 0;
        } else {
            return adjacentMines[r][c];           // numbered boundary
        }
    }

    public void toggleFlag(int r, int c) {
        if (!revealed[r][c]) flagged[r][c] = !flagged[r][c];
    }

    public void revealAllMines() {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (mines[r][c]) revealed[r][c] = true;
    }

    public boolean isWin() {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (!mines[r][c] && !revealed[r][c]) return false;
        return true;
    }

}
