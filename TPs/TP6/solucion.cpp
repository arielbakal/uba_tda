#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main() {
    
    int n; cin >> n;
    string s; cin >> s;
    string t; cin >> t;

    vector<pair<int, int>> swaps_memo;

    int ops_sum = 0;

    int diff_pairs = 0;

    for (int i=0; i<n; i++) {
        if (s[i] != t[i]) {
            diff_pairs++;
        }

    }

    auto swap = [&](int s_index, int t_index) {
        char temp_s = s[s_index];
        s[s_index] = t[t_index];
        t[t_index] = temp_s;
        swaps_memo.push_back({s_index, t_index});
    };
    
    bool no_solution = false;

    if (diff_pairs % 2 == 0) {
        for (int i=0; i<n; i++) { // iterate over s
    
            if (no_solution) {
                break;
            }
    
            if (s[i] != t[i]) { // if a get diff pair
    
                bool found_equal_pair = false;
    
                for (int j=i+1; j<n; j++) { // iterate over {i...n} and search for second diff pair
    
                    if (s[j] != t[j]) { // got second diff pair
    
                        if (s[i] == s[j]) { // got equal pairs
                            // swap s[i] with t[j]
                            swap(i, j);
                            ops_sum++;
    
                            found_equal_pair = true;
                            break;
                        } 
                    }
                    
                }
    
                if (found_equal_pair == false) { // find second diff pair, not equal
                    for (int k=i+1; k<n; k++) {
    
                        if (s[k] != t[k]) { // got second diff pair (here only handles not equal diff pairs)
                            // swap s[k] with t[k]
                            swap(k, k);
                            ops_sum++;
                            // then swap s[k] with t[i] 
                            swap(k, i);
                            ops_sum++;
    
                            break;
                        }
                        if (k == n-1) { //if didnt found second diff pair, then there is no solution
                            ops_sum = -1;
                            no_solution = true;
                            break;
                        }
                    }
                }
                found_equal_pair = false; // restart var for next pairs
            }
        }
    } else {
        no_solution = true;
        ops_sum = -1;
    }
    
    
    if (no_solution) {
        cout << ops_sum << endl;
    } else {
        cout << ops_sum << endl;
        for (const auto& pair : swaps_memo) {
            cout << pair.first + 1 << " " << pair.second + 1 << endl;
        }
    }

}