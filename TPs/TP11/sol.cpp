#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// 1. Convert subsequences sum contraints system to difference constraints system
// 2. Model constraint graph
// 3. Implement Bellman-Ford, if ends: then sequence exists, else: found a negative-weight cycle then sequence DONT exists 

// Multiply all "gt" subsequeces values by -1, this will invert the constraint to get all the same ("lt")
// Sum all subsequences, if i get [0,...,0] then verify 0<sum(k_i) (k_i after invertion) then thats our answer. 


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
    }
    return 0;
}
