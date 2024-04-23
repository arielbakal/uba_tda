#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// NOTES: 
// SOLVES CORRECTLY INDIVIDUAL PROBLEMS
// problem at handling all vectors in each subset iteration

struct Forest {
    int t, h, f;
};

vector<Forest> forest_features; // contains (t, h, f) for each forest
vector<vector<vector<int>>> forest; // contains acorns heights for each tree for each forest (forest<tree<acorn>>)

int acorn_pd(int c) {
    int t = forest_features[c].t;
    int h = forest_features[c].h;
    int f = forest_features[c].f;

    vector<vector<int>> M(t, vector<int>(h + 1));

    vector<int> M_max(h + 1);

    for (int tree = 0; tree < t; tree++) {
        for (int acorn_height : forest[c][tree]) {
            M[tree][acorn_height] += 1;
        }
    }

    // Iterate bottom-up
    for (int height = 1; height <= h; height++) {
        for (int tree = 0; tree < t; tree++) {
            if (height - f > 0) { // Verify if I can fly to other tree
                int continue_at_tree = M[tree][height] + M[tree][height - 1];
                int fly_other_tree = M[tree][height] + M_max[height - f];
                M[tree][height] = max(continue_at_tree, fly_other_tree);
            } else { // else, continue
                M[tree][height] += M[tree][height - 1];
            }
            
            // update max acorns at height
            M_max[height] = max(M_max[height], M[tree][height]);
        }
    }

    int max_acorns = *max_element(M_max.begin(), M_max.end());

    // cout << "Memo Matrix M:" << endl;
    // for (int i = 0; i < t; ++i) {
    //     for (int j = 0; j <= h; ++j) {
    //         cout << M[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // // Print max at height list M_max
    // cout << "Max at Height List M_max:" << endl;
    // for (int i = 0; i <= h; ++i) {
    //     cout << M_max[i] << " ";
    // }
    // cout << endl;

    return max_acorns;
}

int main() {
    int C;
    cin >> C;

    // iterate over datasets (forests)
    for (int i = 0; i < C; i++) {

        // first line: t, h, f
        int t, h, f;
        cin >> t >> h >> f;

        forest_features.push_back({t, h, f});

        vector<vector<int>> trees_temp(t); // Resize to hold 't' empty vectors

        // Clear the vector to avoid retaining values from previous dataset
        trees_temp.clear();

        // iterate over t trees
        for (int j = 0; j < t; j++) {

            // #acorns on j-th tree
            int a;
            cin >> a;

            // Resize the vector to hold 'a' elements
            trees_temp.push_back(vector<int>(a));

            // iterate over a acorns
            for (int k = 0; k < a; k++) {
                cin >> trees_temp[j][k];
            }
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

        int max_acorns = acorn_pd(c);

        cout << max_acorns << endl;
    }

    return 0;
}