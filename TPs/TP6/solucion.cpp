#include <iostream>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

int main() {
    
    int n; cin >> n;
    string string_s; cin >> string_s;
    string string_t; cin >> string_t;

    char* s = &string_s[0];
    char* t = &string_t[0];

    vector<tuple<int, int>> swaps_memo;

    int ops_sum = 0;

    auto swap = [&](int s_index, int t_index) {
        char temp_s = s[s_index];
        s[s_index] = t[t_index];
        t[t_index] = temp_s;
    };

    for (int i=0; i<n; i++) { // iterate over s

        if (s[i] != t[i]) { // if a get diff pair

            if (n == 1) {
                ops_sum = -1;
            }

            bool found_equal_pair = false;

            for (int j=i+1; j<n; j++) { // iterate over {i...n} and search for second diff pair

                if (s[j] != t[j]) { // got second diff pair

                    if (s[i] == s[j]) { // got equal pairs
                        // swap s[i] with t[j]
                        swap(i, j);
                        swaps_memo.push_back(make_tuple(i, j));
                        ops_sum++;

                        found_equal_pair = true;
                        j = n; // end loop
                        i = 0; // restart primary loop
                    } 
                }
                
            }

            if (found_equal_pair == false) { // find second diff pair, not equal
                for (int k=i+1; k<n; k++) {

                    if (s[k] != t[k]) { // got second diff pair (here only handles not equal diff pairs)
                        // swap s[k] with t[k]
                        swap(k, k);
                        swaps_memo.push_back(make_tuple(k, k));
                        ops_sum++;
                        // then swap s[k] with t[i] 
                        swap(k, i);
                        swaps_memo.push_back(make_tuple(k, i));
                        ops_sum++;

                        k = n; // end loop
                        i = 0; // restart primary loop
                    }
                    if (k == n-1) { //if didnt found second diff pair, then there is no solution
                        ops_sum = -1;
                    }
                }
            }
            found_equal_pair = false; // restart var for next pairs
        }
    }

    cout << ops_sum << endl;
    for (const auto& pair : swaps_memo) {
        cout << get<0>(pair) + 1 << " " << get<1>(pair) + 1 << endl;
    }

}