#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// We've got a tree graph with n nodes and n-1 edges.
// To avoid creating empty spaces in graph, the node indexation starts at 0 (each input node should be substracted by 1)
// Idea:
// 1. Color tree nodes in a way that adjacent nodes have diff colors. This is bc if we add backward edges that connects
// same color nodes, we create an odd cycle => that edge makes the graph non-bipartite. 
// To do so, we traverse the graph with DFS while coloring nodes.
// 2. Count edges that keep the graph bipartite. For each node we have n(n-1)/2 - (n-1)  ...

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

int count_non_bipartite_edges(const vector<vector<int>> graph, const int n, vector<bool>& assigned_edges, vector<bool>& colors) {

    int count = 0;

    for (int u=0; u<n; u++) {
        assigned_edges[u] = true;
        
        for (int v=0; v<n; v++) {
            if (v != u && !(find(graph[u].begin(), graph[u].end(), v) == graph[u].end())) { // if v != u and v not a neighbor of u
                if (!assigned_edges[v]) {
                    if (colors[v] != colors[u]) { // we have an even cycle => we still have a bipartite graph
                        count += 1;
                    }
                }
            }
        }
    }
    return count;
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

    // count edges
    int res = count_non_bipartite_edges(graph, n, assigned_edges, colors);

    cout << res << endl;

    return 0;
}