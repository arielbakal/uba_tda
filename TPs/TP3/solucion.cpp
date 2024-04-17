#include <iostream>
#include <vector>
using namespace std;

// NOTES
// i'll probably need to save in each tree<acorn> vector the amount of acorns at first position, 
// to know how many iteration i've to do, also to get O(1) accesing that var

struct Forest {
    int t, h, f;
};

vector<Forest> forest_features; // contains (t, h, f) for each forest
vector<vector<vector<int>>> forest; // contains acorns heights for each tree for each forest (forest<tree<acorn>>)

int acorn_pd(int t, int h, int f, int c, vector<vector<int>> M, bool first_call) {

    if (first_call) {
        
        for (int tree=0; tree<forest_features[c].t; tree++) { // i have t-bottoms

            if (h == forest_features[c].h + 1) { // base case (got to the top)
                return 0;
            }

            if (M[t][h] == -1){

                M[t][h] = max() 

            }

        }

    } else {



    }

    

}





int main() {
    int C;
    cin >> C;

    // iterate over datasets (forests)
    for (int i=0; i<C; i++) {

        // first line: t, h, f
        int t, h, f;
        cin >> t >> h >> f;

        forest_features.push_back({t, h, f});

        vector<vector<int>> trees_temp(t); 

        // iterate over t trees
        for (int j=0; j<t; j++) {

            // #accorns on t-th tree
            int a;
            cin >> a;

            vector<int> acorns_t_tree(a);

            // iterate over a acorns
            for (int k=0; k<a; k++) {
                cin >> acorns_t_tree[k];
            }

            trees_temp.push_back(acorns_t_tree);
        }

        forest.push_back(trees_temp);

        int zero; cin >> zero;
    }

    // // Output forest_features
    // for (const auto& feature : forest_features) {
    //     cout << feature.t << " " << feature.h << " " << feature.f << endl;
    // }

    // // Output forest
    // for (const auto& trees : forest) {
    //     for (const auto& tree : trees) {
    //         for (int acorn : tree) {
    //             cout << acorn << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    for (int c=0; c<C; c++) {

        vector<vector<int>> M(forest_features[c].t + 1, forest_features[c].h + 1, -1);

        max_acorns = acorn_pd(forest_features[c].t, forest_features[c].h, forest_features[c].f, M);

        cout << max_acorns;

    }

    return 0;
}