#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// REDO: this doesnt work, i need to model a map and solve with bellman-ford.
// maybe k[i] could be the weight from s[i]-1 to s[i] + n[i] and weight k-1 or -k+1 depending of lt/gt because it works with gt/lt and equal!!


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
            if (o[i] == 1) constraint_sum -= k[i]; else constraint_sum += k[i];
            
            for (int j=s[i]; j<s[i]+n[i]; j++) {
                if (o[i] == 1) {
                    subseq_list[j] = subseq_list[j] - j;
                } else {
                    subseq_list[j] = subseq_list[j] + j;
                }
            }
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
