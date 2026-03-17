import java.util.Scanner;

public class dynamic_programming_2 {
    // top-down memoized dynamic programming for minimal cut cost
    public static int minimalCostTopDown(int[] positions) {
        int n = positions.length;
        int[][] memo = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                memo[i][j] = -1;
            }
        }
        return findbestsplit(0, n - 1, positions, memo);
    }

    private static int findbestsplit(int left, int right, int[] positions, int[][] memo) {
        if (right - left <= 1) {
            return 0;
        }
        if (memo[left][right] != -1) {
            return memo[left][right];
        }
        int best = Integer.MAX_VALUE;
        int cutCost = positions[right] - positions[left];
        for (int mid = left + 1; mid < right; mid++) {
            //cut in the mid seems reasonable
            int cost = cutCost + findbestsplit(left, mid, positions, memo) + findbestsplit(mid, right, positions, memo);
            if (cost < best) {
                best = cost;
            }
        }
        memo[left][right] = best;
        return best;
    }

    // bottom-up tabulation dynamic programming for minimal cut cost
    public static int minimalCostBottomUp(int[] positions) {
        int n = positions.length;
        int[][] dp = new int[n][n];
        for (int length = 2; length < n; length++) {
            for (int left = 0; left + length < n; left++) {
                int right = left + length;
                dp[left][right] = Integer.MAX_VALUE;
                int cutCost = positions[right] - positions[left];
                for (int mid = left + 1; mid < right; mid++) {
                    int cost = cutCost + dp[left][mid] + dp[mid][right];
                    if (cost < dp[left][right]) {
                        dp[left][right] = cost;
                    }
                }
                if (dp[left][right] == Integer.MAX_VALUE) {
                    dp[left][right] = 0;
                }
            }
        }
        return dp[0][n - 1];
    }

    // main handles input and prints minimal cost for each case
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (!scanner.hasNextInt()) {
            return;
        }
        int tests = scanner.nextInt();
        for (int t = 0; t < tests; t++) {
            if (!scanner.hasNextInt()) {
                break;
            }
            int length = scanner.nextInt();
            if (!scanner.hasNextInt()) {
                break;
            }
            int cuts = scanner.nextInt();
            int[] positions = new int[cuts + 2];
            positions[0] = 0;
            positions[cuts + 1] = length;
            for (int i = 1; i <= cuts; i++) {
                positions[i] = scanner.nextInt();
            }
            int topDown = minimalCostTopDown(positions);
            int bottomUp = minimalCostBottomUp(positions);
            int result = topDown;
            if (bottomUp < result) {
                result = bottomUp;
            }
            System.out.println(result);
        }
        scanner.close();
    }
}
