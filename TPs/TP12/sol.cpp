#include <iostream>
#include <vector>
using namespace std;

// We want to ensure our destroyed towers dont interfere on calculating remaining towers distances,
// thats bc we need to iterate in reverse order.
// Then we need to sum only destroyed towers distances to ensure that the paths already calculated by floyd,
// dont include any towers that will be destroyed on future iterations.

// Implement Floyd where k runs in reverse order and sum destroyed towers costs.

// TODO: try implementing Dantzig to get better time

long long inverse_floyd_warshall(vector<vector<int>>& graph, vector<int> tower_order, int n) {
    long long total_cost = 0;
    vector<bool> destroyed(n, false);

    for (int k = n - 1; k >= 0; k--) { // destroy towers in reverse order
        int tower = tower_order[k];
        destroyed[tower] = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i!=j) graph[i][j] = min(graph[i][j], graph[i][tower] + graph[tower][j]); // update matrix
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (i != j && destroyed[i] && destroyed[j]) {
                    total_cost += graph[i][j] + graph[j][i];
                }
            }
        }
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

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> power_matrix[i][j]; // all positives values, ensures no loops
            }
        }

        vector<int> tower_order(n);
        for (int i = 0; i < n; i++) {
            cin >> tower_order[i];
        }

        long long result = inverse_floyd_warshall(power_matrix, tower_order, n);

        cout << result << endl;
    }
    return 0;
}