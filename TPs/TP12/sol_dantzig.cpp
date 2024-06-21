#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// notes: dantzig logic impl, but wrong problem impl

int INF = numeric_limits<int>::max();

long long inverse_dantzig(vector<vector<int>>& graph, vector<int> tower_order, int n) {
    long long total_cost = 0;
    vector<bool> destroyed(n, true);

    for (int l=0; l<n-1; l++) {
        int k = tower_order[l];
        for (int i=0; i<k; i++) {
            if (!destroyed[i]) continue;
            int min_1 = INF;
            int min_2 = INF;
            for (int j=0; j<k; j++) {
                if (!destroyed[j]) continue;
                int min_1_temp = graph[i][j] + graph[j][k+1];
                int min_2_temp = graph[k+1][j] + graph[j][i];
                if (min_1_temp < min_1) min_1 = min_1_temp;
                if (min_2_temp < min_2) min_2 = min_2_temp;
            }
            graph[i][k+1] = min_1;
            graph[k+1][i] = min_2;
        }
        for (int i=0; i<k; i++) {
            if (!destroyed[i]) continue;
            for (int j=0; j<k; j++) {
                if (!destroyed[j]) continue;
                graph[i][j] = min(graph[i][j], graph[i][k+1] + graph[k+1][j]);
            }
        }
        // sum matrix values
        for (int i=0; i<k; i++) {
            if (!destroyed[i]) continue;
            for (int j=0; j<k; j++) {
                if (!destroyed[j]) continue;
                total_cost += graph[i][j]; 
            }
        }
        destroyed[k] = false;
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

        long long result = inverse_dantzig(power_matrix, tower_order, n);

        cout << result << endl;
    }
    return 0;
}