#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

// STATUS: topdown impl
// TODO: funciona para todos los tests que conozco

int topdown_incr_decr(int i, int black, int white, vector<vector<vector<int>>>& Memo, const vector<int>& X, const int N) {
    
    if (i==N) {
        return 0;
    }
    
    if (Memo[i][black][white] != -1) {
        return Memo[i][black][white]; 
    }
    
    int include_black = INT_MIN;
    int include_white = INT_MIN;
    
    if (black == N || X[black] < X[i]) {
        include_black = topdown_incr_decr(i+1, i, white, Memo, X, N) + 1;
    }
    
    if (white == N || X[white] > X[i]) {
        include_white = topdown_incr_decr(i+1, black, i, Memo, X, N) + 1;
    } 
    int exclude = topdown_incr_decr(i+1, black, white, Memo, X, N);
    
    Memo[i][black][white] = max(max(include_black, include_white), exclude);
    
    return Memo[i][black][white];
}

int main() {
    while (true) {
        int N; cin >> N;
        if (N == -1) break;
        vector<int> X(N);
        for (int i = 0; i < N; i++) {
            cin >> X[i];
        }
        
        vector<vector<vector<int>>> Memo(N, vector<vector<int>>(N+1, vector<int>(N+1, -1)));

        int res = topdown_incr_decr(0, N, N, Memo, X, N);
        
        cout << N - res << endl;
    }

    return 0;
}
