#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {

    int T; cin >> T;
    for (int t=0; t<T; t++) {

        int N, M; cin >> N >> M;
        unordered_map<string, int> suiting_tshirts;

        for (int m=0; m<M; m++) {

            string size1, size2; cin >> size1 >> size2;
            
            suiting_tshirts[size1] += 1;
            suiting_tshirts[size2] += 1;
        }
    }
    return 0;
}