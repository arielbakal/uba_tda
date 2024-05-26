# Notes: impl graph and priorityqueue  

T = int(input()) # test cases
keys_global = []

for _ in range(T):
    safe = input().split()
    N = int(safe[0])
    keys = [safe[i] for i in range(1, N+1)]
    keys = [tuple(int(d) for d in key) for key in keys] 
    keys_global.append(keys)
    


