#include <iostream>
#include <string>
#include <vector>

using namespace std;

int size_index(string size) {
    if (size == "XXL") return 0;
    if (size == "XL") return 1;
    if (size == "L") return 2;
    if (size == "M") return 3;
    if (size == "S") return 4;
    if (size == "XS") return 5;
    return -1;
}

int main() {

    int T; cin >> T;
    for (int t=0; t<T; t++) {

        int N, M; cin >> N >> M;
        vector<int> suiting_tshirts(6); // XXL=0, XL=1, ... , XS=5
        vector<vector<pair<int,int>>> graph(8); 

        for (int m=0; m<M; m++) {

            string size1, size2; cin >> size1 >> size2;
            
            suiting_tshirts[size_index(size1)] += 1;
            suiting_tshirts[size_index(size2)] += 1;
        }
        
        // build flow graph
        for (int i=1; i<7; i++) { // reindex sizes i->i+1 to let i=0 to node s
            // node s = 0th, node t = 7th
            graph[0].push_back({i, N/6}); // node s to all sizes
            graph[i].push_back({7, suiting_tshirts[i-1]}); // node size to node t
        }
    }
    return 0;
}