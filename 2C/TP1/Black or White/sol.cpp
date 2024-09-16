#include <iostream>
#include <vector>
using namespace std;

// STATUS: Backtracking algo implemented
// TODO: test backtracking algorithm; impl both asc and desc algorithm and test it; do recursive topdown;

int bt(int i, vector<int> A, int l, const vector<int> X, const int N) {
    
    if (i==N) {
        return l;
    }
    if (A.size() == 0) {
        vector<int> added_A;
        added_A = A;
        added_A.push_back(X[i]); 
        return bt(i+1, added_A, l-1, X, N);
    }
    if (A[A.size()-1] >= X[i]){
        vector<int> empty_A;
        empty_A.push_back(X[i]);
        return min(bt(i+1, A, l, X, N), bt(i+1, empty_A, N-1, X, N));
    }   
    vector<int> added_A;
    added_A = A;
    added_A.push_back(X[i]);
    return min(bt(i+1, added_A, l-1, X, N), bt(i+1, A, l, X, N));
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
        
        vector<int> A;
        int res;
        
        res = bt(0, A, N, X, N);
        
        cout << res << endl;
    }
    
    return 0;
}