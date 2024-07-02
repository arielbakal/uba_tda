#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int X, Y, P; 
    while(cin >> X >> Y >> P) {
        vector<vector<char>> char_graph(X, vector<char>(Y));
        vector<vector<int>> flow_graph;
        
        for (int i=0; i<X; i++) {
            for (int j=0; j<Y; j++) {
                cin >> char_graph[i][j];
            }
        }
    }
    return 0;
}