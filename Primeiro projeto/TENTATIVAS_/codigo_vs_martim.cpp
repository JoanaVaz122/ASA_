#include <vector>
#include <iostream>

using namespace std;

int maxCutValue(int X, int Y, vector<vector<int>>& parts) {
    int n = parts.size();

    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            dp[i][j] = dp[i ][j- 1];

            for (int k = 0; k < n; k++) {
                int ai = parts[k][0];
                int bi = parts[k][1];
                int pi = parts[k][2];

                if ((i >= ai && j >= bi) || (i >= bi && j >= ai)) {
                    if(X % bi == 0 && Y % ai == 0){
                        dp[i][j] = max(dp[i][j], max(dp[i][j - ai] + pi, dp[i - bi][j] + pi));
                    }else if(X % ai == 0 && Y % bi == 0){
                        dp[i][j] = max(dp[i][j], max(dp[i][j - bi] + pi, dp[i - ai][j] + pi));
                    }
                }
            }
        }
    }

    return dp[X][Y];
}

int main() {
    int _X, _Y, _n;
    std::cin >> _X >> _Y >> _n;

    if (_X == 0 || _Y == 0 || _n == 0) {
        cout << "0" << endl;
        return 0;
    }

    vector<vector<int>> parts_type(_n, vector<int>(3));

    for (int i = 0; i < _n; i++) {
        std::cin >> parts_type[i][0] >> parts_type[i][1] >> parts_type[i][2];
    }

    int result = maxCutValue(_X, _Y, parts_type);
    cout << result << endl;

    return 0;
}