#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<bool> graph_coloring_dfs(const vector<vector<int>> graph, vector<bool>& visited, vector<bool>& colors, int u) {

    visited[u] = true;

    for (int v : graph[u]) {
        if (!visited[v]) {
            if (colors[u] == 0) {colors[v] = 1;} else {colors[v] = 0;}
            graph_coloring_dfs(graph, visited, colors, v);
        }
    }

    return colors;
}

int main() {
    int n; cin >> n; 

    vector<vector<int>> graph(n);
    vector<bool> visited(n);
    vector<bool> assigned_edges(n);
    vector<bool> empty_colors(n);

    for (int i=0; i<n-1; i++) { // we read n-1 edges
        int u, v; cin >> u >> v;
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }

    // get colored nodes
    empty_colors[0] = 0; // root node has color 0
    vector<bool> colors = graph_coloring_dfs(graph, visited, empty_colors, 0);

    int elems_in_set_A = 0;

    for (int v=0; v<n; v++) {
        if (colors[v]) {elems_in_set_A += 1;}
    }

    // count edges
    int res = (elems_in_set_A * (n - elems_in_set_A)) - (n-1);

    cout << res << endl;

    return 0;
}