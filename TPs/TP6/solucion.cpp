#include <iostream>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

// NOTES: remove pair before swapping

int main() {
    
    int n; cin >> n;
    string string_s; cin >> string_s;
    string string_t; cin >> string_t;

    vector<tuple<char, int>> s;
    vector<tuple<char, int>> t;
    int string_len = 0;

    // remove all equal pairs (there's no need for swapping)
    for (int i=0; i<n; i++) {
        if (string_s[i] != string_t[i]) {
            s.push_back(make_tuple(string_s[i],i));
            t.push_back(make_tuple(string_t[i],i));
            string_len++;
        }
    }

    vector<tuple<int, int>> swaps_memo;

    int ops_sum = 0;

    auto swap = [&](int s_index, int t_index) {
        // swap chars, maintaining index
        tuple<char, int> new_s = make_tuple(get<0>(t[t_index]), get<1>(s[s_index]));
        tuple<char, int> new_t = make_tuple(get<0>(s[s_index]), get<1>(t[t_index]));
        s[s_index] = new_s;
        t[t_index] = new_t;

        swaps_memo.push_back(make_tuple(get<1>(s[s_index]), get<1>(t[t_index])));
    };

    for (int i=0; i<string_len; i++) { // iterate over s

        if (get<0>(s[i]) != get<0>(t[i])) { // if a get diff pair

            if (n == 1) {
                ops_sum = -1;
            }

            bool found_equal_pair = false;

            for (int j=i+1; j<string_len; j++) { // iterate over {i...n} and search for second diff pair

                if (get<0>(s[j]) != get<0>(t[j])) { // got second diff pair

                    if (get<0>(s[i]) == get<0>(s[j])) { // got equal pairs
                        // swap s[i] with t[j]
                        swap(i, j);
                        ops_sum++;

                        found_equal_pair = true;
                        j = string_len; // end loop
                        i = 0; // restart primary loop
                    } 
                }
                
            }

            if (found_equal_pair == false) { // find second diff pair, not equal
                for (int k=i+1; k<string_len; k++) {

                    if (get<0>(s[k]) != get<0>(t[k])) { // got second diff pair (here only handles not equal diff pairs)
                        // swap s[k] with t[k]
                        swap(k, k);
                        ops_sum++;
                        // then swap s[k] with t[i] 
                        swap(k, i);
                        ops_sum++;

                        k = string_len; // end loop
                        i = 0; // restart primary loop
                    }
                    if (k == n-1) { //if didnt found second diff pair, then there is no solution
                        ops_sum = -1;
                    }
                }
            }
            found_equal_pair = false; // restart var for next pairs
        } else {

        }
    }

    cout << ops_sum << endl;
    for (const auto& pair : swaps_memo) {
        cout << get<0>(pair) + 1 << " " << get<1>(pair) + 1 << endl;
    }

}