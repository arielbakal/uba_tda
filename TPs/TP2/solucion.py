T = int(input())
heights = []
widths = []

# Recibo inputs
for _ in range(T):
    N = int(input())
    heights_temp = [int(x) for x in input().split()]
    heights.append(heights_temp)
    widths_temp = [int(x) for x in input().split()]
    widths.append(widths_temp)
    
def skyline_incr(i, last_height, total_width, case):
    if i == N: # Si recorri todo el skyline
        return 0
    
    if M_incr[i][last_height] == -1: # Verifico si ya tengo solucion al subproblema

        if heights[case-1][i] > last_height: # Verifico si el skyline es creciente

            # Asigno el maximo entre las recursiones de excluir o incluir el elemento
            M_incr[i][last_height] = max(skyline_incr(i+1, last_height, total_width, case), skyline_incr(i+1, heights[case-1][i], total_width + widths[case-1][i], case) + widths[case-1][i])

        else: # De no ser creciente, sigo recorriendo
            M_incr[i][last_height] = skyline_incr(i+1, last_height, total_width, case)    

    return M_incr[i][last_height]

def skyline_decr(i, last_height, total_width, case): # Igual que skyline_incr pero distinta comparacion
    if i == N: 
        return 0
    if M_decr[i][last_height] == -1:
        if heights[case-1][i] < last_height: 
            M_decr[i][last_height] = max(skyline_decr(i+1, last_height, total_width, case), skyline_decr(i+1, heights[case-1][i], total_width + widths[case-1][i], case) + widths[case-1][i])
        else:
            M_decr[i][last_height] = skyline_decr(i+1, last_height, total_width, case)    
    return M_decr[i][last_height]

for case in range(1, T+1):
    N = len(widths[case-1])
    widths_sum = sum(widths[case-1])

    # Inicializo memoria 
    M_incr = [[-1] * (max(heights[case-1]) + 2) for _ in range(N + 1)]
    M_decr = [[-1] * (max(heights[case-1]) + 2) for _ in range(N + 1)]

    max_incr_length = skyline_incr(0, 0, 0, case)
    max_decr_length = skyline_decr(0, max(heights[case-1]) + 1, 0, case)

    if max_incr_length >= max_decr_length:
        print(f"Case {case}. Increasing ({max_incr_length}). Decreasing ({max_decr_length}).")
    else:
        print(f"Case {case}. Decreasing ({max_decr_length}). Increasing ({max_incr_length}).")
