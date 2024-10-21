#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


// TODO: start from zero using the logic of the statement. This will not solve the problem

int main() {
    int n, m; 
    cin >> n >> m;
    
    vector<int> weights(m);
    unordered_map<int, int> count_weights;
    unordered_map<int, int> edge_in_agm;
    
    int count_equal_edges = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        weights[i] = w;
        count_weights[w]++;
    }

    vector<int> indices(m);
    for (int i = 0; i < m; i++) {
        indices[i] = i;
    }
    
    sort(indices.begin(), indices.end(), [&](int i, int j) {
        return weights[i] < weights[j];
    });
    
    for (int i = 0; i < m; i++) {
        int sorted_weight = weights[indices[i]];
        
        if (i < n) {
            if (count_weights[sorted_weight] > 1) {
                count_equal_edges++;
                edge_in_agm[sorted_weight] = 3; // AT LEAST ONE
            } else {
                edge_in_agm[sorted_weight] = 2; // ANY
            }
        } else {
            edge_in_agm[sorted_weight] = 1; // NONE
        }
    }

    for (int i = 0; i < m; i++) {
        int w = weights[i];
        if (count_equal_edges == m) {
            cout << "at least one" << endl;
        } else if (count_equal_edges == n - 1) {
            if (count_weights[w] > 1) {
                cout << "any" << endl;
            } else {
                cout << "none" << endl;
            }
        } else {
            if (edge_in_agm[w] == 3) {
                cout << "at least one" << endl;
            } else if (edge_in_agm[w] == 2) {
                cout << "any" << endl;
            } else {
                cout << "none" << endl;
            }
        }
    }
    
    return 0;
}
