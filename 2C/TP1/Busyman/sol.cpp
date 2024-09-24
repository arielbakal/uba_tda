#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> merge(vector<pair<int, int>>& ladoIzq, vector<pair<int, int>>& ladoDer) {
    vector<pair<int, int>> res;
    int i = 0, j = 0;

    while (i < ladoIzq.size() && j < ladoDer.size()) {
        if (ladoIzq[i].second <= ladoDer[j].second) {
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

vector<pair<int, int>> mergeSort_modified(vector<pair<int, int>>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    int medio = arr.size() / 2;
    vector<pair<int, int>> izq(arr.begin(), arr.begin() + medio);
    vector<pair<int, int>> der(arr.begin() + medio, arr.end());

    izq = mergeSort_modified(izq);
    der = mergeSort_modified(der);

    return merge(izq, der);
}

int main()
{
    int T; cin >> T;
    for (int t=0; t<T; t++) {
        int N; cin >> N;
        vector<pair<int, int>> act_time(N);
        
        for (int i=0; i<N; i++) {
            int start, end;
            cin >> start >> end;
            act_time[i] = make_pair(start, end);
        }
        
        int res = 1;
        
        // Ordeno en base a los end times
        vector<pair<int, int>> act_time_sorted = mergeSort_modified(act_time);
        
        pair<int,int> actual_act = act_time_sorted[0];
        for (int i=1; i<N; i++) {
            // Si la actividad sig empieza despues de que termina la actual, es valido considerarlo
            if (actual_act.second <= act_time_sorted[i].first) {
                actual_act = act_time_sorted[i];
                res += 1;
            }
        }
        cout << res << endl;
    }

    return 0;
}