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

            for (int j=i+1; j<n; j++) { // iterate over {i...n} and search for second diff pair

                if (s[j] != t[j]) { // got second diff pair

                    if (s[i] == s[j]) { // got equal pairs
                        // swap s[i] with t[j]
                        swap(i, j);
                        swaps_memo.push_back(make_tuple(i, j));
                        ops_sum++;
                    } else { // got inverted pairs
                        // swap s[j] with t[j]
                        swap(j, j);
                        swaps_memo.push_back(make_tuple(j, j));
                        ops_sum++;
                        // then swap s[j] with t[i] 
                        swap(j, i);
                        swaps_memo.push_back(make_tuple(j, i));
                        ops_sum++;
                    }
                    j=n;
                }
                if (j == n-1) { //if didnt found second diff pair, then there is no solution
                    ops_sum = -1;
                }
            }
        }
    }

    cout << ops_sum << endl;
    for (const auto& pair : swaps_memo) {
        cout << get<0>(pair) << " " << get<1>(pair) << endl;
    }

}
