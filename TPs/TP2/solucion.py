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
    
def skyline_incr(i, last_height, total_width):
    if i == N: # Si recorri todo el skyline
        return 0
    
    if M_incr[i][total_width] == -1:

        if heights[0][i] > last_height: # Verifico si el skyline es increasing

            # Asigno el maximo entre las recursiones de excluir o incluir el elemento
            M_incr[i][total_width] = max(skyline_incr(i+1, last_height, total_width), skyline_incr(i+1, heights[0][i], total_width + widths[0][i]) + widths[0][i])

        else: # De no ser increasing, sigo recorriendo
            M_incr[i][total_width] = skyline_incr(i+1, last_height, total_width)    

    return M_incr[i][total_width]

N = len(widths[0])

widths_sum = sum(widths[0])

# Inicializo memoria 
M_incr = [[-1] * (widths_sum + 1) for _ in range(N + 1)]
M_decr = [[-1] * (widths_sum + 1) for _ in range(N + 1)]

max_incr_length = skyline_incr(0, float('-inf'), 0)

print(M_incr)
print(max_incr_length)