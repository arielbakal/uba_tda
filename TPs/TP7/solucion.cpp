#include <iostream>
#include <vector>
using namespace std;

// NOTES: 
// there is no graph as tree, cant use DFS or BFS. Look for Djikstra or A*

vector<int> find_shortest_path(int r, vector<vector<int>>& doors, vector<vector<int>>& switches) {
    return {};
}

int main() {
    int r, d, s;
    int case_num;

    while (true) {
        cin >> r >> d >> s;

        if (r == 0 && d == 0 && s == 0) break;

        case_num++;
        cout << "Villa #" << case_num << endl;

        // represent graphs as adjacents lists
        vector<vector<int>> doors_graph(r); // O(r) allocate r cells in memo
        vector<vector<int>> switches_graph(r); // O(r) 

        for (int t=0; t<d; t++) { // builds door_graph. Iterating over all edges O(d) 
            int i, j; cin >> i >> j;
            // door connects both i, j rooms
            doors_graph[i-1].push_back(j-1); // O(1) since i already allocated memory
            doors_graph[j-1].push_back(i-1); // O(1)
        } 

        for (int t=0; t<s; t++) { // builds lights_graph. Iterating over all switches O(s)
            int k, l; cin >> k >> l;
            // room k switches room l
            switches_graph[k-1].push_back(l-1); 
        }

        // building door_graph is O(r+d) and lights_graph is O(r+s)
        
        vector<int> shortest_path = find_shortest_path(r, doors_graph, switches_graph);

        if (shortest_path.empty()) {
            cout << "The problem cannot be solved." << endl;
        } else {
            // implement
        }
    }

    return 0;
}