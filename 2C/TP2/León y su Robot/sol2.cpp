#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

int kruskalMST(vector<tuple<int, int, int>>& edges, int n) {
    long long mst_weight = 0;
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int aristas = 0;

    for (auto [w, u, v] : edges) {
        if (dsu.findSet(u) != dsu.findSet(v)) {
            dsu.unionByRank(u, v);
            mst_weight += w;
            aristas++;
        } 
        if (aristas == n - 1) break;
    }

    if (aristas == n - 1) return mst_weight;
    else return -1;
}

int main() {
    int n, m; cin >> n >> m;

    vector<long long> assigned_node_weight(n);
    vector<tuple<int, int, long long>> edges(m);

    for (int i=0; i<n; i++) {
        cin >> assigned_node_weight[i];
    }

    for (int i=0; i<m; i++) {
        int x, y, w; cin >> x >> y >> w;
        int assigned_cost = assigned_node_weight[x] + assigned_node_weight[y]; 
        if (assigned_cost > w) {
            edges.emplace_back(x, y, w);
        } else {
            edges.emplace_back(x, y, assigned_cost);
        }
    }
    
    long long mst_cost = kruskalMST(edges, n);

    return 0;
}