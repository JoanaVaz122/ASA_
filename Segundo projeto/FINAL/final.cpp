#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int n, m;

void iterativeDFS(vector<vector<int>>& graph, stack<int>& exitOrder, vector<int>& visited) {

    stack<int> dfsStack;

    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            dfsStack.push(i);

            while (!dfsStack.empty()) {
                int current = dfsStack.top();
                dfsStack.pop();

                if (visited[current] == 0) {
                    dfsStack.push(current);

                    visited[current] = 1;

                    for (int neighbor : graph[current]) {
                        if (visited[neighbor] == 0) {
                            dfsStack.push(neighbor);
                        }
                    }
                } else if (visited[current] == 1) {
                    visited[current] = 2;
                    exitOrder.push(current);
                }
            }
        }
    }
}

void iterativeDFS2(vector<vector<int>>& graphT, stack<int>& exitOrder, vector<int>& maxJumps, vector<int>& visited, vector<int>& sccs_ids) {

    while (!exitOrder.empty()) {
        int current = exitOrder.top();
        exitOrder.pop();

        if (visited[current] == 0) {
            stack<int> dfsStack;
            dfsStack.push(current);
            int max_scc = 0;
            stack<int> sccStack;

            while (!dfsStack.empty()) {
                int current = dfsStack.top();
                dfsStack.pop();
                sccStack.push(current);

                for (int neighbor : graphT[current]) {
                    if (visited[neighbor] == 0) {
                        if (sccs_ids[current] == 0) {
                            sccs_ids[current] = current;
                        }

                        sccs_ids[neighbor] = sccs_ids[current];
                        visited[current] = 1;
                        dfsStack.push(neighbor);
                    } else {
                        if (maxJumps[neighbor] >= maxJumps[current]) {
                            if (sccs_ids[current] != sccs_ids[neighbor] || (sccs_ids[current] == 0 && sccs_ids[neighbor] == 0)) {
                                maxJumps[current] = max(maxJumps[current], maxJumps[neighbor] + 1);
                            }
                            max_scc = max(max_scc, maxJumps[current]);
                        }
                    }
                }

                visited[current] = 1;
            }

            while (!sccStack.empty()) {
                visited[sccStack.top()] = 2;
                maxJumps[sccStack.top()] = max_scc;
                sccStack.pop();
            }
        }
    }
}

int main() {
    if (scanf("%d %d", &n, &m) != 2 || n < 1 || m < 0) {
        return 0;
    }

    vector<vector<int>> graph(n + 1);
    vector<vector<int>> graphT(n + 1);
    stack<int> exitOrder;
    vector<int> maxJumps(n + 1, 0);
    vector<int> visited(n + 1, 0);
    vector<int> sccs_ids(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int x, y;
        if (scanf("%d %d", &x, &y) != 2){
            return 0;
        }

        graph[x].push_back(y);
        graphT[y].push_back(x);
    }

    iterativeDFS(graph, exitOrder, visited);

    fill(visited.begin(), visited.end(), 0);

    iterativeDFS2(graphT, exitOrder, maxJumps, visited, sccs_ids);

    int maxJump = *max_element(maxJumps.begin(), maxJumps.end());
    printf("%d\n", maxJump);

    return 0;
}
