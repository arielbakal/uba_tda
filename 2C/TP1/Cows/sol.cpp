#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int can_cows_fit(int actual_dist, int C, const vector<int>& stall_pos, const int N) {
    
    int cows_fitted, last_pos;
    
    for (int i=0; i<N; i++) {
        if (i==0) {
            cows_fitted = 1;
            last_pos = stall_pos[0];
        }
        int last_pos_dist = stall_pos[i] - last_pos; 
        if (last_pos_dist >= actual_dist) {
            cows_fitted += 1;  
            last_pos = stall_pos[i];  
            
            if (cows_fitted == C) {  
                return true;
            }
        }
    }
    
    return false;
}

int div_and_conquer_dist(int low, int high, int C, const vector<int>& stall_pos, const int N) {
    
    if (low > high) {
        return low-1;
    }
    
    int mid = (low + high) / 2;
    if (can_cows_fit(mid, C, stall_pos, N)) {
        
        return div_and_conquer_dist(mid+1, high, C, stall_pos, N);
    } else {
        
        return div_and_conquer_dist(low, mid-1, C, stall_pos, N);
    }
}

vector<int> merge(vector<int>& ladoIzq, vector<int>& ladoDer) {
    vector<int> res;
    int i = 0, j = 0;

    while (i < ladoIzq.size() && j < ladoDer.size()) {
        if (ladoIzq[i] <= ladoDer[j]) {
            res.push_back(ladoIzq[i]);
            i++;
        } else {
            res.push_back(ladoDer[j]);
            j++;
        }
    }

    while (i < ladoIzq.size()) {
        res.push_back(ladoIzq[i]);
        i++;
    }

    while (j < ladoDer.size()) {
        res.push_back(ladoDer[j]);
        j++;
    }

    return res;
}

vector<int> mergeSort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    int medio = arr.size() / 2;
    vector<int> izq(arr.begin(), arr.begin() + medio);
    vector<int> der(arr.begin() + medio, arr.end());

    izq = mergeSort(izq);
    der = mergeSort(der);

    return merge(izq, der);
}

int main() {
    int T;
    cin >> T;
    for (int t=0; t<T; t++) {
        int N, C;
        cin >> N >> C;
        vector<int> stall_pos(N);
        
        for (int i = 0; i < N; i++) {
            cin >> stall_pos[i];
        }
        
        vector<int> sorted_stall_pos = mergeSort(stall_pos);
        
        int max_dist = sorted_stall_pos[N-1] - sorted_stall_pos[0];
        
        int res = div_and_conquer_dist(1, max_dist, C, sorted_stall_pos, N);
        
        cout << res << endl;
    }
    return 0;
}
