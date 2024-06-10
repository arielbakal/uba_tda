#include <iostream>
#include <vector>
#include <climits> 
using namespace std;

// We want to ensure our destroyed towers dont infer on calculating remaining towers distances,
// thats bc we need to iterate in reverse order.
// Then we need to sum only destroyed towers distances to ensure that the paths already calculated by floyd,
// dont include any towers that will be destroyed on future iterations.

// Implement Floyd where k runs in reverse order and sum destroyed towers costs.

// NOTES: handle ij where i=j cases

const int INF = INT_MAX;

int inverse_floyd_warshall(vector<vector<int>>& graph, vector<int> tower_order, int n) {
    int total_cost = 0;
    vector<bool> destroyed(n, false);

    for (int k=n-1; k>=0; k--) { // destroy towers in reverse order
        int tower = tower_order[k];
        destroyed[tower] = true;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]); // update matrix
                if (destroyed[i] && destroyed[j]) total_cost += graph[i][j]; // sum destroyed towers distances
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

        int result = inverse_floyd_warshall(power_matrix, tower_order, n);

        cout << result << endl;
    }
    return 0;
}
