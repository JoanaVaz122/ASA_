#include <vector>
#include <cstdio>
#include <chrono>

using namespace std;
using namespace chrono;

int maxCutValue(int X, int Y, vector<vector<int>>& dp) {

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {

            int max_horiz = dp[i][j];
            int max_verti = dp[i][j];

            for (int k = 1; k < j; k++ ){
                max_horiz = max(max_horiz, dp[i][k] + dp[i][j - k]);
            }

            for (int l = 1; l < i; l++ ){
                max_verti = max(max_verti, dp[l][j] + dp[i - l][j]);
            }

            dp[i][j] = max(max(dp[i][j], max_horiz), max_verti);
        }
    }

    return dp[X][Y];
}

int main() {
    int _X, _Y, _n;
    scanf("%d %d %d", &_X, &_Y, &_n);

    if (_X == 0 || _Y == 0 || _n == 0) {
        printf("0\n");
        return 0;
    }

    vector<vector<int>> dp(_X + 1, vector<int>(_Y + 1, 0));

    auto start = high_resolution_clock::now(); // Record the start time

    for (int i = 0; i < _n; i++) {
        int posX, posY, value;
        scanf("%d %d %d", &posX, &posY, &value);

        if(posX <= _X && posY <= _Y){
            dp[posX][posY] = value;
        }
        if(posY <= _X && posX <= _Y){
            dp[posY][posX] = value;
        }
    }

    int result = maxCutValue(_X, _Y, dp);

    auto stop = high_resolution_clock::now(); // Record the stop time

    auto duration = duration_cast<milliseconds>(stop - start); // Calculate the duration

    printf("Result: %d\n", result);
    printf("Time taken: %lld milliseconds\n", duration.count());

    return 0;
}