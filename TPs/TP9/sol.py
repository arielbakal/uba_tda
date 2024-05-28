# NOTES: translate to cpp

# 1. Build adj list where each neighbor has its cost, excluding 0000
# 2. Calculate distances between 0000 and all keys, then get min_dist (also starting_cost) and starting_key.
# This will be our starting key for Prim. We cant start from 0000 or include it on the graph bc we cant JUMP there.
# If we do it will generate an MST where 0000 could have multiples edges
# 3. Implement Prim but only summing costs (we dont need to save fathers and recreate MST)

def single_key_dist(a, b):
    distance = abs(a - b)
    return min(distance, 10 - distance)

def keys_dist(key1, key2):
    res = 0
    for i in range(4):
        res += single_key_dist(key1[i], key2[i])
    return res

def min_start_cost(keys):
    min_dist = float('inf')
    min_key = (0, 0, 0, 0)
    for key in keys:
        dist = keys_dist((0, 0, 0, 0), key) 
        if dist < min_dist:
            min_key = key
            min_dist = dist
    return min_dist, min_key

def build_graph(keys): # represent graph as adj list with neighbors as a pair<neighbor, weight to that neighbor>
    adj_list = {}
    for key1 in keys:
        neighbors = []
        for key2 in keys:
            if key1 != key2:
                neighbors.append([key2, keys_dist(key1, key2)])
        adj_list[key1] = neighbors
    return adj_list

# Since graph is complete, m ∈ Ω(n^2) => I should use Prim trivial impl O(n^2) rather than heap impl O((m+n)logn) = O(n^2logn). Bc O(n^2) < O(n^2logn)

def prim_min_cost(graph, starting_cost, starting_key):
    total_cost = starting_cost
    visited = [starting_key]

    for _ in range(len(graph)):
        min_dist = float('inf')
        min_key = None
        for key in graph.keys():
            if key not in visited:
                for neighbor in graph[key]:
                    if neighbor[0] in visited:
                        if neighbor[1] < min_dist:
                            min_dist = neighbor[1]
                            min_key = key

        if min_key is None:  
            break

        visited.append(min_key)
        total_cost += min_dist

    return total_cost

T = int(input()) # test cases
keys_global = []

for _ in range(T):
    safe = input().split()
    N = int(safe[0])
    keys = [safe[i] for i in range(1, N+1)]
    keys = [tuple(int(d) for d in key) for key in keys] 
    keys_global.append(keys)

for i in range(T):
    graph = build_graph(keys_global[i])
    starting_cost, starting_key = min_start_cost(keys_global[i])
    min_cost = prim_min_cost(graph, starting_cost, starting_key)
    print(min_cost)