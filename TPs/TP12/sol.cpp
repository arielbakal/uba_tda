#include <iostream>
#include <vector>
#include <queue>
#include <climits> 

// 1. Dijkstra with queue (since we got nearly n^2 edges) O(n^2).
// 2. Iterate over n towers and run dijkstra for all pairs of towers (note that while iterating we are removing towers from graph).
// 3. Sum all costs.
// Total complexity: O(n*n^3 + (n-1)(n-1)^3 + ... + 1*1^3) = O(n^4 + (n-1)^4 + ... + 1^4) = O(n^4).
// O(n^4) bounds any other operation complexity that can be in the code.

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

int floyd(vector<vector<int>> graph, int n, vector<bool> destroyed_towers) {
    int all_pair_sum = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i != j) {
                if (!destroyed_towers[i] || !destroyed_towers[j]) {
                    all_pair_sum += dijkstra(graph, i, j, n);
                }
            }
        }
    }
    return all_pair_sum;
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

        int total_cost = 0;
        vector<bool> destroyed(n, false);
        for (int tower: tower_order){
            total_cost += floyd(graph, n, destroyed);
            for (int i = 0; i < n; i++) {
                power_matrix[tower][i] = INF;
                power_matrix[i][tower] = INF;
            }
        }

        cout << total_cost;
    }

    return 0;
}
    