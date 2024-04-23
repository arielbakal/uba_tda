# NOTES
# i'll probably need to save in each tree<acorn> vector the amount of acorns at first position, 
# to know how many iteration i've to do, also to get O(1) accesing that var

import sys

# Set the recursion limit to a higher value
sys.setrecursionlimit(2100)  # Set the limit to 10,000 recursions

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

def acorn_pd(f, c):
    M = [[0] * (forest_features[c].h + 1) for _ in range(forest_features[c].t)]
    M_max = [0] * (forest_features[c].h + 1)

    for tree in range(forest_features[c].t):
        for acorn_height in forest[c][tree]:
            M[tree][acorn_height] += 1

    # Iterate bottom-up
    for height in range(1, forest_features[c].h + 1):
        for tree in range(forest_features[c].t):
            if height - f > 0:
                M[tree][height] = max(M[tree][height] + M[tree][height-1], M[tree][height] + M_max[height-f])
            else:
                M[tree][height] += M[tree][height-1]
            M_max[height] = max(M_max[height], M[tree][height])

    max_acorns = max(M_max)

    # print(M)
    # print(M_max)

    return max_acorns

C = int(input())

forest_features = [] # contains (t, h, f) for each forest
forest = [] # contains acorns heights for each tree for each forest (forest<tree<acorn>>)

# iterate over datasets (forests)
for _ in range(C):
    # first line: t, h, f
    t, h, f = map(int, input().split())
    forest_features.append(Forest(t, h, f))

    trees = []
    # iterate over t trees
    for _ in range(t):
        # #acorns on t-th tree
        acorns = list(map(int, input().split()))[1:]  # Skipping the first value which is the number of acorns
        trees.append(acorns)
    
    forest.append(trees)

zero = int(input())

for c in range(C):
    max_acorns = acorn_pd(forest_features[c].f, c)
    print(max_acorns)