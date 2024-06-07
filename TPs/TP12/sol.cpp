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
            if (neighbor_dist != 0) { // ensure there is an edge
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

    for (int k=0; k<t; k++) {

        int n; cin >> n; // n towers
        vector<vector<int>> power_matrix(n);

        for (int i=0; i<n; i++) { // build power matrix
            vector<int> power_line(n);
            for (int j=0; j<n; j++) {
                cin >> power_line[j];
            }
            power_matrix.push_back(power_line);
        }

        vector<int> tower_order(n);

        for (int i=0; i<n; i++) {
            cin >> tower_order[i];
        }

        cout << dijkstra(power_matrix, 0, 1, n);
    }
    
    return 0;
}
