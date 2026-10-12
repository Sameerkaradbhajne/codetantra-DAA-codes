/**
 * @file 1.1.11. Knapsack Problem.c
 * @brief Implementation of the 0/1 Knapsack Problem using Dynamic Programming.
 * @strategy Dynamic Programming (1D Space-Optimized Bottom-Up Tabulation)
 * @complexity
 *   - Time Complexity:
 *     - Best Case: O(N * W)
 *     - Average Case: O(N * W)
 *     - Worst Case: O(N * W)
 *   - Space Complexity: O(W) [Space-optimized DP array]
 */

#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *values = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &values[i]) != 1) return 0;
    }

    int *weights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &weights[i]) != 1) return 0;
    }

    int w;
    if (scanf("%d", &w) != 1) return 0;

    // dp[j] stores the maximum value that can be attained with a capacity of j
    int *dp = (int *)calloc(w + 1, sizeof(int));

    // Build the DP table bottom-up
    for (int i = 0; i < n; i++) {
        // Traverse backwards to prevent using the same item multiple times
        for (int j = w; j >= weights[i]; j--) {
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
        }
    }

    // The maximum value for capacity W will be at dp[W]
    printf("%d\n", dp[w]);

    // Free allocated memory
    free(values);
    free(weights);
    free(dp);

    return 0;
}
