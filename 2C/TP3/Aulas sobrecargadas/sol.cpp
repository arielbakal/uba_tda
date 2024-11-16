#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m; cin >> n >> m;

    int a_sum = 0;
    vector<int> a(n);
    vector<int> b(n);

    // classrooms = A
    // s = 0 | 1° classrooms' state = 1...n | 2° classrooms' state = n+1...2n | t = 2n+1
    vector<vector<pair<int, int>>> graph((2*n) + 2);

    for (int i=0; i<n; i++) {
        int sub_a; cin >> sub_a;
        a_sum += sub_a;
        a[i] = sub_a;
        graph[0].emplace_back(i+1, sub_a); // s -> Ai with cost ai
    }
    for (int i=0; i<n; i++) {
        int sub_b; cin >> sub_b;
        b[i] = sub_b;
        graph[i+1].emplace_back(n+(i+1), sub_b); // Ai -> Ai with cost bi
        graph[n+(i+1)].emplace_back(2*n+1, sub_b); // Ai -> t with cost bi
    }

    for (int i=0; i<m; i++) {
        int p, q; cin >> p >> q;
        graph[p].emplace_back(q+n, b[p-1]); // Ap -> Aq with cost bp 
    }

    // int max_flow = flowfunction();

    // if (a_sum == max_flow) {
    //     cout << "YES" << endl;
    // } else {
    //     cout << "NO" << endl;
    // }

    for (int i = 0; i < graph.size(); ++i) {
        cout << "Node " << i << ":";
        for (const auto& edge : graph[i]) {
            cout << " (" << edge.first << ", " << edge.second << ")";
        }
        cout << endl;
    }

    return 0;
}