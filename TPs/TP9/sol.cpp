#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cstdlib>

using namespace std;

vector<array<int, 4>> keys;

int single_key_dist(int a, int b) {
    int distance = abs(a-b);
    if (distance < 10-distance) {
        return distance;
    } 
    return 10-distance;
}

int keys_dist(array<int, 4> key1, array<int, 4> key2) {
    int distance = 0;
    for (int i=0; i<4; i++) {
        distance += single_key_dist(key1[i], key2[i]);
    }
    return distance;
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
        
        array<int, 4> init;
        for (int k = 0; k < 4; k++) {
            init[k] = 0;
        }
        
        for(array<int, 4> key: keys) {
            cout << keys_dist(init, key) << " ";
        }
        cout << endl;
    }

    return 0;
}