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

pair<int, int> min_start_cost(vector<string> keys, int N) {
    int min_dist = 26;
    int min_key;
    string init = "0000";
    for (int i=0; i<N; i++) {
        int dist = keys_dist(init, keys[i]);
        if (dist < min_dist) {
            min_key = i;
            min_dist = dist;
        }
    }
    return pair<int, int>({min_dist, min_key});
}

unordered_map<int, vector<pair<int, int>>> build_graph(vector<string> keys, int N) {
    unordered_map<int, vector<pair<int, int>>> adj_list;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i != j) {
                adj_list[i].push_back({j, keys_dist(keys[i], keys[j])});
            }
        }
    }
    return adj_list;
}

int prim_min_cost(unordered_map<int, vector<pair<int, int>>> graph, int starting_cost, int starting_key, int N) {
    int total_cost = starting_cost;
    vector<bool> visited(N, false);
    visited[starting_key] = true;

    for (int k=0; k<N; k++) {
        int min_dist = 26;
        int min_key = -1;
        for (int i=0; i<N; i++) {
            if (!(visited[i])) { 
                vector<pair<int, int>> neighbors = graph[i];
                for (pair<int, int> neighbor: neighbors) {
                    if (visited[neighbor.first]) { 
                        if (neighbor.second < min_dist) {
                            min_dist = neighbor.second;
                            min_key = i;
                        }
                    }
                }
            }
        }
        if (min_key == -1) {
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
        
        unordered_map<int, vector<pair<int, int>>> graph = build_graph(keys, N);

        pair<int, int> start = min_start_cost(keys, N);

        int min_cost = prim_min_cost(graph, start.first, start.second, N);
        
        cout << min_cost << endl;
    }

    return 0;
}