#include <iostream>
#include <vector>
using namespace std;

void graph_coloring_dfs(const vector<vector<int>>& graph, long long& elems_in_set_A, vector<bool>& visited, vector<bool>& colors, int u) {

    visited[u] = true;

    for (int v : graph[u]) {
        if (!visited[v]) {
            if (colors[u] == 0) {colors[v] = 1;} else {colors[v] = 0; elems_in_set_A += 1;}
            graph_coloring_dfs(graph, elems_in_set_A, visited, colors, v);
        }
    }
}

int main() {
    int n; cin >> n; 

    vector<vector<int>> graph(n);
    vector<bool> visited(n, false);
    vector<bool> colors(n, false);

    for (int i=0; i<n-1; i++) { // we read n-1 edges
        int u, v; cin >> u >> v;
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }

    // get colored nodes
    colors[0] = 0; // root node has color 0
    long long elems_in_set_A = 1;
    graph_coloring_dfs(graph, elems_in_set_A, visited, colors, 0);

    // count edges
    long long res = (elems_in_set_A * (n - elems_in_set_A)) - (n-1);

    cout << res << endl;

    return 0;
}