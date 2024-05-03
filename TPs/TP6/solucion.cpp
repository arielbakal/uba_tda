#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main() {
    
    int n; cin >> n;
    string string_s; cin >> string_s;
    string string_t; cin >> string_t;
    
    vector<pair<char, int>> s;
    vector<pair<char, int>> t;
    int string_len = 0;
    
    // remove all equal pairs (there's no need for swapping)
    for (int i=0; i<n; i++) {
        if (string_s[i] != string_t[i]) {
            s.push_back(make_pair(string_s[i],i));
            t.push_back(make_pair(string_t[i],i));
            string_len++;
        }
    }

    set<pair<int, int>> swaps_memo;

    int ops_sum = 0;

    auto swap = [&](int s_index, int t_index) {
        
        pair<char, int> temp_s = s[s_index];
        pair<char, int> temp_t = t[t_index];
        
        swaps_memo.insert({s_index, t_index});

        if (temp_s.first == temp_t.first) {
            s.erase(s.begin() + s_index);
            t.erase(t.begin() + t_index);
            string_len--;
        } else {
            // swap chars, maintaining index
            pair<char, int> new_s = make_pair(temp_t.first, temp_s.second);
            pair<char, int> new_t = make_pair(temp_s.first, temp_t.second);
            s[s_index] = new_s;
            t[t_index] = new_t;
        }
    };

    for (int i=0; i<string_len; i++) { // iterate over s

        if (s[i].first != t[i].first) { // if a get diff pair

            if (string_len == 1) {
                ops_sum = -1;
            }

            bool found_equal_pair = false;

            for (int j=i+1; j<string_len; j++) { // iterate over {i...n} and search for second diff pair

                if (s[j].first != t[j].first) { // got second diff pair

                    if (s[i].first == s[j].first) { // got equal pairs
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

                    if (s[k].first != t[k].first) { // got second diff pair (here only handles not equal diff pairs)
                        // swap s[k] with t[k]
                        swap(k, k);
                        ops_sum++;
                        // then swap s[k] with t[i] 
                        swap(k, i);
                        ops_sum++;

                        k = string_len; // end loop
                        i = 0; // restart primary loop
                    }
                    if (k == string_len-1) { //if didnt found second diff pair, then there is no solution
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
        cout << pair.first + 1 << " " << pair.second + 1 << endl;
    }

}
