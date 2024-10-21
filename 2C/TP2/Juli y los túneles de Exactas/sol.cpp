#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs_coloring(vector<vector<int>>& graph, const int n, vector<bool>& visited, vector<int>& distance_from_0, int u) {
    queue<int> q;
    q.push(u);
    visited[u] = true;
    distance_from_0[u] = 0;

    while (!q.empty()) {
        int f = q.front();
        q.pop();

        for (int v: graph[f]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
                distance_from_0[v] = distance_from_0[f] + 1;
            }
        }
    }
}

int main() {

    int n; cin >> n;
    vector<vector<int>> graph(n);
    vector<bool> visited(n, false);
    vector<int> distance_from_0(n, -1);

    for (int i=0; i<n; i++) {
        // build directed graph
        if (i==0) {
            graph[i].push_back(i+1);        
        } else if (i<n-1) {
            graph[i].push_back(i+1);
            graph[i].push_back(i-1);
        } else {
            graph[i].push_back(i-1);
        }

        // add shortcut edges
        int shortcut_to_class; cin >> shortcut_to_class;
        if (i!=shortcut_to_class-1 && i-1!=shortcut_to_class-1 && i+1!=shortcut_to_class-1) {
            graph[i].push_back(shortcut_to_class-1);    
        }
    }
    bfs_coloring(graph, n, visited, distance_from_0, 0);

    for (int i=0; i<n; i++) {
        cout << distance_from_0[i] << " ";
    }

    return 0;
}