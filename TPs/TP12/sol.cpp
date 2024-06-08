#include <iostream>
#include <vector>
#include <climits> 

using namespace std;

const int INF = INT_MAX;

vector<vector<int>> floydWarshall(const vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist = graph;

    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    return dist;
}

int destroy_towers_cost(const vector<vector<int>>& power_matrix, const vector<int>& tower_order, int n) {
    int total_cost = 0;
    vector<vector<int>> floyd_graph = floydWarshall(power_matrix, n);
    vector<bool> destroyed(n, false);            
                
    for (int tower: tower_order) {
        int current_cost = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (i!=j) {
                    if (!destroyed[i] && !destroyed[j]) {
                        current_cost += floyd_graph[i][j];
                    }
                }
            }
        }
        destroyed[tower] = true;
        total_cost += current_cost;
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
