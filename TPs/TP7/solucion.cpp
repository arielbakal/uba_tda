#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

// NOTES: 
// Solve with BFS. Remove unnecesary includes

unordered_map<int, int> bfs(const vector<vector<int>>& grafo, int nodo_inicial) {

    vector<bool> visitados(grafo.size(), false);
    queue<int> cola;
    unordered_map<int, int> padres;

    cola.push(nodo_inicial);
    visitados[nodo_inicial] = true;

    while (!cola.empty()) {
        int nodo_actual = cola.front();
        cola.pop();

        for (int vecino : grafo[nodo_actual]) {
            if (!visitados[vecino]) {
                cola.push(vecino);
                padres[vecino] = nodo_actual;
                visitados[vecino] = true;
            }
        }
    }

    return padres;
}

vector<int> encontrar_camino(const unordered_map<int, int>& padres, int inicio, int fin) {
    vector<int> camino;
    int nodo_actual = fin;

    while (nodo_actual != inicio) {
        // Usamos at() en lugar de [] para acceder a elementos en un unordered_map const
        auto it = padres.find(nodo_actual);
        if (it != padres.end()) {  // Verificar si el nodo tiene un padre
            camino.push_back(nodo_actual);
            nodo_actual = it->second;  // Obtener el valor (padre) del iterador
        } else {
            return {}; // No se encontró un camino
        }
    }

    camino.push_back(inicio); // Agregar el nodo inicial
    reverse(camino.begin(), camino.end()); // Invertir el camino
    return camino;
}
int main() {
    int r, d, s;
    int case_num = 0;

    while (true) {
        cin >> r >> d >> s;

        if (r == 0 && d == 0 && s == 0) break;

        case_num++;
        cout << "Villa #" << case_num << endl;
        
        // represent graphs as adjacents lists
        vector<vector<int>> doors_graph(r); // O(r) allocate r cells in memo
        vector<vector<int>> switches_graph(r); // O(r)
        vector<bool> visited(r, false); // tracking visited rooms

        for (int t = 0; t < d; t++) { // builds door_graph. Iterating over all edges O(d) 
            int i, j;
            cin >> i >> j;
            // door connects both i, j rooms
            doors_graph[i - 1].push_back(j - 1); // O(1) since i already allocated memory
            doors_graph[j - 1].push_back(i - 1); 
        }

        for (int t = 0; t < s; t++) { // builds lights_graph. Iterating over all switches O(s)
            int k, l;
            cin >> k >> l;
            // room k switches room l
            switches_graph[k - 1].push_back(l - 1);
        }

        unordered_map<int, int> tree = bfs(doors_graph, 0);
        
        vector<int> camino = encontrar_camino(tree, 0, r-1);

        for (int paso: camino) {
            cout << paso << endl;
        }
    }

    return 0;
}
