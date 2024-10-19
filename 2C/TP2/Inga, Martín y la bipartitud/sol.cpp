#include <iostream>
#include <vector>
#include <map>
using namespace std;

// We've got a tree graph with n nodes and n-1 edges.
// To avoid creating empty spaces in graph, the node indexation starts at 0 (each input node should be substracted by 1)

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

int count_non_bipartite_edges(vector<vector<int>> graph) {

    return 0;
}


int main() {
    int n; cin >> n; 

    vector<vector<int>> graph(n);
    vector<bool> visited(n);
    vector<bool> empty_colors(n);

    for (int i=0; i<n-1; i++) { // we read n-1 edges
        int u, v; cin >> u >> v;
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }

    // get colored nodes
    empty_colors[0] = 0; // root node has color 0
    vector<bool> colors = graph_coloring_dfs(graph, visited, empty_colors, 0);

    return 0;
}