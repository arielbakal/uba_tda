#include <iostream>
#include <string>
using namespace std;

bool are_equivalent(const string& string_a, const string& string_b) {
    int len_a = string_a.length();
    int len_b = string_b.length();

    if (len_a != len_b) // Error handling
        return false;
    
    if (len_a == 0)
        return false;

    if (string_a == string_b) // Base case (they are equal)
        return true;
    
    if (len_a == 1)
        return false;
    
    if (len_a % 2 == 0) { // If even length
        int mid = len_a / 2;

        string string_a_1 = string_a.substr(0, mid);
        string string_a_2 = string_a.substr(mid);

        string string_b_1 = string_b.substr(0, mid);
        string string_b_2 = string_b.substr(mid);

        bool first_case = are_equivalent(string_a_1, string_b_1) && are_equivalent(string_a_2, string_b_2);
        if (first_case)
            return true;
        else {
            bool second_case = are_equivalent(string_a_1, string_b_2) && are_equivalent(string_a_2, string_b_1);
            return second_case;
        }
    } else { // If odd length
        return false;
    }
}

int main() {
    string string_a, string_b;
    cin >> string_a >> string_b;
    
    if (are_equivalent(string_a, string_b)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}   