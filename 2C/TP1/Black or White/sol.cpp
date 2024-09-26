#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

// STATUS: bt impl
// TODO: funciona para todos los tests que conozco

int bt_incr_decr(int i, int black, int white, const vector<int>& X, const int N) {
    
    if (i==N) {
        return 0;
    }
    
    int include_black = INT_MIN;
    int include_white = INT_MIN;
    
    if (black == -1 || X[black] < X[i]) {
        include_black = bt_incr_decr(i+1, i, white, X, N) + 1;
    }
    
    if (white == -1 || X[white] > X[i]) {
        include_white = bt_incr_decr(i+1, black, i, X, N) + 1;
    } 
    int exclude = bt_incr_decr(i+1, black, white, X, N);
    
    return max(max(include_black, include_white), exclude);
}

int main() {
    while (true) {
        int N; cin >> N;
        if (N == -1) break;
        vector<int> X(N);
        for (int i = 0; i < N; i++) {
            cin >> X[i];
        } 

        int res = bt_incr_decr(0, -1, -1, X, N);
        
        cout << N - res << endl;
    }

    return 0;
}
