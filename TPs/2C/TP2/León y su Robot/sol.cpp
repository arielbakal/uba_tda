#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

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

long long kruskalMST(vector<tuple<long long, int, int>>& edges, int n) {
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

    vector<long long> a(n);
    vector<tuple<long long, int, int>> edges(m+n-1);

    for (int i=0; i<n; i++) {
        cin >> a[i];
    }

    // find min assigned weight node
    int min_assigned_weight_node = 0;
    for (int i=0; i<n; i++) {
        if (a[i] < a[min_assigned_weight_node]) {
            min_assigned_weight_node = i;
        }
    }
    
    // since a[u] + a[v] <= a[w] + a[v] for any w!=u and u has min assigned weight,
    // we can just keep all edges to u and build the "base" mst for case m=0 where
    // we dont have any special offer edges

    long long max_base_edges = 0;
    long long base_mst_cost = 0;
    // connect all nodes to the min assigned weight, building the base mst
    for (int i=0; i<n; i++) {
        long long assigned_edge_weight = a[min_assigned_weight_node] + a[i];
        if (i != min_assigned_weight_node) {
            edges.emplace_back(assigned_edge_weight, min_assigned_weight_node, i);
            base_mst_cost += assigned_edge_weight;
            if (assigned_edge_weight > max_base_edges) {
                max_base_edges = assigned_edge_weight;
            }
        }
    }

    // if we have special offer edges (m>0) add them to the base mst, and let kruskal find if
    // they are really special (they minimize even more the mst)
    if (m>0) {
        int count_added_edges = 0;
        for (int i=0; i<m; i++) {
            int x, y; cin >> x >> y;
            long long w; cin >> w;
            if (w < max_base_edges) { // if w < max special edge then we could get a lower mst_cost
                edges.emplace_back(w, x-1, y-1); // re-index to 0
                count_added_edges++;
            }
        }

        if (count_added_edges>0) {
            // find mst from base mst + special offer edges
            long long mst_cost = kruskalMST(edges, n);
            cout << mst_cost << endl;
        } else {
            cout << base_mst_cost << endl;
        }  
    } else {
        cout << base_mst_cost << endl;
    }

    return 0;
}
