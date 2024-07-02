#include <iostream>
#include <string>
#include <limits.h>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

bool bfs(vector<vector<int>>& residual_graph, int s, int t, vector<int>& parent, vector<bool>& visited, int M) {
    fill(visited.begin(), visited.end(), false);
    queue<int> q;
    
    // start from source
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int w = 0; w < M+9; ++w) {
            if (!visited[w] && residual_graph[v][w] > 0) {
                // if we reach sink just return true
                if (w == t) {
                    parent[w] = v;
                    return true;
                }
                // continue exploring
                q.push(w);
                parent[w] = v;
                visited[w] = true;
            }
        }
    }
    // we didn't reach sink
    return false;
}

int edmonds_karp(vector<vector<int>>& graph, int s, int t, int M) {
    int v, w;
    vector<vector<int>> residual_graph = graph;
    vector<int> parent(M+9);
    vector<bool> visited(M+9);
    
    int max_flow = 0;
    
    // augment flow while path source to sink exists
    while (bfs(residual_graph, s, t, parent, visited, M)) {
        // find min residual capacity edges along the path filled by BFS 
        // (find max flow through the path found)
        int path_flow = INT_MAX;
        for (w = t; w != s; w = parent[w]) {
            int v = parent[w];
            path_flow = min(path_flow, residual_graph[v][w]);
        }

        // update residual capacities and reverse edges along the path
        for (w = t; w != s; w = parent[w]) {
            int v = parent[w];
            residual_graph[v][w] -= path_flow;
            residual_graph[w][v] += path_flow;
        }

        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    int T; cin >> T;
    unordered_map<string, int> size_map = {{"XXL", 1}, {"XL", 2}, {"L", 3}, {"M", 4}, {"S", 5}, {"XS", 6}};
    
    for (int t = 0; t < T; t++) {
        int N, M; cin >> N >> M;
        vector<vector<int>> graph(M + 9, vector<int>(M + 9, 0)); // space complexity O(n^2) but M<=30
        // graph: 
        // source->0, 
        // XXL -> 1, XL -> 2, ... , XS -> 6
        // volunteer_1 -> 7, volunteer_2 -> 1+7, ... , volunteer_M -> M+7
        // sink->M+8

        for (int i = 1; i <= 6; ++i) {
            graph[0][i] = N / 6;
        }

        int sink_node = M + 8;
        for (int m = 0; m < M; ++m) {
            string size1, size2; cin >> size1 >> size2;
            int volunteer_index = m + 7;
            
            // direct two sizes that fits volunteer 
            graph[size_map[size1]][volunteer_index] = 1;
            graph[size_map[size2]][volunteer_index] = 1;
            
            // direct volunteer to sink (each volunteer receives 1 t-shirt at most)
            graph[volunteer_index][sink_node] = 1;
        }

        int result = edmonds_karp(graph, 0, sink_node, M);

        if (result == M) cout << "YES"; else cout << "NO";
        cout << endl;
    }
    return 0;
}