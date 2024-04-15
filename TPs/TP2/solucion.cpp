#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> heights;
vector<vector<int>> widths;

int skyline_incr(int i, int last_height, int total_width, int case_num) {
    int N = heights[case_num - 1].size();
    static vector<vector<int>> M_incr(N + 1, vector<int>(*max_element(heights[case_num - 1].begin(), heights[case_num - 1].end()) + 2, -1));
    
    if (i == N) 
        return 0;

    if (M_incr[i][last_height] == -1) {
        if (heights[case_num - 1][i] > last_height) {
            M_incr[i][last_height] = max(skyline_incr(i + 1, last_height, total_width, case_num), skyline_incr(i + 1, heights[case_num - 1][i], total_width + widths[case_num - 1][i], case_num) + widths[case_num - 1][i]);
        } else {
            M_incr[i][last_height] = skyline_incr(i + 1, last_height, total_width, case_num);
        }
    }
    return M_incr[i][last_height];
}

int skyline_decr(int i, int last_height, int total_width, int case_num) {
    int N = heights[case_num - 1].size();
    static vector<vector<int>> M_decr(N + 1, vector<int>(*max_element(heights[case_num - 1].begin(), heights[case_num - 1].end()) + 2, -1));

    if (i == N) 
        return 0;
    
    if (M_decr[i][last_height] == -1) {
        if (heights[case_num - 1][i] < last_height) {
            M_decr[i][last_height] = max(skyline_decr(i + 1, last_height, total_width, case_num), skyline_decr(i + 1, heights[case_num - 1][i], total_width + widths[case_num - 1][i], case_num) + widths[case_num - 1][i]);
        } else {
            M_decr[i][last_height] = skyline_decr(i + 1, last_height, total_width, case_num);
        }
    }
    return M_decr[i][last_height];
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; ++i) {
        int N;
        cin >> N;

        vector<int> heights_temp(N);
        vector<int> widths_temp(N);

        for (int j = 0; j < N; ++j) {
            cin >> heights_temp[j];
        }

        for (int j = 0; j < N; ++j) {
            cin >> widths_temp[j];
        }

        heights.push_back(heights_temp);
        widths.push_back(widths_temp);

        int max_incr_length = skyline_incr(0, 0, 0, i + 1);
        int max_decr_length = skyline_decr(0, *max_element(heights[i].begin(), heights[i].end()) + 1, 0, i + 1);

        if (max_incr_length >= max_decr_length) {
            cout << "Case " << i + 1 << ". Increasing (" << max_incr_length << "). Decreasing (" << max_decr_length << ")." << endl;
        } else {
            cout << "Case " << i + 1 << ". Decreasing (" << max_decr_length << "). Increasing (" << max_incr_length << ")." << endl;
        }
    }

    return 0;
}
