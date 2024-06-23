#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Multiply all "gt" subsequeces values by -1, this will invert the constraint to get all the same ("lt")
// Sum all subsequences, if i get [0,...,0] then verify 0<sum(k_i) (k_i after invertion) then thats our answer.
// if i get any (no null) combination like [a1, 0, a2, ....] then a subsequence exists.


int main() {
    int N, M;
    vector<int> s, n, o, k; // gt = 1, lt = 0
    string line;
    
    while (cin >> N) {
        if (N == 0) break;
        cin >> M;
        
        cin.ignore();
        
        s.resize(M); n.resize(M); o.resize(M); k.resize(M); 
        
        for (int i=0; i<M; i++) {
            getline(cin, line); istringstream iss(line);
            string op;
            iss >> s[i] >> n[i] >> op >> k[i];
            if (op == "gt") o[i] = 1; else o[i] = 0;
        }

        vector<int> subseq_list(N, 0);
        int constraint_sum = 0;

        for (int i=0; i<M; i++) {
            vector<int> subseq_list_temp(N);
            for (int j=s[i]; j<s[i]+n[i]; j++) {
                if (o[i] == 1) {
                    subseq_list[i] = subseq_list[i] - j;
                } else {
                    subseq_list[i] = subseq_list[i] + j;
                }
            }
            if (o[i] == 1) constraint_sum -= k[i]; else constraint_sum += k[i];
        }

        bool result = false;

        
        for (int i=0; i<N; i++) {
            if (subseq_list[i] != 0) {
                result = true;
                break;
            }
        }
        
        if (result) {
            cout << "lamentable kingdom";
        } else {
            if (0<constraint_sum) cout << "lamentable kingdom"; else cout << "successful conspiracy";
        }
        cout << endl;

    }
    return 0;
}
