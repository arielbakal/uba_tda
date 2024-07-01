#include <iostream>
#include <string>
#include <vector>
using namespace std;

// TODO: Impl Edmonds-Karp algorithm

int size_index(string size) {
    if (size == "XXL") return 1;
    if (size == "XL") return 2;
    if (size == "L") return 3;
    if (size == "M") return 4;
    if (size == "S") return 5;
    if (size == "XS") return 6;
    return -1;
}

int main() {

    int T; cin >> T;
    for (int t=0; t<T; t++) {

        int N, M; cin >> N >> M;
        vector<vector<pair<int,int>>> graph(M+9); 
        // graph: 
        // source->0, 
        // XXL -> 1, XL -> 2, ... , XS -> 6
        // volunteer_1 -> 7, volunteer_2 -> 1+7, ... , volunteer_M -> M+7
        // sink->M+8

        for (int i=1; i<7; i++) {
            graph[0].push_back({i, N/6}); // node s to all sizes
        }

        int sink_node = M+8;
        for (int m=0; m<M; m++) {
            string size1, size2; cin >> size1 >> size2;
            int volunteer_index = m+7;
            
            // direct two sizes that fits volunteer 
            graph[size_index(size1)].push_back({volunteer_index, 1});
            graph[size_index(size2)].push_back({volunteer_index, 1});

            // direct volunteer to sink (each volunteer receives 1 t-shirt at most)
            graph[volunteer_index].push_back({sink_node, 1});
        }
    }
    return 0;
}