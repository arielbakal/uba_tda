#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    while (true) {
        int n; // n elevators
        int k; // objective k floor
        if (!(cin >> n >> k)) break;

        vector<int> T(n); // each elevator's time between adjacent floors 
        for (int i = 0; i < n; i++) {
            cin >> T[i]; 
        }

        vector<vector<int>> elevators_floors(n);

        cin.ignore(); // to ignore the newline character left in the input buffer

        for (int j = 0; j < n; j++) {
            string line;
            getline(cin, line);
            istringstream iss(line);
            int number;
            while (iss >> number) {
                elevators_floors[j].push_back(number);
            }
        }

        cout << n << " " << k << endl;

        for (int i = 0; i < n; i++) {
            cout << T[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            for (int num : elevators_floors[i]) {
                cout << num << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
