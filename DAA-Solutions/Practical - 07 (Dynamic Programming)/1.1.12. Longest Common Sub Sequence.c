/**
 * @file 1.1.12. Longest Common Sub Sequence.c
 * @brief Find the length of the Longest Common Subsequence (LCS) present in three given strings.
 * @strategy Dynamic Programming (3D Bottom-Up Tabulation)
 * @complexity
 *   - Time Complexity:
 *     - Best Case: O(m * n * o)
 *     - Average Case: O(m * n * o)
 *     - Worst Case: O(m * n * o) [Where m, n, o are the lengths of strings X, Y, Z]
 *   - Space Complexity: O(m * n * o) [For 3D DP table]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Helper function to return the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find the length of the LCS of three strings
int lcsOf3(char *X, char *Y, char *Z, int m, int n, int o) {
    // Strip trailing newlines from lengths if present from fgets
    if (m > 0 && X[m - 1] == '\n') m--;
    if (n > 0 && Y[n - 1] == '\n') n--;
    if (o > 0 && Z[o - 1] == '\n') o--;

    // 3D DP array initialized to zero
    // static is used to handle larger sizes safely outside the stack
    static int dp[MAX_LENGTH + 1][MAX_LENGTH + 1][MAX_LENGTH + 1];

    // Build the DP table bottom-up
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= o; k++) {
                // If characters match in all three strings
                if (X[i - 1] == Y[j - 1] && Y[j - 1] == Z[k - 1]) {
                    dp[i][j][k] = 1 + dp[i - 1][j - 1][k - 1];
                } else {
                    // Take the maximum by dropping one character from each string
                    dp[i][j][k] = max(max(dp[i - 1][j][k], dp[i][j - 1][k]), dp[i][j][k - 1]);
                }
            }
        }
    }

    return dp[m][n][o];
}

int main() {
    char X[MAX_LENGTH + 2];
    char Y[MAX_LENGTH + 2];
    char Z[MAX_LENGTH + 2];

    if (scanf("%s", X) != 1) return 0;
    if (scanf("%s", Y) != 1) return 0;
    if (scanf("%s", Z) != 1) return 0;

    int m = strlen(X);
    int n = strlen(Y);
    int o = strlen(Z);

    printf("%d\n", lcsOf3(X, Y, Z, m, n, o));

    return 0;
}
