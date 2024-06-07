#include <iostream>
#include <vector>
#include <queue>
#include <climits> 

// 1. Dijkstra with queue (since we got nearly n^2 edges) O(n^2).
// 2. Iterate over n towers and run dijkstra for all pairs of towers (note that while iterating we are removing towers from graph).
// 3. Sum all costs.
// Total complexity: O(n*n^2 + (n-1)(n-1)^2 + ... + 1*1^2) = O(n^3 + (n-1)^3 + ... + 1^3)
// Our complexity aproaches more to O(n^4) than O(n^3) 

using namespace std;

int dijkstra(const vector<vector<int>>& graph, int source, int target, int n, const vector<bool>& destroyed) {
    const int INF = INT_MAX;

    vector<int> distances(n, INF);
    queue<int> q;

    distances[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (destroyed[current]) continue; // skip destroyed towers

        for (int neighbor = 0; neighbor < n; neighbor++) {
            int neighbor_dist = graph[current][neighbor];
            if (neighbor_dist != 0 && !destroyed[neighbor]) { // check if edge and the neighbor is not destroyed
                int new_dist = distances[current] + neighbor_dist;
                if (new_dist < distances[neighbor]) {
                    distances[neighbor] = new_dist;
                    q.push(neighbor);
                }
            }
        }
    }

    return distances[target];
}

int dijkstra_all_pairs(vector<vector<int>> graph, int n, const vector<bool>& destroyed) {
    int all_pair_sum = 0;
    for (int i = 0; i < n; i++) {
        if (destroyed[i]) continue; // skip destroyed towers
        for (int j = 0; j < n; j++) {
            if (i != j && !destroyed[j]) {
                int cost = dijkstra(graph, i, j, n, destroyed);
                if (cost != INT_MAX) { // only add if there is a valid path
                    all_pair_sum += cost;
                }
            }
        }
    }
    return all_pair_sum;
}

int destroy_towers_cost(vector<vector<int>> graph, const vector<int>& tower_order, int n) {
    int total_cost = 0;
    vector<bool> destroyed(n, false);
    for (int tower : tower_order) {
        int current_cost = dijkstra_all_pairs(graph, n, destroyed);
        total_cost += current_cost;
        destroyed[tower] = true; 
    }
    return total_cost;
}

int main() {
    int t; 
    cin >> t;

    for (int k = 0; k < t; k++) {
        int n; 
        cin >> n; // number of towers
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

        int result = destroy_towers_cost(power_matrix, tower_order, n);
        cout << result << endl;
    }

    return 0;
}
