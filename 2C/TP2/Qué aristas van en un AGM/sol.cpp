#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>
#include <string>
#include <map>

using namespace std;

struct tuple_hash {
    std::size_t operator()(const std::tuple<int, int, int>& t) const {
        auto [a, b, c] = t;
        std::size_t h1 = std::hash<int>{}(a);
        std::size_t h2 = std::hash<int>{}(b);
        std::size_t h3 = std::hash<int>{}(c);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class DSU {
    vector<int> rank, parent;
public:
    DSU(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i < n + 1; i++) {
            parent[i] = i;
        }
    }

    int findSet(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findSet(parent[node]);
    }

    void unionByRank(int u, int v) {
        int uRepresentative = findSet(u);
        int vRepresentative = findSet(v);
        if (uRepresentative == vRepresentative) return;
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else if (rank[uRepresentative] > rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};

// vector<pair<int, int>> tarjan(const vector<vector<int>>& adj, int n) {
//     vector<int> ids(n, -1), low(n, -1);
//     vector<bool> visited(n, false);
//     vector<pair<int, int>> bridges;
//     int time = 0;

//     // Función DFS para encontrar puentes
//     function<void(int, int)> dfs = [&](int u, int parent) {
//         visited[u] = true;
//         ids[u] = low[u] = time++;

//         // Recorremos todos los vecinos de u
//         for (int v : adj[u]) {
//             if (v == parent) continue;  // Ignoramos la arista de vuelta al padre

//             if (!visited[v]) {
//                 dfs(v, u);
//                 low[u] = min(low[u], low[v]);

//                 // Si low[v] > ids[u], entonces (u, v) es un puente
//                 if (low[v] > ids[u]) {
//                     bridges.push_back({u, v});
//                 }
//             } else {
//                 low[u] = min(low[u], ids[v]);
//             }
//         }
//     };

//     // Recorrer cada nodo que no ha sido visitado
//     for (int i = 0; i < n; i++) {
//         if (!visited[i]) {
//             dfs(i, -1);
//         }
//     }

//     return bridges;
// }

bool dfs_path_tracking(int u, int parent, vector<bool>& visited, vector<int>& path, vector<pair<int, int>>& cycle_edges, vector<vector<int>>& graph) {
    visited[u] = true;
    path.push_back(u);

    for (int v : graph[u]) {
        if (!visited[v]) {
            if (dfs_path_tracking(v, u, visited, path, cycle_edges, graph)) {
                return true;
            }
        } else if (v != parent) {
            // encontramos un ciclo
            int i = path.size() - 1;
            while (path[i] != v) {
                cycle_edges.push_back({path[i - 1], path[i]});
                i--;
            }
            cycle_edges.push_back({u, v});
            return true;
        }
    }

    path.pop_back();
    return false;
}

vector<pair<int, int>> findCycle(int n, vector<bool>& visited, vector<int>& path, vector<pair<int, int>>& cycle_edges, vector<vector<int>> graph) {
    visited.assign(n, false);
    path.clear();
    cycle_edges.clear();

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs_path_tracking(i, -1, visited, path, cycle_edges, graph)) {
            break;
        }
    }
    return cycle_edges;
}

int kruskalMST(vector<tuple<int, int, int>>& edges, int n,
               unordered_map<tuple<int, int, int>, int, tuple_hash>& classified_edges,
               unordered_map<int, int>& count_weights, map<tuple<int, int>, int> edges_weight) {
    long long mst_weight = 0;
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int aristas = 0;
    vector<vector<int>> agm(n + 1);
    int last_rep_weight = -1;

    for (auto [w, u, v] : edges) {
        if (dsu.findSet(u) != dsu.findSet(v)) {
            // Si hay aristas de peso repetido, pausa y verifica en el agm actual todas las aristas repetidas de peso w actual
            if (count_weights[w] > 1) {
                if (last_rep_weight != w) {
                    last_rep_weight = w;
                    vector<vector<int>> subgraph;
                    subgraph.assign(agm.begin(), agm.end());
                    for (auto [rep_w, rep_u, rep_v] : edges) {
                        if (w == rep_w) {
                            if (dsu.findSet(rep_u) != dsu.findSet(rep_v)) { // vemos si la arista puede unir dos disjoint sets,
                                // si independientemente no forma un ciclo, es ANY
                                classified_edges[{rep_w, rep_u, rep_v}] = 2;  
                            } else {
                                // si no, forma un ciclo y es NONE
                                classified_edges[{rep_w, rep_u, rep_v}] = 0;
                            }
                            subgraph[rep_u].push_back(rep_v);
                            subgraph[rep_v].push_back(rep_u);
                        }

                    }
                    // verificamos si agregando todas las repetidas formamos algun ciclo y
                    // las que formen parte de aquel ciclo, son AT LEAST ONE
                    vector<bool> visited;    
                    vector<int> path;         
                    vector<pair<int, int>> cycle_edges;
                    cycle_edges = findCycle(n, visited, path, cycle_edges, subgraph);
                    for (const auto& [cycle_u, cycle_v] : cycle_edges) {
                        classified_edges[{w, cycle_u, cycle_v}] = 1;
                        classified_edges[{w, cycle_v, cycle_u}] = 1;
                    }
                }
            } 
            dsu.unionByRank(u, v);
            mst_weight += w;
            agm[u].push_back(v);
            agm[v].push_back(u);
            if (count_weights[w] == 1) {
                classified_edges[{w, u, v}] = 2;  
            }
            aristas++;
        } else {
            if (count_weights[w] == 1) {
                classified_edges[{w, u, v}] = 0;  
            }
        }
        if (aristas == n - 1) break;
    }

    if (aristas == n - 1) return mst_weight;
    else return -1;
}

int main() {
    int n, m;
    cin >> n >> m;

    unordered_map<int, string> classify_names;
    classify_names[0] = "none";
    classify_names[1] = "at least one";
    classify_names[2] = "any";
    
    vector<tuple<int, int, int>> unsorted_edges;
    vector<tuple<int, int, int>> edges;
    unordered_map<int, int> count_weights;
    unordered_map<tuple<int, int, int>, int, tuple_hash> classified_edges; 
    map<tuple<int, int>, int> edges_weight;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        unsorted_edges.push_back({w, u-1, v-1});
        edges_weight[{u-1, v-1}] = w;
        count_weights[w]++;
        edges.push_back({w, u-1, v-1});
    }

    int mst_weight = kruskalMST(edges, n, classified_edges, count_weights, edges_weight);

    // cout << "Peso del MST: " << mst_weight << endl;

    // for (auto [w, u, v] : unsorted_edges) {
    //     cout << w << ": " << classify_names[classified_edges[{w, u ,v}]] << endl;
    // }

    for (auto [w, u, v] : unsorted_edges) {
        cout << classify_names[classified_edges[{w, u ,v}]] << endl;
    }

    return 0;
}
