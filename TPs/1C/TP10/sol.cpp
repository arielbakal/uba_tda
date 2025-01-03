#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstdlib>

using namespace std;
using node = pair<int, int>; // node = (floor, elevator)

// 1. Build graph as floor nodes with elevator states, and get costs between floors of same state.
// We create ghost nodes (0, -1), (target, -1) connected to all (0, i), (target, i) resp. with cost 0.
// These nodes allows fixed starting and target nodes for all test cases and avoids multiple dijkstra iterations for
// any number of floor 0 starting elevators.
// 2. Solve with dijkstra (we only sum distances)

struct hash_pair {
    template <class T1, class T2>
    size_t operator() (const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

struct compare_node {
    bool operator() (const pair<node, int>& a, const pair<node, int>& b) {
        return a.second > b.second; 
    }
};

// unordered_map with node=pair<int, int> as key and pair<node, cost> as values.
// (needed to implement hash and compare_node functions since cpp dont support that type of key. Messy but i wanted to learn how to impl that)
map<node, map<node, int>> build_graph(vector<vector<int>> elevators_floors, vector<int> T, int n, int target) {
    map<node, map<node, int>> graph;

    // build nodes for each state (elevator)
    for (int e=0; e<n; e++) { // iterate over elevators
        int size = elevators_floors[e].size();
        for (int i=0; i<size; i++) {
            for (int j=i+1; j<size; j++) {
                if (i != j) {
                    int floor1 = elevators_floors[e][i];
                    int floor2 = elevators_floors[e][j];
                    int cost = T[e] * abs(floor1 - floor2);
                    graph[{floor1, e}][{floor2, e}] = cost;
                    graph[{floor2, e}][{floor1, e}] = cost;
                }
            }
        }
    }
    // build nodes for each floor sharing states (elevators)
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
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
    // build (0, -1) and (target, -1) nodes and connecting them to (0, i) and (target, i) nodes resp. (i=0..n-1) 
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

    priority_queue<pair<node, int>, vector<pair<node, int>>, compare_node> pq;
    unordered_map<node, int, hash_pair> distance;

    // initialize distances to INF
    for (const auto& node : graph) {
        distance[node.first] = inf;
    }
    
    distance[source] = 0;
    pq.push({source, 0});

    while (!pq.empty()) {
        node current = pq.top().first;
        int current_dist = pq.top().second;
        pq.pop();
        
        // return if we reach target
        if (current == target) {
            return current_dist;
        }
        
        // skip smaller distances
        if (current_dist > distance[current]) {
            continue;
        }

        // skip if node not in graph
        if (graph.find(current) == graph.end()) {
            continue; 
        }
        
        // explore neighbors
        for (const auto& neighbor : graph.at(current)) {
            node next = neighbor.first;
            int weight = neighbor.second;
            int new_dist = current_dist + weight;
            
            // update distances
            if (new_dist < distance[next]) {
                distance[next] = new_dist;
                pq.push({next, new_dist});
            }
        }
    }
    return distance[target]; // return min dist to target, if INF then is unreachable
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

        vector<vector<int>> elevators_floors(n); // vector<floor> for each elevator

        cin.ignore(); // to ignore the newline character left in the input buffer

        bool is_possible = false;

        // read entire line, split up numbers and save (didnt know when to stop iterating for each elevator)
        for (int j = 0; j < n; j++) {
            string line;    
            getline(cin, line);
            istringstream iss(line);
            int number;
            while (iss >> number) {
                elevators_floors[j].push_back(number);
                if (number == k) is_possible = true; // early check if target is reachable
            }
        }

        if (!is_possible) { // if target unreachable, then just return IMPOSSIBLE
            cout << "IMPOSSIBLE" << endl;
        } else if (k == 0) { // if target is 0, then just return 0 (we start there)
            cout << 0 << endl;
        } else {
            map<node, map<node, int>> graph = build_graph(elevators_floors, T, n, k); 
            int min_seconds = dijkstra(graph, {0, -1}, {k, -1});

            if (min_seconds == 10000) {
                cout << "IMPOSSIBLE" << endl;
            } else {
                cout << min_seconds << endl;
            }
        }
        
    }
    return 0;
}