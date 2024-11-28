#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
#include <functional>
#include <unordered_map>

using namespace std;

vector<vector<int>> subgraph;
vector<int> classified_edges;
vector<tuple<int, int, int, int>> edges;
vector<int> u, d, l;
int timeCounter;

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

void dfs(int v, DSU dsu, int p = -1, int depth = 0) {
	l[v] = d[v] = depth;
	u[v] = timeCounter+1;
	for (int i = 0; i < (int)subgraph[v].size(); i++) {
		if (subgraph[v][i] == p)continue;
		auto [w, edge_u, edge_v, idx] = edges[subgraph[v][i]];
		int new_u = dsu.findSet(edge_u);
		int new_v = dsu.findSet(edge_v);
		int to = new_u == v ? new_v : new_u;
		if (u[to]>timeCounter)
			l[v] = min(l[v], d[to]);
		else {
			dfs(to, dsu, subgraph[v][i], depth+1);
			l[v] = min(l[v], l[to]);
		}

		if (l[to] > d[v]) {
			classified_edges[idx] = 2;
		}
	}
}

void kruskalMST(vector<tuple<int, int, int, int>> edges, int n, int m,
                vector<int>& classified_edges,
                unordered_map<int, int>& count_weights) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    // Inicialización de vectores globales para Tarjan
    u.assign(n, 0);
    d.assign(n, 0);
    l.assign(n, 0);
    timeCounter = 0;
    
    subgraph.assign(n, vector<int>());

    for (int i=0; i<m;) {
        auto [w, u, v, idx] = edges[i];
        int count_weight = count_weights[w];
        for (int j = i; j < i+count_weight; j++) {
            auto [w, u, v, idx] = edges[j];
            if (dsu.findSet(u) != dsu.findSet(v)) {
                subgraph[u].push_back(j);
                subgraph[v].push_back(j);
            } else {
                classified_edges[idx] = 0;
            }
        }

        for (int j=i; j<i+count_weight; j++) {
            auto [w, u, v, idx] = edges[j];
            int new_u = dsu.findSet(u);
            int new_v = dsu.findSet(v);
            if (u[new_u]<=timeCounter) {
                dfs(new_u, dsu);
            }
            if (u[new_u]<=timeCounter) {
                dfs(new_v, dsu);
            }
        }

        for (int j=i; j<i+count_weight; j++) {
            int new_u = dsu.findSet(u);
            int new_v = dsu.findSet(v);
            dsu.unionByRank(new_u, new_v);
            subgraph[new_u].clear();
            subgraph[new_v].clear();
        }


        i = i + count_weight;
        timeCounter++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    map<int, string> classify_names = {{0, "none"}, {1, "at least one"}, {2, "any"}};
    
    unordered_map<int, int> count_weights;
    
    classified_edges.assign(m, 1);  

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.emplace_back(w, u, v, i);
        count_weights[w]++;
    }

    kruskalMST(edges, n, m, classified_edges, count_weights);

    for (int i=0; i<m; i++) {
        cout << classify_names[classified_edges[i]] << endl;
    }

    return 0;
}
