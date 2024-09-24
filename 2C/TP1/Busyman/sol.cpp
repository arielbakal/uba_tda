#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
    int T; cin >> T;
    for (int t=0; t<T; t++) {
        int N; cin >> N;
        vector<pair<int,int>> act_time(N);
        vector<int> act_length(N);
        
        for (int i=0; i<N; i++) {
            int start, end;
            cin >> start >> end;
            act_time[i] = make_pair(start, end);
            act_length[i] = end - start;
        }
        
    }

    return 0;
}