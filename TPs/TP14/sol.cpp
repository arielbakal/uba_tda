#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#include <string>

using namespace std;

bool bfs(vector<vector<int>>& residual_graph, int s, int t, vector<int>& parent, vector<bool>& visited, int graph_size) {
    fill(visited.begin(), visited.end(), false);
    queue<int> q;
    
    // start from source
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int w = 0; w < graph_size; ++w) {
            if (!visited[w] && residual_graph[v][w] > 0) {
                // if we reach sink just return true
                if (w == t) {
                    parent[w] = v;
                    return true;
                }
                // continue exploring
                q.push(w);
                parent[w] = v;
                visited[w] = true;
            }
        }
    }
    // we didn't reach sink
    return false;
}

int edmonds_karp(vector<vector<int>>& graph, int s, int t, int graph_size) {
    int v, w;
    vector<vector<int>> residual_graph = graph;
    vector<int> parent(graph_size);
    vector<bool> visited(graph_size);
    
    int max_flow = 0;
    
    // augment flow while path source to sink exists
    while (bfs(residual_graph, s, t, parent, visited, graph_size)) {
        // find min residual capacity edges along the path filled by BFS 
        // (find max flow through the path found)
        int path_flow = INT_MAX;
        for (w = t; w != s; w = parent[w]) {
            int v = parent[w];
            path_flow = min(path_flow, residual_graph[v][w]);
        }

        // update residual capacities and reverse edges along the path
        for (w = t; w != s; w = parent[w]) {
            int v = parent[w];
            residual_graph[v][w] -= path_flow;
            residual_graph[w][v] += path_flow;
        }

        max_flow += path_flow;
    }
    return max_flow;
}

vector<pair<char,int>> get_neighbors(vector<vector<pair<char, int>>> char_graph, int i, int j, int X, int Y) {
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<pair<char, int>> neighbors;

    for (const auto& dir : directions) {
        int ni = i + dir.first;
        int nj = j + dir.second;

        // Check if the neighbor is within grid bounds
        if (ni >= 0 && ni < X && nj >= 0 && nj < Y) {
            if (char_graph[ni][nj].first == '~') continue;
            neighbors.push_back(char_graph[ni][nj]);
        }
    }
    return neighbors;
}

int main() {
    int X, Y, P; 
    while(cin >> X >> Y >> P) {
        vector<vector<pair<char, int>>> char_graph(X, vector<pair<char, int>>(Y));
        int graph_size = (X*Y)+2;
        vector<vector<int>> flow_graph(graph_size, vector<int>(graph_size, 0));
        // graph: source -> 0 | chars -> 1 to X*Y | sink -> (X*Y)+1

        char character;
        int node_num = 0;
        for (int i=0; i<X; i++) {
            for (int j=0; j<Y; j++) {
                node_num += 1;
                cin >> character;
                char_graph[i][j] = {character, node_num};
            }
        }

        int sink_node = (X*Y)+1;

        pair<char, int> char_pair;
        vector<pair<char, int>> neighbors;
        for (int i=1; i<=X; i++) {
            for (int j=1; j<=Y; j++) {
                char_pair = char_graph[i-1][j-1]; // {char, node_num}

                if (char_pair.first == '~') continue; // got water

                // from source move to * with capacity 1
                // from * . @ move both ways with capacity 1. if neighbor is # move with capacity P (one-way)
                // from # move to sink with capacity P
                if (char_pair.first == '#') {
                    flow_graph[char_pair.second][sink_node] = P;
                    continue;
                } 
                neighbors = get_neighbors(char_graph, i-1, j-1, X, Y);
                if (char_pair.first == '@') {
                    flow_graph[0][char_pair.second] = 1;
                    for (auto neighbor : neighbors) {
                        if (neighbor.second == '#') {
                            flow_graph[char_pair.second][neighbor.second] = P;
                        } else {
                            flow_graph[char_pair.second][neighbor.second] = P;
                            flow_graph[neighbor.second][char_pair.second] = P;
                        }
                    }
                    continue;
                }
                if (char_pair.first == '*') {
                    flow_graph[0][char_pair.second] = 1;
                }
                for (auto neighbor : neighbors) {
                    if (neighbor.second == '#') {
                        flow_graph[char_pair.second][neighbor.second] = P;
                    } else {
                        flow_graph[char_pair.second][neighbor.second] = 1;
                        flow_graph[neighbor.second][char_pair.second] = 1;
                    }
                }
            }
        }
        char blank; cin >> blank;

        int result = edmonds_karp(flow_graph, 0, (X*Y)+1, graph_size);
        cout << result << endl;
    }
    return 0;
}