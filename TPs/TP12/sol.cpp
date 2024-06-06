#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t; cin >> t;

    for (int k=0; k<t; k++) {

        int n; cin >> n; // n towers
        vector<vector<int>> power_matrix(n);

        for (int i=0; i<n; i++) { // build power matrix
            vector<int> power_line(n);
            for (int j=0; j<n; j++) {
                cin >> power_line[j];
            }
            power_matrix.push_back(power_line);
        }

        vector<int> tower_order(n);

        for (int i=0; i<n; i++) {
            cin >> tower_order[i];
        }
    }
    
    return 0;
}
