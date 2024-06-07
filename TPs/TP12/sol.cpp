#include <iostream>
#include <vector>
#include <queue>
#include <climits> 

using namespace std;

int dijkstra(const vector<vector<int>>& graph, int source, int target, int n) {
    const int INF = INT_MAX;

    vector<int> distances(n, INF);
    queue<int> q;

    distances[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // explore neighbors
        for (int i = 0; i < n; i++) {
            int neighbor_dist = graph[current][i];
            if (neighbor_dist != 0) { 
                int neighbor = i;
                int new_dist = distances[current] + neighbor_dist;

                // update distances
                if (new_dist < distances[neighbor]) {
                    distances[neighbor] = new_dist;
                    q.push(neighbor);
                }
            }
        }
    }

    return distances[target];
}

int main() {
    int t; cin >> t;

    for (int k = 0; k < t; k++) {
        int n; cin >> n; // number of towers
        vector<vector<int>> power_matrix(n, vector<int>(n));

        for (int i = 0; i < n; i++) { // build power matrix
            for (int j = 0; j < n; j++) {
                cin >> power_matrix[i][j];
            }
        }

        vector<int> tower_order(n);
        for (int i = 0; i < n; i++) {
            cin >> tower_order[i];
        }
    }

    return 0;
}
