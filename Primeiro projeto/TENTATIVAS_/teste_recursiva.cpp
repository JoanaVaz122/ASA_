#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int maxCutValueRecursive(int X, int Y, vector<vector<int>>& dp) {
    // Caso base: se já calculou o valor para essa posição, retorne-o
    if (dp[X][Y] != -1) {
        return dp[X][Y];
    }

    // Caso base: se chegou às bordas, retorne 0
    if (X == 0 || Y == 0) {
        return 0;
    }

    int max_cut_value = 0;

    // Loop para explorar todas as possíveis combinações de cortes horizontais
    for (int k = 1; k < Y; k++) {
        max_cut_value = max(max_cut_value, maxCutValueRecursive(X, k, dp) + maxCutValueRecursive(X, Y - k, dp));
    }

    // Loop para explorar todas as possíveis combinações de cortes verticais
    for (int l = 1; l < X; l++) {
        max_cut_value = max(max_cut_value, maxCutValueRecursive(l, Y, dp) + maxCutValueRecursive(X - l, Y, dp));
    }

    // Armazena o resultado na tabela de memoização
    dp[X][Y] = max_cut_value;

    return max_cut_value;
}

int main() {
    int _X, _Y, _n;
    scanf("%d %d %d", &_X, &_Y, &_n);

    // Check for invalid input dimensions or no cuts
    if (_X == 0 || _Y == 0 || _n == 0) {
        printf("0\n");
        return 0;
    }

    // Inicializa a tabela de memoização com -1
    vector<vector<int>> dp(_X + 1, vector<int>(_Y + 1, -1));

    // Loop para ler os valores de entrada para cada corte
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

    int result = maxCutValueRecursive(_X, _Y, dp);
    printf("%d\n", result);

    return 0;
}
