#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

// Estructura para DSU (Union-Find)
struct DSU {
    vector<int> parent, rank;

    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;

        if (rank[x] < rank[y]) {
            parent[x] = y;
        } else if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[y] = x;
            ++rank[x];
        }
        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Encuentra el nodo con el peso mínimo
    int min_node = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[min_node]) {
            min_node = i;
        }
    }

    // Lista de aristas: (peso, nodo1, nodo2)
    vector<tuple<long long, int, int>> edges;

    // Conecta todos los nodos al nodo con peso mínimo
    for (int i = 0; i < n; ++i) {
        if (i != min_node) {
            edges.emplace_back(a[min_node] + a[i], min_node, i);
        }
    }

    // Añade las ofertas especiales como aristas
    for (int i = 0; i < m; ++i) {
        int x, y;
        long long w;
        cin >> x >> y >> w;
        --x; --y;  // Convierte a índice 0
        edges.emplace_back(w, x, y);
    }

    // Ordena las aristas por peso
    sort(edges.begin(), edges.end());

    // Aplica el algoritmo de Kruskal
    DSU dsu(n);
    long long mst_cost = 0;
    for (auto& [w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            mst_cost += w;
        }
    }

    cout << mst_cost << endl;

    return 0;
}
