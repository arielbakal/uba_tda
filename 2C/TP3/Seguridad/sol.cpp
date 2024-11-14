#include <iostream>
#include <queue>
#include <vector>
#include <utility> 
#include <limits>
#include <tuple>

using namespace std;

vector<long long> dijkstra(const vector<vector<pair<int, int>>>& graph, int n, int source) {
    int INF = numeric_limits<int>::max();
    int diff_shortest_paths = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<long long> dist(n, INF);
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        // Explore neighbors
        for (const auto &neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            // If a shorter path to v is found
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            } 
        }
    }
    
    return dist;
}

void dfs(int u, int n, vector<bool>& visited, const vector<vector<pair<int, int>>>& graph, const vector<long long>& min_dist, long long& total_cost) {
    visited[u] = true;

    for (const auto& [v, c] : graph[u]) {
        if (!visited[v]) {
            if (min_dist[u] == min_dist[v] + c) {
                total_cost += c;
                if (v != 0) {   
                    dfs(v, n, visited, graph, min_dist, total_cost);
                }
            }
        }   
        
    }
}

int main() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);

    for (int i=0; i<m; i++) {
        int v, w, c; cin >> v >> w >> c;
        // build adj list O(m+n)
        if (v!=w) { // avoid loop edges
            // saving pair<w, c> as a neighbor of v ensures multi-edges handling bc they will be unique in that way
            // i can easily access c(v,w) also 
            graph[v].emplace_back(w, c);
            graph[w].emplace_back(v, c);
        }
    }
    // dijkstra impl with binary heap => O((m+n)logn) = O(m.log(n)) since m > n
    vector<long long> all_min_dist = dijkstra(graph, n, 0);

    long long total_cost = 0;

    vector<bool> visited(n);
    dfs(n-1, n, visited, graph, all_min_dist, total_cost);

    cout << total_cost*2 << endl;

    return 0;
}