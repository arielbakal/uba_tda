#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// NOTES: 
// Solve with BFS. Remove unnecesary includes

vector<int> bfs(const vector<vector<int>>& grafo, int nodo_inicial, int nodo_final) {
    vector<bool> visitados(grafo.size(), false);
    queue<int> cola;
    vector<int> padres(grafo.size(), -1); // Inicializamos padres a -1 (sin padre)
    vector<int> camino;

    cola.push(nodo_inicial);
    visitados[nodo_inicial] = true;

    while (!cola.empty()) {
        int nodo_actual = cola.front();
        cola.pop();

        if (nodo_actual == nodo_final) {
            // Reconstruir el camino desde el nodo final hasta el inicial
            while (nodo_actual != nodo_inicial) {
                camino.push_back(nodo_actual);
                nodo_actual = padres[nodo_actual];
            }
            camino.push_back(nodo_inicial);
            reverse(camino.begin(), camino.end()); // Invertir el camino
            return camino;
        }

        for (int vecino : grafo[nodo_actual]) {
            if (!visitados[vecino]) {
                cola.push(vecino);
                padres[vecino] = nodo_actual;
                visitados[vecino] = true;
            }
        }
    }
    return camino;  // Retornamos un vector vacío si no se encuentra el camino
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

        vector<int> camino = bfs(doors_graph, 0, r-1);

        for (int paso: camino) {
            cout << paso << endl;
        }
    }

    return 0;
}
