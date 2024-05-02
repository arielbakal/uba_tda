#include <iostream>
#include <string>
using namespace std;

int main() {
    
    int n; cin >> n;
    string string_s; cin >> string_s;
    string string_t; cin >> string_t;

    char* s = &string_s[0];
    char* t = &string_t[0];

    int ops_sum = 0;

    for (int i=0; i<n; i++) { // iterate over s

        if (s[i] != t[i]) { // if a get diff pair

            if (n == 1) {
                ops_sum = -1;
            }

            for (int j=i+1; j<n; j++) { // iterate over {i...n} and search for second diff pair

                if (s[j] != t[j]) { // got second diff pair

                    if (s[i] == s[j]) { // got equal pairs
                        // swap s[i] with t[j]
                        char temp_s_i = s[i]; 
                        s[i] = t[j];
                        t[i] = temp_s_i;
                        ops_sum++;
                    } else { // got inverted pairs
                        // swap s[j] with t[j]
                        char temp_s_j = s[j];
                        s[j] = t[j];
                        t[j] = temp_s_j;
                        ops_sum++;
                        // then swap t[i] with s[j] 
                        char temp_t_i = t[i];
                        t[i] = s[j];
                        s[j] = temp_t_i;
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

    cout << ops_sum << s << t << endl;

}
