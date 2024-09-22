#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// STATUS: topdown impl
// TODO: 

int bt_incr(int i, int last_elem, const vector<int>& X, vector<vector<int>>& M_incr) {
    
    if (i==X.size()) {
        return 0;
    }

    if (M_incr[i][last_elem] == -1) {
        if (last_elem >= X[i]){ // Si NO es increasing, continuo
            M_incr[i][last_elem] = bt_incr(i+1, last_elem, X, M_incr);

        } else { // Si es increasing, busco el maximo entre actualizar last_elem y continuar explorando
            M_incr[i][last_elem] = max(bt_incr(i+1, X[i], X, M_incr) + 1, bt_incr(i+1, last_elem, X, M_incr));
        }
    }
    return M_incr[i][last_elem];
}

int bt_decr(int i, int last_elem, const vector<int>& X, vector<vector<int>>& M_decr) {

    if (i==X.size()) {
        return 0;
    }

    if (M_decr[i][last_elem] == -1) {
        if (last_elem <= X[i]){ // Si NO es decreasing, continuo
            M_decr[i][last_elem] = bt_decr(i+1, last_elem, X, M_decr);

        } else { // Si es decreasing, busco el maximo entre actualizar last_elem y continuar explorando
            M_decr[i][last_elem] = max(bt_decr(i+1, X[i], X, M_decr) + 1, bt_decr(i+1, last_elem, X, M_decr));
        }
    }
    return M_decr[i][last_elem];
}

int main()
{
    int N;
    while (cin >> N) {
        if (N == -1) break;
        vector<int> X(N);
        for (int i=0; i<N; i++) {
            cin >> X[i];
        }
        
        int res_incr;
        int res_decr;
        int max_elem; max_elem = *max_element(X.begin(), X.end());

        vector<vector<int>> M_incr(N + 1, vector<int>(max_elem + 2, -1));
        vector<vector<int>> M_decr(N + 1, vector<int>(max_elem + 2, -1));
        
        res_incr = bt_incr(0, 0, X, M_incr);
        res_decr = bt_decr(0, max_elem + 1, X, M_decr);
        
        if ((N - res_incr - res_decr) <= 0) {
            cout << 0 << endl;
        } else {
            cout << N - res_incr - res_decr << endl;
        }
    }
    
    return 0;
}