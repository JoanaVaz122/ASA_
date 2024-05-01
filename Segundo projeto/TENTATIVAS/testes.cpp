#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    int maxJumps = 0;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            int jumps = dfs(neighbor, graph, visited);
            maxJumps = max(maxJumps, jumps);
        }
    }

    return maxJumps + 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);


    // Verificações adicionadas
    if (n < 2 || m < 0) {
        return 0;  // Retorna código de erro
    }

    vector<vector<int>> graph(n);


    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);

        // Verifica se os inteiros estão separados por exatamente um espaço em branco
        char c;
        scanf("%c", &c);
        if (c != ' ' && c != '\n') {
            return 0;  // Retorna código de erro
        }

        graph[x - 1].push_back(y - 1);  // Ajusta os índices para começarem em 0
    }

    int maxJumps = 0;

    for (int i = 0; i < n; ++i) {
        vector<bool> visited(n, false);
        int jumps = dfs(i, graph, visited);
        maxJumps = max(maxJumps, jumps);
    }

    printf("%d\n", maxJumps - 1);  // Correção para contar em termos de arestas

    return 0;
}
