#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
#include <functional>

using namespace std;

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

void tarjan(const vector<vector<int>>& adj, int n, int w, map<tuple<int, int, int>, int>& classified_edges) {
    vector<int> ids(n, -1), low(n, -1);
    vector<bool> visited(n, false);
    int time = 0;

    function<void(int, int)> dfs = [&](int u, int parent) {
        visited[u] = true;
        ids[u] = low[u] = time++;

        for (int v : adj[u]) {
            if (v == parent) continue;
            if (!visited[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > ids[u]) {
                    classified_edges[{w, u, v}] = 2;
                    classified_edges[{w, v, u}] = 2;
                }
            } else {
                low[u] = min(low[u], ids[v]);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }
}

void kruskalMST(vector<tuple<int, int, int, int>>& edges, int n,
               map<tuple<int, int, int>, int>& classified_edges,
               map<int, int>& count_weights, map<int, vector<tuple<int, int, int>>>& rep_weight_edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    vector<vector<int>> agm(n + 1);
    int last_rep_weight = -1;

    for (auto [w, u, v, index] : edges) {
        if (dsu.findSet(u) != dsu.findSet(v)) {
            if (count_weights[w] > 1 && last_rep_weight != w) {
                last_rep_weight = w;
                vector<vector<int>> subgraph(agm);
                for (auto [rep_w, rep_u, rep_v] : rep_weight_edges[w]) {
                    if (dsu.findSet(rep_u) != dsu.findSet(rep_v)) {
                        classified_edges[{rep_w, rep_u, rep_v}] = 1;
                        subgraph[rep_u].push_back(rep_v);
                        subgraph[rep_v].push_back(rep_u);
                    } else {
                        classified_edges[{rep_w, rep_u, rep_v}] = 0;
                    }
                }
                tarjan(subgraph, n, w, classified_edges);
            }
            dsu.unionByRank(u, v);
            agm[u].push_back(v);
            agm[v].push_back(u);
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
    vector<tuple<int, int, int, int>> edges;
    map<int, int> count_weights;
    map<tuple<int, int, int>, int> classified_edges;
    map<int, vector<tuple<int, int, int>>> rep_weight_edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.emplace_back(w, u, v, i);
        rep_weight_edges[w].emplace_back(w, u, v);
        count_weights[w]++;
    }

    kruskalMST(edges, n, classified_edges, count_weights, rep_weight_edges);

    vector<string> output(m);
    for (const auto& [w, u, v, index] : edges) {
        output[index] = classify_names[classified_edges[{w, u, v}]];
    }

    for (const auto& result : output) {
        cout << result << endl;
    }

    return 0;
}
