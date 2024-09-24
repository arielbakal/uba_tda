#include <vector>
#include <limits.h>
#include <cstdlib>
#include <iostream>

using namespace std;

// STATUS: funcion BT impl
// TODO: lo que se busca es maximizar la distancia TOTAL entre TODAS las vacas y retornar la min dist entre esas distancias que maximizan el total.

int min_dist_stall(int i, int last_stall_pos, int actual_min_dist, int C, const int N, const vector<int>& stall_pos) {
    
    if (i==N && C>0) {
        return INT_MAX;
    } 
    if (i==N || C==0) {
        return actual_min_dist;
    }

    int dont_assing_cow = min_dist_stall(i+1, last_stall_pos, actual_min_dist, C, N, stall_pos);
    
    if (last_stall_pos == -1) {
        actual_min_dist = INT_MAX;
    } else {
        int temp_min_dist = abs(stall_pos[last_stall_pos] - stall_pos[i]);
        actual_min_dist = min(actual_min_dist, temp_min_dist);
    }
    
    int assing_cow = min_dist_stall(i+1, i, actual_min_dist, C-1, N, stall_pos);
    
    return min(dont_assing_cow, assing_cow);
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
        
        int res = min_dist_stall(0, -1, INT_MAX, C, N, stall_pos);
        
        cout << res << endl;
    }
    return 0;
}