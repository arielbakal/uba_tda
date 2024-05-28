#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cstdlib>
#include <unordered_map>
using namespace std;

typedef array<int, 4> Key; 

vector<Key> keys;

int single_key_dist(int a, int b) {
    int distance = abs(a-b);
    if (distance < 10-distance) {
        return distance;
    } 
    return 10-distance;
}

int keys_dist(Key key1, Key key2) {
    int distance = 0;
    for (int i=0; i<4; i++) {
        distance += single_key_dist(key1[i], key2[i]);
    }
    return distance;
}

unordered_map<int, vector<pair<int, int>>> build_graph(vector<Key> keys, int N) {
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

int main() {
    int T; cin >> T;

    for (int i=0; i<T; i++) {
        int N; cin >> N;
        keys.resize(N);

        for(int j=0; j<N; j++) {
            string key_str; cin >> key_str;
            for (int k = 0; k < 4; k++) {
                keys[j][k] = key_str[k] - '0';
            }
        }
        
        Key init;
        for (int k = 0; k < 4; k++) {
            init[k] = 0;
        }
        
        unordered_map<int, vector<pair<int, int>>> graph = build_graph(keys, N);
        
        for (const auto& par : graph) {
            int clave = par.first;
            const vector<pair<int, int>>& valores = par.second;
    
            cout << "Clave: " << clave << ", Valores: ";
            for (const auto& valor : valores) {
                cout << "(" << valor.first << ", " << valor.second << ") ";
            }
            cout << endl;
        }
        
        
    }

    return 0;
}