# NOTES
# i'll probably need to save in each tree<acorn> vector the amount of acorns at first position, 
# to know how many iteration i've to do, also to get O(1) accesing that var

class Forest:
    def __init__(self, t, h, f):
        self.t = t
        self.h = h
        self.f = f

def acorns_at_height(t, h, c):
    acorns_at_tree = forest[c][t]
    acorns = 0
    for acorn in acorns_at_tree:
        if acorn == h:
            acorns += 1
    return acorns

def acorn_pd(t, h, f, c, M):
    if h > forest_features[c].h: # base case (got to the top)
        return 0

    if M[t][h] == -1:
        continue_at_tree = acorns_at_height(t, h, c) + acorn_pd(t, h + 1, f, c, M)
        other_trees_max = 0
        for other_tree in range(forest_features[c].t):
            if other_tree != t:
                # Move to other tree, decrease height by 2
                acorn_from_other_tree = acorn_pd(other_tree, h + f, f, c, M)
                other_trees_max = max(other_trees_max, acorn_from_other_tree + acorns_at_height(t, h, c))
        M[t][h] = max(continue_at_tree, other_trees_max)
    return M[t][h]

C = int(input())

forest_features = [] # contains (t, h, f) for each forest
forest = [] # contains acorns heights for each tree for each forest (forest<tree<acorn>>)

# iterate over datasets (forests)
for _ in range(C):
    # first line: t, h, f
    t, h, f = map(int, input().split())
    forest_features.append(Forest(t, h, f))

    trees_temp = []
    # iterate over t trees
    for _ in range(t):
        # #acorns on t-th tree
        acorns_t_tree = list(map(int, input().split()))[1:]  # Skipping the first value which is the number of acorns
        trees_temp.append(acorns_t_tree)

    forest.append(trees_temp)

zero = int(input())

# # Output forest_features
# for feature in forest_features:
#     print(feature.t, feature.h, feature.f)

# # Output forest
# for trees in forest:
#     for tree in trees:
#         print(' '.join(map(str, tree)))

for c in range(C):
    M = [[-1] * (forest_features[c].h + 1) for _ in range(forest_features[c].t)]

    max_acorns = 0

    for tree in range(forest_features[c].t):
        max_acorns_temp = acorn_pd(tree, 1, forest_features[c].f, c, M)
        if max_acorns_temp > max_acorns:
            max_acorns = max_acorns_temp

    print(max_acorns)

