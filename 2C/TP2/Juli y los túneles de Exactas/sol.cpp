#include <iostream>
#include <vector>

using namespace std;

int main() {

    int n; cin >> n;

    vector<vector<int>> graph(n);

    for (int i=0; i<n; i++) {

        // build directed graph
        if (i==0) {
            graph[i].push_back(i+1);        
        } else if (i<n-1) {
            graph[i].push_back(i+1);
            graph[i].push_back(i-1);
        } else {
            graph[i].push_back(i-1);
        }

        // add shortcut edges
        int shortcut_to_class; cin >> shortcut_to_class;
        if (i!=shortcut_to_class-1 && i-1!=shortcut_to_class-1 && i+1!=shortcut_to_class-1) {
            graph[i].push_back(shortcut_to_class-1);    
        }
    }

    for (int i=0; i<n; i++) {

        cout << i << ": ";

        for (int v: graph[i]) {

            cout << v << " ";
        }

        cout << endl;
    }

    return 0;
}