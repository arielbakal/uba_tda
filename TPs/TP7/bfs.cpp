#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj_list;
vector<bool> visited;

void bfs(int u) {
    queue<int> q;

    q.push(u);
    visited[u] = true;

    while (!q.empty()) {

        int f = q.front();
        q.pop();

        cout << f << " ";

        // Enqueue all adjacent of f and mark them visited
        for (auto i = adj_list[f].begin(); i != adj_list[f].end(); i++) {
            if (!visited[*i]) {
                q.push(*i);
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
    for (int i = 0; i < m i++) {
        cin >> u >> v;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            bfs(i);
    }

    return 0;
}
