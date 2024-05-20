#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> adj_list;
vector<bool> visited;

// DFS recursivo
void dfs_recursive(int u) {
    cout << u << " ";
    visited[u] = true;

    for (int v : adj_list[u]) {
        if (!visited[v]) {
            dfs_recursive(v);
        }
    }
}

// DFS iterativo
void dfs(int u) {
    stack<int> s;

    s.push(u); 
    visited[u] = true;

    while (!s.empty()) {
        int f = s.top(); 
        s.pop();

        cout << f << " ";

        // Push all unvisited adjacent of f onto the stack
        for (auto i = adj_list[f].rbegin(); i != adj_list[f].rend(); ++i) { // Recorremos en reversa
            if (!visited[*i]) {
                s.push(*i);
                visited[*i] = true;
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    adj_list.assign(n, vector<int>());
    visited.assign(n, false);

    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u); 
    }

    cout << "DFS recursivo: ";
    for (int i = 0; i < n; i++) {
        if (!visited[i])
            dfs_recursive(i);
    }
    cout << endl;

    // Reiniciamos 'visited' para el DFS iterativo
    visited.assign(n, false);

    cout << "DFS iterativo: ";
    for (int i = 0; i < n; i++) {
        if (!visited[i])
            dfs(i);
    }
    cout << endl;

    return 0;
}
