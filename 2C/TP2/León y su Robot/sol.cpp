#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// TODO: no pasa por memory limit, en el priority queue se acumula muchos pesos gigantes
// y en un punto se excede. Segun chatgpt hay que hacer la idea de sol2.cpp

long long primMST(int n, vector<vector<pair<int, long long>>>& adj, vector<long long>& assigned_node_weight) {
    
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    vector<bool> visited(n, false);
    long long mst_cost = 0;
    
    pq.push({0, 0});
    
    while(!pq.empty()){
        auto p = pq.top();
        pq.pop();

        long long wt = p.first;  
        int u = p.second; 

        if (visited[u] == true){
            continue; 
        }
        
        mst_cost += wt; 
        visited[u] = true; 

        for (auto [v, original_weight] : adj[u]) {
            if (!visited[v]) {
                pq.push({min(original_weight, assigned_node_weight[u] + assigned_node_weight[v]);, v});
            }
        }
        
        for(int v=0; v<n; v++){
            if (v!=u && !visited[v]) {
                pq.push({assigned_node_weight[u] + assigned_node_weight[v], v});  
            }
        }
    }
    return mst_cost;  
}

int main() {
    int n, m; cin >> n >> m;

    vector<long long> assigned_node_weight(n);
    vector<vector<pair<int, long long>>> adj(n);

    for (int i=0; i<n; i++) {
        cin >> assigned_node_weight[i];
    }

    for (int i=0; i<m; i++) {
        int x, y; cin >> x >> y;
        long long w; cin >> w;
        adj[x-1].emplace_back(y-1, w);
        adj[y-1].emplace_back(x-1, w);
    }

    long long mst_cost = primMST(n, adj, assigned_node_weight);

    cout << mst_cost << endl;

    return 0;
}