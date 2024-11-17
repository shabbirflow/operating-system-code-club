#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxPoints(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    if (grid[0][0] == -1 || grid[n - 1][m - 1] == -1) {
        return 0;
    }
    vector<vector<int>> dp1(n, vector<int>(m, -1));
    dp1[0][0] = grid[0][0];  // Starting point
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == -1) {
                continue;  // Skip blocked cells
            }
            if (i > 0 && dp1[i - 1][j] != -1) {
                dp1[i][j] = max(dp1[i][j], dp1[i - 1][j] + grid[i][j]);
            }
            if (j > 0 && dp1[i][j - 1] != -1) {
                dp1[i][j] = max(dp1[i][j], dp1[i][j - 1] + grid[i][j]);
            }
        }
    }
    if (dp1[n - 1][m - 1] == -1) { 
        return 0;
    }

    int i = n - 1, j = m - 1;
    while (i > 0 || j > 0) {
        int val = grid[i][j];
        grid[i][j] = 0;  // Marking the cell as 0
        if ((i > 0) && (dp1[i][j] == (dp1[i - 1][j] + val))) {
            i--;  // Move up
        } else {
            j--;  // Move left
        }
    }
    grid[0][0] = 0;  // Mark the starting cell as well
    vector<vector<int>> dp2(n, vector<int>(m, -1));
    dp2[n - 1][m - 1] = grid[n - 1][m - 1];  // Starting point for return

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (grid[i][j] == -1) {
                continue;  // Skip blocked cells
            }
            if (i < n - 1 && dp2[i + 1][j] != -1) {
                dp2[i][j] = max(dp2[i][j], dp2[i + 1][j] + grid[i][j]);
            }
            if (j < m - 1 && dp2[i][j + 1] != -1) {
                dp2[i][j] = max(dp2[i][j], dp2[i][j + 1] + grid[i][j]);
            }
        }
    }
    int max_points = dp1[n - 1][m - 1] + (dp2[0][0] == -1 ? 0 : dp2[0][0]);
    return max_points;
}

// Example Usage
int main() {
    vector<vector<int>> grid = {
        {0, 2, 3},
        {-1, 1, 1},
        {6, 1, 2}
    };
    cout << maxPoints(grid) << endl;  // Output should be the maximum points collected
    return 0;
}
