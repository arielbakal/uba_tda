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
    keys_global.append(keys)
    
def keys_dist(a, b):
    distance = abs(a - b)
    return min(distance, 10 - distance)

def build_graph(keys):
    adj_list = {}
    for key1 in keys:
        neighbors = []
        for key2 in keys:
            if key1 != key2:
                neighbors.append(key2)
        adj_list[key1] = neighbors
    return adj_list

