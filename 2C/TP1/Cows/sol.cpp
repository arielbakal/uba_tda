#include <vector>
#include <limits.h>
#include <cstdlib>
#include <utility>
#include <iostream>

using namespace std;

// STATUS: funcion BT impl
// TODO: Hacer divide and conquer chequeando la minima distancia a mid

pair<int, int> min_dist_stall(int i, int last_stall_pos, int actual_tot_dist, int actual_min_dist, int C, const int N, const vector<int>& stall_pos) {
    
    if (i==N && C>0) {
        return make_pair(0, INT_MAX);
    } 
    if (i==N || C==0) {
        return make_pair(actual_tot_dist, actual_min_dist);
    }

    pair<int, int> dont_assing_cow = min_dist_stall(i+1, last_stall_pos, actual_tot_dist, actual_min_dist, C, N, stall_pos);
    
    if (last_stall_pos == -1) {
        actual_min_dist = INT_MAX;
    } else {
        int last_stall_dist = abs(stall_pos[i] - stall_pos[last_stall_pos]);
        
        actual_tot_dist = actual_tot_dist + last_stall_dist;
        
        actual_min_dist = min(actual_min_dist, last_stall_dist);
    }
    
    pair<int, int> assing_cow = min_dist_stall(i+1, i, actual_tot_dist, actual_min_dist, C-1, N, stall_pos);
    
    if (dont_assing_cow.first > assing_cow.first) {
        return dont_assing_cow;
    } else {
        return assing_cow;
    }
}

int main()
{
    int T; cin >> T;
    for (int t=0; t<T; t++) {
        int N, C; cin >> N >> C;
        vector<int> stall_pos(N);
        
        for (int i=0; i<N; i++) {
            cin >> stall_pos[i];            
        }
        
        pair<int, int> res = min_dist_stall(0, -1, 0, INT_MAX, C, N, stall_pos);
        
        cout << res.second << endl;
    }
    return 0;
}