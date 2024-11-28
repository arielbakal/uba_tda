#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> heights;
vector<vector<int>> widths;
vector<int> buildings_num;

int skyline_incr(int i, int last_height, int total_width, int case_num, int N, vector<vector<int>>& M_incr) {
    if (i == N) 
        return 0;

    if (M_incr[i][last_height] == -1) {
        if (heights[case_num ][i] > last_height) {
            M_incr[i][last_height] = max(skyline_incr(i + 1, last_height, total_width, case_num, N, M_incr), skyline_incr(i + 1, heights[case_num][i], total_width + widths[case_num][i], case_num, N, M_incr) + widths[case_num][i]);
        } else {
            M_incr[i][last_height] = skyline_incr(i + 1, last_height, total_width, case_num, N, M_incr);
        }
    }
    return M_incr[i][last_height];
}

int skyline_decr(int i, int last_height, int total_width, int case_num, int N, vector<vector<int>>& M_decr) {
    if (i == N) 
        return 0;
    
    if (M_decr[i][last_height] == -1) {
        if (heights[case_num][i] < last_height) {
            M_decr[i][last_height] = max(skyline_decr(i + 1, last_height, total_width, case_num, N, M_decr), skyline_decr(i + 1, heights[case_num][i], total_width + widths[case_num][i], case_num, N, M_decr) + widths[case_num][i]);
        } else {
            M_decr[i][last_height] = skyline_decr(i + 1, last_height, total_width, case_num, N, M_decr);
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
        buildings_num.push_back(N);
    }

    for (int i = 0; i < T; ++i) {

        vector<vector<int>> M_incr(buildings_num[i] + 1, vector<int>(*max_element(heights[i].begin(), heights[i].end()) + 2, -1));
        vector<vector<int>> M_decr(buildings_num[i] + 1, vector<int>(*max_element(heights[i].begin(), heights[i].end()) + 2, -1));

        int max_incr_length = skyline_incr(0, 0, 0, i, buildings_num[i], M_incr);
        int max_decr_length = skyline_decr(0, *max_element(heights[i].begin(), heights[i].end()) + 1, 0, i, buildings_num[i], M_decr);

        if (max_incr_length >= max_decr_length) {
            cout << "Case " << i + 1 << ". Increasing (" << max_incr_length << "). Decreasing (" << max_decr_length << ")." << endl;
        } else {
            cout << "Case " << i + 1 << ". Decreasing (" << max_decr_length << "). Increasing (" << max_incr_length << ")." << endl;
        }
    }

    return 0;
}
