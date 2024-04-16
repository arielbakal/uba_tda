#include <iostream>
#include <vector>
using namespace std;

struct Forest {
    int t, h, f;
};

vector<Forest> forest_features; // contains (t, h, f) for each forest
vector<vector<vector<int>>> forest; // contains accorns heights for each tree for each forest (forest<tree<accorn>>)

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

            vector<int> accorns_t_tree(a);

            // iterate over a accorns
            for (int k=0; k<a; k++) {
                cin >> accorns_t_tree[k];
            }

            trees_temp.push_back(accorns_t_tree);
        }

        forest.push_back(trees_temp);

        int zero; cin >> zero;
    }

    // Output forest_features
    for (const auto& feature : forest_features) {
        cout << feature.t << " " << feature.h << " " << feature.f << endl;
    }

    // Output forest
    for (const auto& trees : forest) {
        for (const auto& tree : trees) {
            for (int acorn : tree) {
                cout << acorn << " ";
            }
            cout << endl;
        }
    }

    return 0;
}