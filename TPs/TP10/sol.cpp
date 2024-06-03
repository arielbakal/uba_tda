#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
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

struct Compare {
    bool operator() (const std::pair<node, int>& a, const std::pair<node, int>& b) {
        return a.second > b.second; // Min-heap based on distance
    }
};

map<node, map<node, int>> build_graph(vector<vector<int>> elevators_floors, vector<int> T, int n, int target) {
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
        for (int j=0; j<n; j++) {
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
    for (int i=0; i<n; i++) {
        for (int floor: elevators_floors[i]) {
            if (floor == 0) {
                graph[{0,-1}][{0, i}] = 0;
                graph[{0, i}][{0, -1}] = 0;
            } else if (floor == target) {
                graph[{target,-1}][{target, i}] = 0;
                graph[{target, i}][{target, -1}] = 0;
            }
        }
    }
    return graph;
}


int dijkstra(map<node, map<node, int>> graph, node source, node target) {
    int inf = 10000; // travel time cant exceed 100 seconds x 100 floors;

    priority_queue<pair<node, int>, vector<pair<node, int>>, Compare> pq;
    unordered_map<node, int, hash_pair> distance;

    // Initialize distances to INF
    for (const auto& node : graph) {
        distance[node.first] = inf;
    }
    distance[source] = 0;
    pq.push({source, 0});

    while (!pq.empty()) {
        node current = pq.top().first;
        int currentDist = pq.top().second;
        pq.pop();
        
        // Early exit if we reach the target
        if (current == target) {
            return currentDist;
        }
        
        // If this distance is not the smallest known, skip
        if (currentDist > distance[current]) {
            continue;
        }

        if (graph.find(current) == graph.end()) {
            continue; // Skip if current node is not in the graph
        }
        
        // Explore neighbors
        for (const auto& neighbor : graph.at(current)) {
            node next = neighbor.first;
            int weight = neighbor.second;
            int newDist = currentDist + weight;
            
            if (newDist < distance[next]) {
                distance[next] = newDist;
                pq.push({next, newDist});
            }
        }
    }
    
    // Return the minimum distance to the target, or INF if unreachable
    return distance[target];


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

        bool is_possible = false;

        for (int j = 0; j < n; j++) {
            string line;    
            getline(cin, line);
            istringstream iss(line);
            int number;
            while (iss >> number) {
                elevators_floors[j].push_back(number);
                if (number == k) is_possible = true;
            }
        }

        if (!is_possible) {
            cout << "IMPOSSIBLE" << endl;
        } else if (k == 0) {
            cout << 0 << endl;
        } else {
            map<node, map<node, int>> graph = build_graph(elevators_floors, T, n, k);

            int min_seconds = dijkstra(graph, {0, -1}, {k, -1});

            if (min_seconds == 10000 || min_seconds == 0) {
                cout << "IMPOSSIBLE" << endl;
            } else {
                cout << min_seconds << endl;
            }
        }
        
    }
    return 0;
}
