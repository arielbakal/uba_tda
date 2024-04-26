#include <iostream>
#include <string>
using namespace std;

bool are_equivalent(const string& string_a, const string& string_b, int start_a, int end_a, int start_b, int end_b) {
    int len_a = end_a - start_a + 1;
    int len_b = end_b - start_b + 1;

    // Error handling
    if (len_a != len_b || len_a == 0)
        return false;

    // Base case (they are equal)
    if (string_a.compare(start_a, len_a, string_b, start_b, len_b) == 0)
        return true;

    // Early return if the strings are not equal
    if (len_a == 1)
        return false;

    // If even length
    if (len_a % 2 == 0) {
        int mid = len_a / 2;

        // Check if first halves are equivalent
        bool first_case_1 = are_equivalent(string_a, string_b, start_a, start_a + mid - 1, start_b, start_b + mid - 1);
        if (first_case_1) {
            // Check if second halves are equivalent
            bool first_case_2 = are_equivalent(string_a, string_b, start_a + mid, end_a, start_b + mid, end_b);
            if (first_case_2)
                return true;
        } else {
            // Check if the halves are equivalent after swapping
            bool second_case_1 = are_equivalent(string_a, string_b, start_a, start_a + mid - 1, start_b + mid, end_b);
            if (second_case_1) {
                bool second_case_2 = are_equivalent(string_a, string_b, start_a + mid, end_a, start_b, start_b + mid - 1);
                if (second_case_2)
                    return true;
            }
        }
        return false;
    } else { // If odd length
        return false;
    }
}

int main() {
    string string_a, string_b;
    cin >> string_a >> string_b;

    if (are_equivalent(string_a, string_b, 0, string_a.length() - 1, 0, string_b.length() - 1)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
