#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

// 1. Calculate distances between 0000 and all keys, then get min_dist (starting_cost) and starting_key.
// This will be our starting key for Prim. We cant start from 0000 or include it on the keys we pass to Prim bc we cant JUMP there.
// If we do it will generate an MST where 0000 could have multiples edges.
// 3. Implement Prim only summing costs (we dont need to save fathers and recreate MST) 
// and using dynamic programming for distances (we calculate same distances several times).


vector<string> keys;

int single_key_dist(int a, int b) {
    int distance = abs(a - b);
    return min(distance, 10 - distance);
}

int keys_dist(const string& key1, const string& key2) {
    int distance = 0;
    for (int i=0; i<4; i++) {
        distance += single_key_dist(key1[i] - '0', key2[i] - '0');
    }
    return distance;
}

pair<int, int> min_start_cost(const vector<string>& keys, int N) {
    int min_dist = 26;
    int min_key = -1;
    string init = "0000";
    for (int i=0; i<N; i++) {
        int dist = keys_dist(init, keys[i]);
        if (dist < min_dist) {
            min_key = i;
            min_dist = dist;
        }
    }
    return make_pair(min_dist, min_key);
}

int prim_min_cost(const vector<string>& keys, int starting_cost, int starting_key, int N) {
    vector<int> min_cost(N, 26);
    vector<bool> visited(N, false);
    int total_cost = starting_cost;
    min_cost[starting_key] = 0;

    for (int i=0; i<N; i++) {
        int min_key = -1;
        for (int j=0; j<N; j++) {
            if (!visited[j]) {
                if (min_key == -1 || min_cost[j] < min_cost[min_key]) {
                    min_key = j;
                }
            }
        }
        
        if (min_key == -1) break; 
        
        visited[min_key] = true;
        total_cost += min_cost[min_key];

        for (int k=0; k<N; k++) {
            if (!visited[k]) {
                int dist = keys_dist(keys[min_key], keys[k]);
                if (dist < min_cost[k]) {
                    min_cost[k] = dist;
                }
            }
        }
    }

    return total_cost;
}

int main() {
    int T;
    cin >> T;

    for (int k=0; k<T; k++) {
        int N; cin >> N;
        keys.resize(N);

        for (int i=0; i<N; i++) {
            cin >> keys[i];
        }

        pair<int, int> start = min_start_cost(keys, N);

        int min_cost = prim_min_cost(keys, start.first, start.second, N);

        cout << min_cost << endl;
    }

    return 0;
}
