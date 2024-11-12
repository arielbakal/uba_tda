#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int INF = numeric_limits<int>::max();

void summing_dantzig(vector<vector<int>>& L, int n, vector<long long>& subgraph_k_sum) {
    for (int k=0; k<n-1; k++) {
        long long subgraph_sum = 0;
        for (int i=0; i<=k; i++) {
            int min_a = INF;
            int min_b = INF;
            for (int j=0; j<=k; j++) {
                min_a = min(min_a, L[i][j]+L[j][k+1]);
                min_b = min(min_b, L[k+1][j]+L[j][i]);
            }
            L[i][k+1] = min_a;
            L[k+1][i] = min_b;
            subgraph_sum += L[i][k+1] + L[k+1][i];
        } 
        for (int i=0; i<=k; i++) {
            for (int j=0; j<=k; j++) {
                L[i][j] = min(L[i][j], L[i][k+1]+L[k+1][j]);
                if (i!=j) subgraph_sum += L[i][j];
            }
        }
        subgraph_k_sum[k] = subgraph_sum;
    }    
}

int main() {
    int n; cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    vector<vector<int>> built_ordered_graph(n, vector<int>(n));
    vector<long long> subgraph_k_sum(n);
    vector<int> removing_order(n);

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> graph[i][j]; 
        }
    }
    for (int i=0; i<n; i++) {
        int idx; cin >> idx;
        removing_order[i] = idx - 1;
    }
    // since we remove from the last built node (city corner) til the first one, we should build subgraph_k and get the sum in Dantzig
    // from a graph matrix where node's idx are represented by its built order.

    // lets grab the original matrix and re-index it
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            built_ordered_graph[i][j] = graph[removing_order[n-1-i]][removing_order[n-1-j]];
        }
    }
    
    // then get each subgraph_k_sum for first k built nodes
    summing_dantzig(built_ordered_graph, n, subgraph_k_sum);

    // reverse and print subgraph_k_sum to simulate removing last built nodes 
    for (int k=n-2; k>=0; k--) {
        cout << subgraph_k_sum[k] << " ";
    }
    cout << 0;

    return 0;
}