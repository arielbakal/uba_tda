#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>
#include <string>

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

int kruskalMST(vector<tuple<int, int, int>>& edges, int n,
               unordered_map<tuple<int, int, int>, int, tuple_hash>& classified_edges,
               unordered_map<int, int>& count_weights) {
    long long mst_weight = 0;
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int aristas = 0;
    vector<vector<int>> agm(n + 1);

    for (auto [w, u, v] : edges) {
        if (dsu.findSet(u) != dsu.findSet(v)) {
            // Si hay aristas de peso repetido, pausa y verifica el subgrafo actual
            // if (count_weights[w] > 1) {
            // }
            dsu.unionByRank(u, v);
            mst_weight += w;
            agm[u].push_back(v);
            agm[v].push_back(u);
            classified_edges[{w, u, v}] = 2;  
            aristas++;
        } else {
            classified_edges[{w, u, v}] = 0;  
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

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        unsorted_edges.push_back({w, u, v});
        count_weights[w]++;
        edges.push_back({w, u, v});
    }

    int mst_weight = kruskalMST(edges, n, classified_edges, count_weights);

    cout << "Peso del MST: " << mst_weight << endl;

    for (auto [w, u, v] : unsorted_edges) {
        cout << w << ": " << classify_names[classified_edges[{w, u ,v}]] << endl;
    }

    return 0;
}
