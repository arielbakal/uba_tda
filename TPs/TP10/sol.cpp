#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

// NOTES: build graph and solve with dijkstra, this is sufficient for solving but could not solve in time. Start from there and go on.

// 1. build graph as floor nodes with elevator states, and get costs between floors of same state.
// 2. solve with dijkstra

unordered_map<int, vector<int>> build_graph(vector<vector<int>> elevators_floors, int n) {
    unordered_map<int, vector<int>> graph;

    for (int i=0; i<n; i++) {
        int elevator_index = 100+i;
        for (int floor: elevators_floors[i]) {
            graph[floor].push_back(elevator_index);
            graph[elevator_index].push_back(floor);
        }
    }

    return graph;

}


int main() {
    while (true) {
        int n; // n elevators
        int k; // objective k floor
        if (!(cin >> n >> k)) break;

        vector<int> T(n); // each elevator's time between adjacent floors 
        for (int i = 0; i < n; i++) {
            cin >> T[i]; 
        }

        vector<vector<int>> elevators_floors(n);

        cin.ignore(); // to ignore the newline character left in the input buffer

        for (int j = 0; j < n; j++) {
            string line;    
            getline(cin, line);
            istringstream iss(line);
            int number;
            while (iss >> number) {
                elevators_floors[j].push_back(number);
            }
        }

        unordered_map<int, vector<int>> graph = build_graph(elevators_floors, n);

    }
    return 0;
}
