/**
 * @file 1.1.13. Travelling Salesman Problem.c
 * @brief Solves the Travelling Salesman Problem (TSP) using Branch and Bound
 *        with a bitmask DP approach for optimal path computation.
 * @strategy Branch and Bound (Bitmask Dynamic Programming)
 * @complexity
 *   - Time Complexity:
 *     - Best Case:  O(2^n * n^2)
 *     - Average Case: O(2^n * n^2)
 *     - Worst Case: O(n!)
 *   - Space Complexity: O(2^n * n) [DP memoization table]
 *
 * @input
 *   Line 1: Integer n — number of cities
 *   Next n lines: n space-separated integers — cost matrix (cost[i][j] = travel
 *   cost from city i to city j; 0 means no direct path / self-loop)
 *
 * @output
 *   Minimum cost of a Hamiltonian cycle (visiting every city exactly once
 *   and returning to the starting city).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN  20
#define INF   INT_MAX / 2

/* dp[mask][i] = minimum cost to reach city i having visited exactly the cities
   whose bits are set in `mask`, starting from city 0. */
int dp[1 << MAXN][MAXN];
int cost[MAXN][MAXN];
int n;

/* Recursive helper with memoisation (top-down DP). */
int tsp(int mask, int pos) {
    /* All cities visited — return cost to go back to origin. */
    if (mask == (1 << n) - 1) {
        return (cost[pos][0] == 0) ? INF : cost[pos][0];
    }

    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        /* Skip already-visited cities and cities with no direct edge. */
        if ((mask & (1 << city)) || cost[pos][city] == 0) continue;

        int next = cost[pos][city] + tsp(mask | (1 << city), city);
        if (next < ans) ans = next;
    }

    dp[mask][pos] = ans;
    return ans;
}

int main() {
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (scanf("%d", &cost[i][j]) != 1) return 0;

    /* Initialise DP table with -1 (unvisited states). */
    memset(dp, -1, sizeof(dp));

    /* Start from city 0, only city 0 is visited initially (bit 0 set). */
    int result = tsp(1, 0);

    if (result >= INF)
        printf("-1\n"); /* No valid tour exists */
    else
        printf("%d\n", result);

    return 0;
}
