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

vector<pair<int, int>> get_neighbors(vector<vector<pair<char, int>>> char_graph, int i, int j, int X, int Y) {
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<pair<int, int>> neighbors;

    for (const auto& dir : directions) {
        int ni = i + dir.first;
        int nj = j + dir.second;

        // Check if the neighbor is within grid bounds
        if (ni >= 0 && ni < X && nj >= 0 && nj < Y) {
            if (char_graph[ni][nj].first == '~') continue;
            neighbors.push_back({ni, nj});
        }
    }
    return neighbors;
}

int main() {
    int X, Y, P; 
    while(cin >> X >> Y >> P) {
        vector<vector<pair<char, int>>> char_graph(X, vector<pair<char, int>>(Y));
        int graph_size = (X * Y * 2) + 2;
        vector<vector<int>> flow_graph(graph_size, vector<int>(graph_size, 0));
        // graph: source -> 0 | chars -> 1 to X*Y | sink -> (X*Y*2)+1
        // @ nodes will be divided in two states in and out to ensure only 1 person can pass through icebergs at time
        // out @ nodes -> (X*Y + 1, ... , X*Y + X*Y)

        char character;
        int node_num = 1; // start from 1 because 0 is the source
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                cin >> character;
                char_graph[i][j] = {character, node_num++};
            }
        }

        int sink_node = (X * Y * 2) + 1;
        int out_node_offset = X * Y; // starting point for out nodes of icebergs

        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                auto [char_type, node_num] = char_graph[i][j];
                if (char_type == '~') continue; // skip water cells

                // source to all * with capacity 1
                if (char_type == '*') {
                    flow_graph[0][node_num] = 1;
                }

                // all # to sink with capacity P 
                if (char_type == '#') {
                    flow_graph[node_num][sink_node] = P;
                }

                // get neighbors and connect nodes accordingly
                for (auto [ni, nj] : get_neighbors(char_graph, i, j, X, Y)) {
                    auto [neighbor_char, neighbor_num] = char_graph[ni][nj];
                    
                    if (char_type == '@') {
                        int out_node_num = node_num + out_node_offset;
                        flow_graph[node_num][out_node_num] = 1; // internal edge with capacity 1
                        if (neighbor_char != '~') {
                            flow_graph[out_node_num][neighbor_num] = INT_MAX; // connect out node to neighbors with capacity INT_MAX
                        }
                    } else if (neighbor_char == '@') {
                        int neighbor_out_node = neighbor_num + out_node_offset;
                        flow_graph[node_num][neighbor_num] = 1; // connect node to neighbor's in node
                        flow_graph[neighbor_num][neighbor_out_node] = 1; // neighbor's in to out node
                    } else if (char_type == '#') {
                        flow_graph[node_num][neighbor_num] = INT_MAX; // connect from # to neighbors with capacity INT_MAX
                    } else {
                        flow_graph[node_num][neighbor_num] = 1;
                    }
                }
            }
        }

        int result = edmonds_karp(flow_graph, 0, sink_node, graph_size);
        cout << result << endl;
    }
    return 0;
}
