#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// STATUS: topdown impl
// TODO: No funciona para este input
// 9
// 1 3 2 3 4 4 5 6 7
// -1

int bt_incr(int i, int last_index, const int N, const vector<int>& X, vector<vector<int>>& M_incr) {
    
    if (i == N) {
        return 0;
    }

    if (M_incr[i][last_index] == -1) {
        // Si es increasing o index == 0, busco el maximo entre actualizar last_index y continuar explorando.
        if (last_index == 0 || X[last_index - 1] < X[i]) { 
            M_incr[i][last_index] = max(bt_incr(i + 1, i + 1, N, X, M_incr) + 1, bt_incr(i + 1, last_index, N, X, M_incr));

        } else { // Si no, continuo
            M_incr[i][last_index] = bt_incr(i + 1, last_index, N, X, M_incr);
        }
    }
    return M_incr[i][last_index];
}

int bt_decr(int i, int last_index, const int N, const vector<int>& X, vector<vector<int>>& M_decr) {
    
    if (i == N) {
        return 0;
    }

    if (M_decr[i][last_index] == -1) {
        // Si es decreasing o index == 0, busco el maximo entre actualizar last_index y continuar explorando
        if (last_index == 0 || X[last_index - 1] > X[i]) { 
            M_decr[i][last_index] = max(bt_decr(i + 1, i + 1, N, X, M_decr) + 1, bt_decr(i + 1, last_index, N, X, M_decr));

        } else { // Si no, continuo
            M_decr[i][last_index] = bt_decr(i + 1, last_index, N, X, M_decr);
        }
    }
    return M_decr[i][last_index];
}

int main() {
    while (true) {
        int N; cin >> N;
        if (N == -1) break;
        vector<int> X(N);
        for (int i = 0; i < N; i++) {
            cin >> X[i];
        }

        int res_incr;
        int res_decr;

        vector<vector<int>> M_incr(N, vector<int>(N + 1, -1));
        vector<vector<int>> M_decr(N, vector<int>(N + 1, -1));

        res_incr = bt_incr(0, 0, N, X, M_incr); 
        res_decr = bt_decr(0, 0, N, X, M_decr);  

        if ((N - res_incr - res_decr) <= 0) {
            cout << 0 << endl;
        } else {
            cout << N - res_incr - res_decr << endl;
        }
    }

    return 0;
}
