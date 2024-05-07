#include <iostream>
#include <vector>
using namespace std;

// NOTES: 
// REDO find_shortest_path and Implement Dijkstra then A*

vector<int> find_shortest_path(int r, int room, int steps, vector<vector<int>>& doors, vector<vector<int>>& switches, vector<int>& lights_on) {

    if (room == r-1) { // Case base: got to the room
        return steps;
    };

    // visit neighbors
    for (int neighbor : doors[room]) { // iterate over neighbors rooms

        if (lights_on[neighbor] == 1) { // if lights are on in neighbor room then,

            // explore neighbor room
            find_shortest_path(r, neighbor, steps + 1, doors, switches, lights_on);  

        } else { // check if i can switch neighbor room lights

            for (int switches_neighbor : switches[room]) { // iterate over rooms i can switch on
                if (neighbor == switches_neighbor) { // if i can switch on a neighbor room then,

                    // switch light and explore
                    vector<int> temp_lights_on = lights_on;
                    temp_lights_on[switches_neighbor] = 1; // switch lights on 
                    find_shortest_path(r, room, steps + 1, doors, switches, temp_lights_on); // only switches room

                    // dont switch light and explore
                    find_shortest_path(r, room, steps, doors, switches, lights_on);

                    // with this i can explore all combination of which lights i switch on in my switches_neighbor
                } 
            }

            for (int switches_neighbor : switches_neighbors) {


            }



            for (int room_switched : switches[room]) { // get rooms i can switch its lights

                if (neighbor == room_switched) { // if i can switch on a neighbor room then,

                    vector<int> temp_lights_on = lights_on;
                    
                    // explore different room
                    find_shortest_path(r, neighbor, steps + 2, doors, switches);  
                }
            }
        }
        
    }

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

        for (int t=0; t<r: t++) {
            if (t=0) lights_on.push_back(1)
            else lights_on.push_back(0)
        }

        // building door_graph is O(r+d) and lights_graph is O(r+s)
        
        vector<int> shortest_path = find_shortest_path(r, 0, 0, doors_graph, switches_graph, lights_on);

        if (shortest_path.empty()) {
            cout << "The problem cannot be solved." << endl;
        } else {
            // implement
        }
    }

    return 0;
}