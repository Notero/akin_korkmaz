
 /*
 * Programming Assignment 4 – Treasure Hunt
 * Author: Akin Korkmaz
 * Course: Computer Science 2
 * Semester: Fall 2025
 * UCF ID: 5684848
 */

import static java.lang.Math.min;

public class dynamic_programming {

    public static final int maxInt = 999999999;

    public int findMinRiskRecursive(int[][] grid, int row, int col) {
        //Null & Out Of Bounds
        if(grid == null || grid.length == 0 || grid[0].length == 0) return 0;
        if(row >= grid.length || col >= grid[0].length) return maxInt;
        if(row == grid.length - 1 && col == grid[0].length - 1) return grid[row][col];
        //Recurse to right and left
        int down = findMinRiskRecursive(grid, row + 1, col);
        int up = findMinRiskRecursive(grid, row, col + 1);
        //adds up from end to start
        return grid[row][col] + min(down, up);
    }

    public int findMinRiskMemoization(int[][] grid, int row, int col, int[][] memo) {
        //Null & Out Of Bounds
        if(grid == null || grid.length == 0 || grid[0].length == 0) return 0;

        if(row >= grid.length || col >= grid[0].length) return maxInt;

        if(row == grid.length - 1 && col == grid[0].length - 1) return grid[row][col];

        if(memo[row][col] != -1) return memo[row][col];

        int down = findMinRiskMemoization(grid, row + 1, col, memo);
        int right = findMinRiskMemoization(grid, row, col + 1, memo);

        memo[row][col] = grid[row][col] + min(down, right);

        return memo[row][col];

    }
    public int findMinRiskTabulation(int[][] grid) {
        if(grid == null || grid.length == 0 || grid[0].length == 0) return 0;

        int row = grid.length;
        int col = grid[0].length;

        int[][] dp = new int[row][col];

        dp[0][0] = grid[0][0];
        //r = 1 cus 0 0 already done same for c
        for(int r = 1; r < row; r++) {
            dp[r][0] = dp[r-1][0] + grid[r][0];
        }

        for(int c = 1; c < col; c++ ) {
            dp[0][c] = dp[0][c-1] + grid[0][c];
        }

        for(int r = 1; r < row; r++) {
            for(int c = 1; c < col; c++) {
                dp[r][c] = grid[r][c] + min(dp[r-1][c], dp[r][c-1]);
            }
        }
        return dp[row-1][col-1];
    }



}
