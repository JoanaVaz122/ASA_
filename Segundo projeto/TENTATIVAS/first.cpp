#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Função para realizar o BFS e calcular o número máximo de saltos
int bfs(int start, const vector<vector<int>>& graph) {
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);
    queue<pair<int, int>> q;  // Pares (vertice, saltos)
    
    q.push({start, 0});  // Inicializa a fila com o vértice inicial e zero saltos
    visited[start] = true;

    int maxJumps = 0;

    while (!q.empty()) {
        int currentVertex = q.front().first;
        int jumps = q.front().second;
        q.pop();

        maxJumps = max(maxJumps, jumps);

        for (int neighbor : graph[currentVertex]) {
            if (!visited[neighbor]) {
                q.push({neighbor, jumps + 1});
                visited[neighbor] = true;
            }
        }
    }

    return maxJumps;
}

int main() {
    int n, m;
    cin >> n >> m;

    // Inicializa o grafo como uma lista de adjacências
    vector<vector<int>> graph(n + 1);

    // Preenche o grafo com as relações entre os indivíduos
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
    }

    // Escolhe um ponto de partida arbitrário (pode ser otimizado)
    int startVertex = 1;

    // Chama a função BFS e imprime o resultado
    int result = bfs(startVertex, graph);
    cout << result << endl;

    return 0;
}
