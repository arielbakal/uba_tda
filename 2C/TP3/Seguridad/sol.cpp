#include <iostream>
#include <queue>
#include <vector>
#include <utility> 
#include <limits>

using namespace std;

// Solution: 1) dijkstra saving pred 2) backtrack pred with dfs summing edges (costs) once for each shortest path 3) return total_cost*int32_t
// Solution2: 1) dijkstra saving pred 2) dfs to create pred tree 3) dfs to sum costs 4) return total_cost*2

long long dijkstra(const vector<vector<pair<int, int>>>& graph, int n, int source) {
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
    
    for ()
    
    return dist[n-1];
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
    long long all_min_dist = dijkstra(graph, n, 0);

    // return 2*c_0 + 2*c_k + ... + 2*c_n-1 = 2*Σ(c_p) = 2*(shortest path between 0 and n-1) where 0<k<n-1
    // and k represents the nodes idx from the shortest path between 0 and n-1, then p={0,k....,n-1}
    cout << 2*all_min_dist;

    return 0;
}