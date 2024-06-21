#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

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
