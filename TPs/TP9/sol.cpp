#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

int main() {
    int T; cin >> T;
    vector<array<int, 4>> keys;

    for (int i=0; i<T; i++) {
        int N; cin >> N;
        keys.resize(N);

        for(int j=0; j<N; j++) {
            string key_str; cin >> key_str;
            for (int k = 0; k < 4; k++) {
                keys[j][k] = key_str[k] - '0';
            }
        }

        for(array<int, 4> key: keys) {
            for(int digit: key)
                cout << digit;
            cout << " ";
        }
        cout << endl;
    }

    return 0;
}