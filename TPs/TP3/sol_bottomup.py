class Forest:
    def __init__(self, t, h, f):
        self.t = t
        self.h = h
        self.f = f

def acorn_pd(c):
    t, h, f = forest_features[c].t, forest_features[c].h, forest_features[c].f

    M = [[0] * (h + 1) for _ in range(t)] # memo matrix
    # max at height list, for getting the acorns of the tree that maximices
    M_max = [0] * (h + 1) 

    # Initialize acorns 
    for tree in range(t):
        for acorn_height in forest[c][tree]:
            M[tree][acorn_height] += 1

    # Iterate bottom-up
    for height in range(1, h + 1):
        for tree in range(t):
            if height - f > 0: # Verify if i can fly to other tree
                continue_at_tree = M[tree][height] + M[tree][height-1]
                fly_other_tree = M[tree][height] + M_max[height-f]
                M[tree][height] = max(continue_at_tree, fly_other_tree)
            else: # else, continue
                M[tree][height] += M[tree][height-1]
            
            # update max acorns at height
            M_max[height] = max(M_max[height], M[tree][height])

    max_acorns = max(M_max)

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
    max_acorns = acorn_pd(c)
    print(max_acorns)