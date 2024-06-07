#include <iostream>
#include <vector>
#include <queue>
#include <climits> 
using namespace std;

// We got an adj matrix, we can use Floyd-Warshall easily.
// Floyd-Warshall O(n^3) for each tower while deleting them in each iteration.
// Total complexity: O(n*n^2 + (n-1)(n-1)^2 + ... + 1*1^2) = O(n^3 + (n-1)^3 + ... + 1^3)
// Our complexity aproaches more to O(n^4) than O(n^3) 

// NOTES: First iteration returns good, the problem is how i handle the graph after destroying towers. I should get the original graph each time.

const int INF = INT_MAX;

void floydWarshall(vector<vector<int>>& graph, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][k] < INF && graph[k][j] < INF) {
                    if (graph[i][j] > graph[i][k] + graph[k][j]) {
                        graph[i][j] = graph[i][k] + graph[k][j];
                    }
                }
            }
        }
    }
}

int graph_sum(vector<vector<int>> graph, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            if (i!=j && graph[i][j] < INF) result += graph[i][j];
        }
    }
    return result;
}

int destroy_towers_cost(vector<vector<int>>& graph, vector<int> tower_order, int n) {
    int total_cost = 0;
    floydWarshall(graph, n);

    for (int k = 0; k < n; k++) {
        int tower = tower_order[k];
        int current_cost = 0;

        current_cost += graph_sum(graph, n);

        total_cost += current_cost;

        // destroy tower by setting its row and column to INF
        for (int i = 0; i < n; i++) {
            graph[tower][i] = INF;
            graph[i][tower] = INF;
        }

        // recalculate shortest paths ignoring the destroyed tower
        floydWarshall(graph, n);
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
