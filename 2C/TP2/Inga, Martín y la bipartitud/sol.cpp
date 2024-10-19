#include <iostream>
#include <vector>
using namespace std;

// Tenemos un grafo de n nodos y luego n-1 aristas. El grafo siempre es arbol
// Para evitar crear espacios sin utilizar en graph, la enumeracion de los vertices comienza en 0. Por lo tanto cada enumeracion se le resta 1

int main() {

    int n; cin >> n; 

    vector<vector<int>> graph(n);

    for (int i=0; i<n-1; i++) { // leemos las n-1 aristas
        int u, v; cin >> u >> v;

        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }

    return 0;
}