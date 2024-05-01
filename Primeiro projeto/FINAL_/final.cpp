#include <vector>
#include <cstdio>

using namespace std;

int maxCutValue(int X, int Y, vector<vector<int>>& dp) {
    //loops to iterate through all possible subproblems
    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            // Initialize maximum values for horizontal and vertical cuts
            int max_horiz = dp[i][j];
            int max_verti = dp[i][j];

            // Check all possible horizontal cuts
            for (int k = 1; k < j; k++) {
                max_horiz = max(max_horiz, dp[i][k] + dp[i][j - k]);
            }

            // Check all possible vertical cuts
            for (int l = 1; l < i; l++) {
                max_verti = max(max_verti, dp[l][j] + dp[i - l][j]);
            }

            // Update the maximum cut value for the current subproblem
            dp[i][j] = max(max(dp[i][j], max_horiz), max_verti);
        }
    }
    return dp[X][Y];
}

int main() {
    int _X, _Y, _n;
    scanf("%d %d %d", &_X, &_Y, &_n);

    // Check for invalid input dimensions or no cuts
    if (_X == 0 || _Y == 0 || _n == 0) {
        printf("0\n");
        return 0;
    }

    vector<vector<int>> dp(_X + 1, vector<int>(_Y + 1, 0));

    // Loop to read input values for each cut
    for (int i = 0; i < _n; i++) {
        int posX, posY, value;
        scanf("%d %d %d", &posX, &posY, &value);

        if (posX <= _X && posY <= _Y) {
            dp[posX][posY] = value;
        }
        if (posY <= _X && posX <= _Y) {
            dp[posY][posX] = value;
        }
    }
    int result = maxCutValue(_X, _Y, dp);
    printf("%d\n", result);

    return 0;
}
