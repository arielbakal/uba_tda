#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <unordered_map>
using namespace std;

vector<string> keys;

int single_key_dist(int a, int b) {
    int distance = abs(a-b);
    if (distance < 10-distance) {
        return distance;
    } 
    return 10-distance;
}

int keys_dist(string key1, string key2) {
    int distance = 0;
    for (int i=0; i<4; i++) {
        int a = key1[i] - '0';
        int b = key2[i] - '0';
        distance += single_key_dist(a, b);
    }
    return distance;
}

pair<int, string> min_start_cost(vector<string> keys, int N) {
    int min_dist = 26;
    string min_key;
    string init = "0000";
    for (string key: keys) {
        int dist = keys_dist(init, key);
        if (dist < min_dist) {
            min_key = key;
            min_dist = dist;
        }
    }
    return pair<int, string>({min_dist, min_key});
}

unordered_map<string, vector<pair<string, int>>> build_graph(vector<string> keys, int N) {
    unordered_map<string, vector<pair<string, int>>> adj_list;
    for (const auto& key1: keys) {
        for (const auto& key2: keys) {
            if (key1 != key2) {
                adj_list[key1].push_back({key2, keys_dist(key1, key2)});
            }
        }
    }
    return adj_list;
}

int prim_min_cost(unordered_map<string, vector<pair<string, int>>> graph, int starting_cost, string starting_key, int N) {
    int total_cost = starting_cost;
    unordered_map<string, bool> visited;
    visited[starting_key] = true;

    for (int i=0; i<N; i++) {
        int min_dist = 26;
        string min_key = "-1";
        for (const auto& node: graph) {
            string key = node.first;
            if (!(visited[key])) { 
                vector<pair<string, int>> neighbors = graph[key];
                for (pair<string, int> neighbor: neighbors) {
                    if (visited[neighbor.first]) { 
                        if (neighbor.second < min_dist) {
                            min_dist = neighbor.second;
                            min_key = key;
                        }
                    }
                }
            }
        }
        if (min_key == "-1") {
            return total_cost;
        }
        visited[min_key] = true;
        total_cost += min_dist;
    }

    return total_cost;
}

int main() {
    int T; cin >> T;

    for (int i=0; i<T; i++) {
        int N; cin >> N;
        keys.resize(N);

        for (int i = 0; i<N; i++) {
            cin >> keys[i]; 
        }   
        
        unordered_map<string, vector<pair<string, int>>> graph = build_graph(keys, N);

        pair<int, string> start = min_start_cost(keys, N);

        int min_cost = prim_min_cost(graph, start.first, start.second, N);
        
        cout << min_cost << endl;
    }

    return 0;
}