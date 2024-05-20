#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// NOTES: 
// Solve with BFS

pair<int, vector<string>> find_shortest_path(int r, int current_room, int steps, 
                       vector<vector<int>>& doors, vector<bool>& visited, vector<vector<int>>& switches, vector<int>& lights_on, vector<string>& track) {
    if (current_room == r - 1) {
        pair<int, vector<string>> solution;
        solution.first = steps;
        solution.second = track;
        return solution;
    }

    visited[current_room] = true;

    for (int current_room_neighbor : doors[current_room]) { // iterate over neighbor rooms
        if (!visited[current_room_neighbor]) { // avoid visiting rooms i've already visited
            if (lights_on[current_room_neighbor] == 1) { // check if lights are on in neighbor room then,
                for (int switches_other_neighbor : switches[current_room_neighbor]) { // iterate over other neighbor rooms the room's neighbor can switch (messy)
                    if (current_room == switches_other_neighbor) { 
                        // switch off light, move and explore 
                        vector<int> temp_lights_on = lights_on;
                        temp_lights_on[current_room] = 0;
                        vector<string> temp_track = track;
                        temp_track.push_back("Move to room " + to_string(current_room_neighbor + 1));
                        temp_track.push_back("Switch off light in room " + to_string(current_room + 1));
                        pair<int, vector<string>> solution = find_shortest_path(r, current_room_neighbor, steps + 2, doors, visited, switches, temp_lights_on, temp_track);
                        if (solution.first != -1) return solution;
                    }
                }
                // dont switch off light, move and explore
                vector<string> temp_track = track;
                temp_track.push_back("Move to room " + to_string(current_room_neighbor + 1));
                pair<int, vector<string>> solution = find_shortest_path(r, current_room_neighbor, steps + 1, doors, visited, switches, lights_on, temp_track);
                if (solution.first != -1) return solution;
            } else {
                // if i didnt move rooms, then maybe is time for switching on some lights
                for (int switches_neighbor : switches[current_room]) { // iterate over rooms i can switch on
                    if (lights_on[switches_neighbor] == 0) {
                        // switch light and explore
                        vector<int> temp_lights_on = lights_on;
                        temp_lights_on[switches_neighbor] = 1; // switch lights on 
                        vector<string> temp_track = track;
                        temp_track.push_back("Switch on light in room " + to_string(switches_neighbor + 1));
                        pair<int, vector<string>> solution = find_shortest_path(r, current_room, steps + 1, doors, visited, switches, temp_lights_on, temp_track); // only switches room on
                        if (solution.first != -1) return solution;
                    }
                }
                // dont switch light and explore
                vector<string> temp_track = track;
                temp_track.push_back("Move to room " + to_string(current_room_neighbor + 1));
                pair<int, vector<string>> solution = find_shortest_path(r, current_room_neighbor, steps, doors, visited, switches, lights_on, temp_track);
                if (solution.first != -1) return solution;
                // with this i can explore all combination of which lights i switch on in my switches_neighbor
            }
        }
    }
    
    pair<int, vector<string>> no_solution;
    no_solution.first = -1;
    no_solution.second = track;
    return no_solution; // -1 indicates there's no solution
}

int main() {
    int r, d, s;
    int case_num = 0;

    while (true) {
        cin >> r >> d >> s;

        if (r == 0 && d == 0 && s == 0) break;

        case_num++;
        cout << "Villa #" << case_num << endl;
        
        // represent graphs as adjacents lists
        vector<vector<int>> doors_graph(r); // O(r) allocate r cells in memo
        vector<vector<int>> switches_graph(r); // O(r)
        vector<int> lights_on(r, 0); // tracking rooms' lights 
        lights_on[0] = 1;
        vector<bool> visited(r, false); // tracking visited rooms
        visited[0] = true;
        vector<string> track;

        for (int t = 0; t < d; t++) { // builds door_graph. Iterating over all edges O(d) 
            int i, j;
            cin >> i >> j;
            // door connects both i, j rooms
            doors_graph[i - 1].push_back(j - 1); // O(1) since i already allocated memory
            doors_graph[j - 1].push_back(i - 1); 
        }

        for (int t = 0; t < s; t++) { // builds lights_graph. Iterating over all switches O(s)
            int k, l;
            cin >> k >> l;
            // room k switches room l
            switches_graph[k - 1].push_back(l - 1);
        }

        pair<int, vector<string>> sol = find_shortest_path(r, 0, 0, doors_graph, visited, switches_graph, lights_on, track);

        if (sol.first == -1) {
            cout << "The problem cannot be solved." << endl;
        } else {
            for (string move: sol.second) {
                cout << move << endl;
            }
        }
    }

    return 0;
}
