#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// We have M partial sums constraints of the solution, where each b_i = d(v_0, v_i) is equal to the cumulative sum up to i-th var 
// then each term a_i = b_i - b_i-1 = d(v_0, v_i) - d(v_0, v_i-1)
// This cancel out almost all the terms of the partial sum getting d(v_0, v_si+ni) - d(v_0, v_si-1) <= k_i -1
// which can be represented in a graph as v_si-1 -> v_si+ni costs k_i-1
// OBS! handle properly a_0 and for "gt" operator invert the constraint by multiplying by -1

struct edge {int from, to, weight;};
int INF = numeric_limits<int>::max();

bool has_solution(vector<edge>& edges, int N) { // bellman-ford modified to only return if there's any negative weight cycle

    bool res = true;

    vector<long long> dist(N+2, INF);
    dist[N+1] = 0;

    // update distances
    for (int i=0; i<N+2; i++) {
        for (auto edge: edges) {
            dist[edge.to] = min(dist[edge.to], dist[edge.from] + edge.weight);
        }
    }

    // check for negative weight cycles (dist can still be updated)
    for (auto edge: edges) {
        if (dist[edge.to] > dist[edge.from] + edge.weight) {
            res = false;
            break;
        }
    }

    return res;
}

int main() {
    int N, M;
    int s, n, k; string o;
    vector<edge> edges;
    string line;
    
    while (cin >> N) {
        if (N == 0) break;
        cin >> M;
        
        cin.ignore();

        edges.resize(M);
        
        for (int i=0; i<M; i++) {
            cin >> s >> n >> o >> k;
            if (o == "gt") edges[i] ={s+n, s-1, -k-1}; else edges[i] = {s-1, s+n, k-1}; // if "gt" invert equation
        }
        for (int i=0; i<=N; i++) {
            edges.push_back({N+1, i, 0}); // since v_0 is used, we use v_n+1 as our vector connected to each vector with cost 0
        }
        // then we got N+2 nodes, i=0..N+1
        
        bool result = has_solution(edges, N); // there isnt a negative weight cycle (bellman-ford finds dictances vector)
        
        if (result) cout << "lamentable kingdom"; else cout << "successful conspiracy";
        
        cout << endl;
    }
    return 0; 
}