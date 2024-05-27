# Notes: 
# 1. Armo un grafo con las keys como nodos incluyendo 0000
# 2a. Calculo todos los pesos (distancias entre keys)
# 2b. Si |a-b|>5, 10-|a-b| else |a-b|
# 3. Armo un AGM enraizado en 0000
# 4. El resultado es la suma de las aristas del AGM

T = int(input()) # test cases
keys_global = []

for _ in range(T):
    safe = input().split()
    N = int(safe[0])
    keys = [safe[i] for i in range(1, N+1)]
    keys = [tuple(int(d) for d in key) for key in keys] 
    keys.insert(0, (0, 0, 0 ,0))
    keys_global.append(keys)
    
def single_key_dist(a, b):
    distance = abs(a - b)
    return min(distance, 10 - distance)

def keys_dist(key1, key2):
    res = 0
    for i in range(4):
        res += single_key_dist(key1[i], key2[i])
    return res

# Since im building a complete graph, i choose doing an adj matrix with its weights

def build_graph(keys):
    adj_matrix = []
    for key1 in keys:
        weights = []
        for key2 in keys:
            if key1 != key2:
                weights.append(keys_dist(key1, key2))
            else:
                weights.append(0)
        adj_matrix.append(weights) 
    return adj_matrix