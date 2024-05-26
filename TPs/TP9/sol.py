# Notes: 
# 1. Armo un grafo con las keys como nodos incluyendo 0000
# 2. Calculo todos los pesos (distancias entre keys)
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
    


