#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>
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
        // Si el nodo es su propio padre, entonces es el representante
        if (node == parent[node]) return node;

        // Hacemos path compression
        return parent[node] = findSet(parent[node]);
    }

    void unionByRank(int u, int v) {
        int uRepresentative = findSet(u);
        int vRepresentative = findSet(v);

        // Si tienen el mismo representante, ya están en el mismo conjunto
        if (uRepresentative == vRepresentative) return;

        // Unimos los conjuntos según el rank
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

int kruskal_mst_weight(vector<tuple<int, int, int>>& edges, int n) {
    long long mst_weight = 0;
    sort(edges.begin(), edges.end());
    DSU dsu(n);

    int aristas = 0;
    for (auto [w, u, v] : edges) {
        // Si u y v no pertenecen al mismo conjunto,
        if (dsu.findSet(u) != dsu.findSet(v)) {
            // los unimos
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
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges(m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }

    int mst_weight = kruskal_mst_weight(edges, n);

    cout << mst_weight << endl;

    return 0;
}
