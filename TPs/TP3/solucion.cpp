#include <iostream>
#include <vector>
using namespace std;

// NOTES
// i'll probably need to save in each tree<acorn> vector the amount of acorns at first position, 
// to know how many iteration i've to do, also to get O(1) accesing that var

struct Forest {
    int t, h, f;
};

int acorns_at_height(int t, int h, int c);

vector<Forest> forest_features; // contains (t, h, f) for each forest
vector<vector<vector<int>>> forest; // contains acorns heights for each tree for each forest (forest<tree<acorn>>)

int acorns_at_height(int t, int h, int c) {

    vector<int> acorns_at_tree = forest[c][t];

    int acorns = 0;

    for (int acorn : acorns_at_tree) {
        if (acorn == h) {
            acorns += 1;
        }
    }

    return acorns;

};

int acorn_pd(int t, int h, int f, int c, vector<vector<int>>& M) {

    if (h > forest_features[c].h) { // base case (got to the top)
        return 0;
    }

    if (M[t][h] == -1) {

        int continue_at_tree = acorns_at_height(t, h, c) + acorn_pd(t, h+1, f, c, M);

        int other_trees_max = 0;
        for (int other_tree = 0; other_tree < forest_features[c].t; other_tree++) {
            if (other_tree != t) {
                // Move to other tree, decrease height by 2
                int acorn_from_other_tree = acorns_at_height(other_tree, h, c) + acorn_pd(other_tree, h+f, f, c, M);
                other_trees_max = max(other_trees_max, acorn_from_other_tree);
            }
        }

        M[t][h] = max(continue_at_tree, other_trees_max);

    } 

    return M[t][h];
};

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

    // for (int c=0; c<C; c++) {

    //     vector<vector<int>> M(forest_features[c].t + 1, vector<int>(forest_features[c].h + 1, -1));

    //     int max_acorns_tree1 = acorn_pd(1, 1, forest_features[c].f, c, M);

    //     cout << max_acorns_tree1 << endl;

    // }

    return 0;
}