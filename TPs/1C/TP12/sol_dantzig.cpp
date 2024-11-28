#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int INF = numeric_limits<int>::max();

long long dantzig(vector<vector<int>>& graph, int n) {
    long long total_cost = 0;

    for (int k=0; k<n-1; k++) {
        for (int i=0; i<=k; i++) {
            int min_1 = INF;
            int min_2 = INF;
            for (int j=0; j<=k; j++) {
                min_1 = min(min_1, graph[i][j] + graph[j][k+1]);
                min_2 = min(min_2, graph[k+1][j] + graph[j][i]);
            }
            graph[i][k+1] = min_1;
            graph[k+1][i] = min_2;
            total_cost += graph[i][k+1] + graph[k+1][i];
        }
        for (int i=0; i<=k; i++) {
            for (int j=0; j<=k; j++) {
                graph[i][j] = min(graph[i][j], graph[i][k+1] + graph[k+1][j]);
                if (i!=j) total_cost += graph[i][j]; 
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
    
        vector<vector<int>> modified_power_matrix(n, vector<int>(n));

        // We reverse the order of tower_order to prevent destroyed towers to infer in distances in further calculations.
        // Then modify the matrix order to tw_order[n-1]->0, tw_order[n-2]->1, ... ,tw_order[0]->n-1 to just do trivial dantzig. 
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                modified_power_matrix[i][j] = power_matrix[tower_order[n-1-i]][tower_order[n-1-j]];
            }
        }
        // Dantzig invariant ensures that in each iteration we add a node and extend all distances. Since we have reversed order
        // we'll calculate dists from "last tower to destroy" to its self = 0, then
        // min distances from "last tower to destroy" to "second to last tower to destroy" 
        // (which represents calculating dist to remaining towers) and so on.

        long long result = dantzig(modified_power_matrix, n);

        cout << result << endl;
    }
    return 0;
}