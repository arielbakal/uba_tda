#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// STATUS: Backtracking algo implemented
// TODO: impl both asc and desc algorithm and test it; do recursive topdown;

int bt_incr(int i, int last_elem, const vector<int>& X) {
    
    if (i==X.size()) {
        return 0;
    }
    if (last_elem >= X[i]){ // Si NO es increasing, continuo
        return bt_incr(i+1, last_elem, X);
    }   
    // Si es increasing, busco el maximo entre actualizar last_elem y continuar explorando
    return max(bt_incr(i+1, X[i], X) + 1, bt_incr(i+1, last_elem, X)); 
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
        
        res_incr = bt_incr(0, INT_MIN, X);
        
        cout << res_incr << endl;
    }
    
    return 0;
}