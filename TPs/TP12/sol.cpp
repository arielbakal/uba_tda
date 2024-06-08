#include <iostream>
#include <vector>
#include <climits> 

using namespace std;

// TODO: 
// 1. explain floyd warshall
// 2. explain increasing floyd warshall
// 3. add new notes

const int INF = INT_MAX;

int increasing_floyd_warshall(vector<vector<int>>& graph, vector<int> tower_order, int n) {
    int total_cost = 0;
    vector<bool> destroyed(n, false);

    for (int k=n-1; k>=0; k--) {
        int tower = tower_order[k];
        destroyed[tower] = true;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                if (destroyed[i] && destroyed[j]) total_cost += graph[i][j];
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

        for (int i = 0; i < n; i++) { // build power matrix
            for (int j = 0; j < n; j++) {
                cin >> power_matrix[i][j];
            }
        }

        vector<int> tower_order(n);
        for (int i = 0; i < n; i++) {
            cin >> tower_order[i];
        }

        int result = increasing_floyd_warshall(power_matrix, tower_order, n);

        cout << result << endl;
    }

    return 0;
}
