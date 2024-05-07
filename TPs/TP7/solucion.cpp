#include <iostream>
#include <vector>
using namespace std;

// NOTES: 
// there is no graph as tree, cant use DFS or BFS. Look for Djikstra or A*

int main() {
    int r, d, s;

    while (true) {
        cin >> r >> d >> s;

        if (r == 0 && d == 0 && s == 0) break;

        // represent graphs as adjacents lists
        vector<vector<int>> door_graph(r); // O(r) allocate r cells in memo
        vector<vector<int>> switches_graph(r); // O(r) 

        for (int t=0; t<d; t++) { // builds door_graph. Iterating over all edges O(d) 
            int i, j; cin >> i >> j;
            // door connects both i, j rooms
            door_graph[i-1].push_back(j-1); // O(1) since i already allocated memory
            door_graph[j-1].push_back(i-1); // O(1)
        } 

        for (int t=0; t<s; t++) { // builds lights_graph. Iterating over all switches O(s)
            int k, l; cin >> k >> l;
            // room k switches room l
            switches_graph[k-1].push_back(l-1); 
        }
    }

    return 0;
}