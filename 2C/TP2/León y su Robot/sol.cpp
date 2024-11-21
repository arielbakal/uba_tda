#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

long long INF = numeric_limits<long long>::max();

long long primMST(int n, vector<vector<long long>>& adj, vector<long long>& assigned_node_weight) {
    
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
        
        for(int v=0; v<n; v++){
            if(v!=u && visited[v] == false){
                pq.push({min(assigned_node_weight[u] + assigned_node_weight[v], adj[u][v]), v});  
            }
        }
    }
    
    return mst_cost;  
}

int main() {
    int n, m; cin >> n >> m;

    vector<long long> assigned_node_weight(n);
    vector<vector<long long>> adj(n, vector<long long>(n, INF));

    for (int i=0; i<n; i++) {
        cin >> assigned_node_weight[i];
    }

    for (int i=0; i<m; i++) {
        int x, y; cin >> x >> y;
        long long w; cin >> w;
        adj[x-1][y-1] = min(adj[x-1][y-1], w);
        adj[y-1][x-1] = min(adj[y-1][x-1], w);
    }

    long long mst_cost = primMST(n, adj, assigned_node_weight);

    cout << mst_cost << endl;

    return 0;
}