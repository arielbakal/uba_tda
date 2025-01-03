#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

int INF = numeric_limits<int>::max();

int bfs(int s, int t, vector<int>& parent, vector<vector<int>>& adj, vector<vector<int>>& capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int edmonds_karp(int s, int t, vector<vector<int>>& adj, vector<vector<int>>& capacity) {
    int flow = 0;
    vector<int> parent(adj.size());
    int new_flow;

    while (new_flow = bfs(s, t, parent, adj, capacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int main() {
    int n, m; cin >> n >> m;

    int b_sum = 0;
    int a_sum = 0;
    vector<int> a(n);
    vector<int> b(n);

    // classrooms = A
    // s = 0 | 1° classrooms' state = 1...n | 2° classrooms' state = n+1...2n | t = 2n+1
    vector<vector<int>> graph((2*n) + 2);
    vector<vector<int>> capacity((2*n) + 2, vector<int>((2*n) + 2));

    int s = 0;
    int t = 2*n+1;

    for (int i=0; i<n; i++) {
        int sub_a; cin >> sub_a;
        a[i] = sub_a;
        a_sum += sub_a;
        // s -> Ai with cost ai
        graph[s].push_back(i+1);
        graph[i+1].push_back(s);
        capacity[s][i+1] = sub_a; 
        capacity[i+1][s] = 0; 
    }
    for (int i=0; i<n; i++) {
        int sub_b; cin >> sub_b;
        b[i] = sub_b;
        b_sum += sub_b;
        // Ai -> Ai with cost ai
        graph[i+1].push_back(n+(i+1));
        graph[n+(i+1)].push_back(i+1);
        capacity[i+1][n+(i+1)] = a[i]; 
        capacity[n+(i+1)][i+1] = 0; 
        // Ai -> t with cost bi
        graph[n+(i+1)].push_back(t);
        graph[t].push_back(n+(i+1));
        capacity[n+(i+1)][t] = sub_b; 
        capacity[t][n+(i+1)] = 0; 
    }

    for (int i=0; i<m; i++) {
        int p, q; cin >> p >> q;
        // Ap -> Aq with cost ap 
        graph[p].push_back(q+n);
        graph[q+n].push_back(p);
        capacity[p][q+n] = a[p-1]; 
        capacity[q+n][p] = 0; 
        // Aq -> Ap with cost aq 
        graph[q].push_back(p+n);
        graph[p+n].push_back(q);
        capacity[q][p+n] = a[q-1]; 
        capacity[p+n][q] = 0; 
    }

    if (a_sum <= b_sum) {
        int max_flow = edmonds_karp(s, t, graph, capacity);
        if (max_flow == b_sum) {
            cout << "YES" << endl;
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                    cout << capacity[n+j+1][i+1] << " ";
                }   
                cout << endl;
            }
        } else {
            cout << "NO";
        }
    } else {
        cout << "NO";
    }
    

    return 0;
}