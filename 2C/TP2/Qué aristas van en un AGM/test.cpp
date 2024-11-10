#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
#include <functional>

using namespace std;

vector<int> ids, low;
vector<bool> visited;
int timeCounter;

void tarjan(int u, int parent, const vector<vector<int>>& adj, int w,
            map<tuple<int, int, int>, int>& classified_edges,
            vector<int>& ids, vector<int>& low, vector<bool>& visited, int& timeCounter) {
    visited[u] = true;
    ids[u] = low[u] = timeCounter++;

    for (int v : adj[u]) {
        if (v == parent) continue;
        if (!visited[v]) {
            tarjan(v, u, adj, w, classified_edges, ids, low, visited, timeCounter);
            low[u] = min(low[u], low[v]);

            if (low[v] > ids[u]) {
                classified_edges[{w, u, v}] = 2;
                classified_edges[{w, v, u}] = 2;
            }
        } else {
            low[u] = min(low[u], ids[v]);
        }
    }
}

void processNewEdges(vector<tuple<int, int, int>>& new_edges, vector<vector<int>>& adj,
                     int w, map<tuple<int, int, int>, int>& classified_edges, vector<int>& ids, vector<int>& low, vector<bool>& visited, int& timeCounter) {
                         
    for (auto [_, u, v] : new_edges) {
        ids[u] = low[u] = -1;
        visited[u] = false;
        ids[v] = low[v] = -1;
        visited[v] = false;
    }

    for (auto [_, u, v] : new_edges) {
        if (!visited[u]) {
            tarjan(u, -1, adj, w, classified_edges, ids, low, visited, timeCounter);
        }
        if (!visited[v]) {
            tarjan(v, -1, adj, w, classified_edges, ids, low, visited, timeCounter);
        }
    }
}


class DSU {
    vector<int> rank, parent;
public:
    DSU(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findSet(int node) {
        if (node != parent[node]) {
            parent[node] = findSet(parent[node]);  // Path compression
        }
        return parent[node];
    }

    void unionByRank(int u, int v) {
        int uRep = findSet(u);
        int vRep = findSet(v);
        if (uRep != vRep) {
            if (rank[uRep] < rank[vRep]) {
                parent[uRep] = vRep;
            } else if (rank[uRep] > rank[vRep]) {
                parent[vRep] = uRep;
            } else {
                parent[vRep] = uRep;
                rank[uRep]++;
            }
        }
    }
};

void kruskalMST(vector<tuple<int, int, int>> edges, int n,
                map<tuple<int, int, int>, int>& classified_edges,
                map<int, int>& count_weights, map<int, vector<tuple<int, int, int>>>& rep_weight_edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    vector<vector<int>> subgraph(n + 1);
    int last_rep_weight = -1;

    // Inicialización de vectores globales para Tarjan
    ids.assign(n, -1);
    low.assign(n, -1);
    visited.assign(n, false);
    timeCounter = 0;
    vector<tuple<int, int, int>> new_edges(n);

    for (auto [w, u, v] : edges) {
        if (dsu.findSet(u) != dsu.findSet(v)) {
            if (count_weights[w] > 1 && last_rep_weight != w) {
                last_rep_weight = w;

                for (auto [rep_w, rep_u, rep_v] : rep_weight_edges[w]) {
                    if (dsu.findSet(rep_u) != dsu.findSet(rep_v)) {
                        subgraph[rep_u].push_back(rep_v);
                        subgraph[rep_v].push_back(rep_u);
                        new_edges.emplace_back(rep_w, rep_u, rep_v);
                    } else {
                        classified_edges[{rep_w, rep_u, rep_v}] = 0;
                    }
                }
                // Ejecutar Tarjan solo en las nuevas aristas
                processNewEdges(new_edges, subgraph, w, classified_edges, ids, low, visited, timeCounter);
                new_edges.clear();
            }
            dsu.unionByRank(u, v);
            subgraph[u].push_back(v);
            subgraph[v].push_back(u);
            if (count_weights[w] == 1) {
                classified_edges[{w, u, v}] = 2;
            }
        } else {
            if (count_weights[w] == 1) {
                classified_edges[{w, u, v}] = 0;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    map<int, string> classify_names = {{0, "none"}, {1, "at least one"}, {2, "any"}};
    vector<tuple<int, int, int>> edges;
    map<int, int> count_weights;
    map<tuple<int, int, int>, int> classified_edges;
    map<int, vector<tuple<int, int, int>>> rep_weight_edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.emplace_back(w, u, v);
        rep_weight_edges[w].emplace_back(w, u, v);
        count_weights[w]++;
        classified_edges[{w, u, v}] = 1;
    }

    kruskalMST(edges, n, classified_edges, count_weights, rep_weight_edges);

    for (const auto& [w, u, v] : edges) {
        cout << classify_names[classified_edges[{w, u, v}]] << endl;
    }

    return 0;
}
