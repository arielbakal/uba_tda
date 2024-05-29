#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <array>
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
    int min_dist = 100000;
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
    vector<string> visited;
    visited.push_back(starting_key);

    for (int i=0; i<N; i++) {
        int min_dist = 1000000;
        string min_key = "";
        for (const auto& node: graph) {
            string key = node.first;
            if (find(visited.begin(), visited.end(), key) != visited.end()) { 
                for (const auto& neighbor: graph[key]) {
                    if (find(visited.begin(), visited.end(), neighbor.first) == visited.end()) { 
                        if (neighbor.second < min_dist) {
                            min_dist = neighbor.second;
                            min_key = key;
                        }
                    }
                }
            }
        }
        if (min_key == "") {
            return total_cost;
        }
        visited.push_back(min_key);
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