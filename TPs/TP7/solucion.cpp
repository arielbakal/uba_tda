#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// NOTES: 
// TODO: BT bad handled. I track visited but still never ending
// Currently doing backtracking with graphs (?), but looks good. If not, implement Dijkstra then A*. 

vector<int> find_shortest_path(int r, int current_room, int steps, vector<vector<int>>& doors, vector<int> visited, vector<vector<int>>& switches, vector<int> lights_on) {

    if (current_room == r-1 || visited.size() == r) { // Case base: got to the room
        return lights_on;
    };

    for (int current_room_neighbor : doors[current_room]) { // iterate over neighbor rooms

        if (current_room_neighbor != current_room) { // avoid visiting the same room im in

            if (not (find(begin(visited), end(visited), current_room_neighbor) != end(visited))) { // check i've already visited that room. If not then,

                if (lights_on[current_room_neighbor] == 1) { // check if lights are on in neighbor room then,

                    for (int switches_other_neighbor : switches[current_room_neighbor]) { // iterate over other neighbor rooms the room's neighbor can switch (messy)
                        if (current_room == switches_other_neighbor) {
                            // switch off light, move and explore 
                            vector<int> temp_lights_on = lights_on;
                            temp_lights_on[current_room] = 0;
                            vector<int> temp_visited = visited;
                            temp_visited.push_back(current_room_neighbor);
                            find_shortest_path(r, current_room_neighbor, steps + 2, doors, temp_visited, switches, temp_lights_on);  
                        }
                    }
                    // dont switch off light, move and explore
                    vector<int> temp_visited = visited;
                    temp_visited.push_back(current_room_neighbor);
                    find_shortest_path(r, current_room_neighbor, steps + 1, doors, temp_visited, switches, lights_on);  
                } else {

                    // if i didnt move rooms, then maybe is time for switching on some lights
                    for (int switches_neighbor : switches[current_room]) { // iterate over rooms i can switch on

                        if (lights_on[switches_neighbor] == 0) {

                            // switch light and explore
                            vector<int> temp_lights_on = lights_on;
                            temp_lights_on[switches_neighbor] = 1; // switch lights on 
                            find_shortest_path(r, current_room, steps + 1, doors, visited, switches, temp_lights_on); // only switches room on
                        }

                        // dont switch light and explore
                        find_shortest_path(r, current_room, steps, doors, visited, switches, lights_on);
                        // with this i can explore all combination of which lights i switch on in my switches_neighbor
                    }
                }
            }
        }
    }

    return lights_on;
}

int main() {
    int r, d, s;
    int case_num;

    while (true) {
        cin >> r >> d >> s;

        if (r == 0 && d == 0 && s == 0) break;

        case_num++;
        cout << "Villa #" << case_num << endl;

        // represent graphs as adjacents lists
        vector<vector<int>> doors_graph(r); // O(r) allocate r cells in memo
        vector<vector<int>> switches_graph(r); // O(r) 

        // tracking rooms' lights 
        vector<int> lights_on(r);

        for (int t=0; t<d; t++) { // builds door_graph. Iterating over all edges O(d) 
            int i, j; cin >> i >> j;
            // door connects both i, j rooms
            doors_graph[i-1].push_back(j-1); // O(1) since i already allocated memory
            doors_graph[j-1].push_back(i-1); // O(1)
        } 

        for (int t=0; t<s; t++) { // builds lights_graph. Iterating over all switches O(s)
            int k, l; cin >> k >> l;
            // room k switches room l
            switches_graph[k-1].push_back(l-1); 
        }

        for (int t=0; t<r; t++) {
            if (t=0) lights_on.push_back(1);
            else lights_on.push_back(0);
        }

        // building door_graph is O(r+d) and lights_graph is O(r+s)
        
        // vector<int> shortest_path = find_shortest_path(r, 0, 0, doors_graph, switches_graph, lights_on);

        vector<int> lights = find_shortest_path(r, 0, 0, doors_graph, {0}, switches_graph, lights_on);

        for (int l : lights) {
            cout << l;
        }

        // if (shortest_path.empty()) {
        //     cout << "The problem cannot be solved." << endl;
        // } else {
        //     // implement
        // }
    }

    return 0;
}