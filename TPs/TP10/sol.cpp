#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <unordered_map>
#include <cstdlib>

using namespace std;
using node = pair<int, int>; // node = (floor, elevator);

// NOTES: build graph and solve with dijkstra, this is sufficient for solving but could not solve in time. Start from there and go on.

// 1. build graph as floor nodes with elevator states, and get costs between floors of same state.
// 2. solve with dijkstra

struct hash_pair {
    template <class T1, class T2>
    size_t operator() (const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

map<node, map<node, int>> build_graph(vector<vector<int>> elevators_floors, vector<int> T, int n) {
    map<node, map<node, int>> graph;

    for (int i=0; i<n; i++) {
        for (int floor1: elevators_floors[i]) {
            for (int floor2: elevators_floors[i]) {
                if (floor1 != floor2) {
                    int cost = T[i] * abs(floor1 - floor2);
                    graph[{floor1, i}][{floor2, i}] = cost;
                    graph[{floor2, i}][{floor1, i}] = cost;
                }
            }
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; i<n; i++) {
            if (i != j) {
                for (int floor1: elevators_floors[i]) {
                    for (int floor2: elevators_floors[j]) {
                        if (floor1 == floor2) {
                            graph[{floor1, i}][{floor2, j}] = 60;
                            graph[{floor2, j}][{floor1, i}] = 60;
                        }
                    }
                }
            }
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
        map<node, map<node, int>> graph = build_graph(elevators_floors, T, n);

        for (const auto& source : graph) {
            std::cout << "Node (" << source.first.first << ", " << source.first.second << ") has edges:\n";
            for (const auto& dest : source.second) {
                std::cout << "  -> (" << dest.first.first << ", " << dest.first.second << ") with cost " << dest.second << "\n";
            }
        }

    }
    return 0;
}
