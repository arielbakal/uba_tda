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
    
def skyline_incr(i, width):
    if i == 0 or width == 0: # Si recorri todo el skyline
        return 0
    
    if M_incr[i][width] == []: # Si no tengo asignado valor en memoria, lo calculo

        # if i == 1:
        #     return widths[0][i-1]
        # else:

        if heights[0][i-2] <= heights[0][i-1]: # Verifico si el skyline es increasing

            # Asigno el maximo entre las recursiones de excluir o incluir el elemento
            M_incr[i][width] = max(skyline_incr(i-1, width), skyline_incr(i-1, width - widths[0][i-1]) + widths[0][i-1])

        else: # De no ser increasing, sigo recorriendo
            M_incr[i][width] = skyline_incr(i-1, width)    

    return M_incr[i][width]

N = len(widths[0])

widths_sum = sum(widths[0])

# Inicializo memoria 
M_incr = [[] * (widths_sum + 1) for _ in range(N + 1)]
M_decr = [[] * (widths_sum + 1) for _ in range(N + 1)]

max_incr_length = skyline_incr(N, widths_sum)

print(M_incr)
print(max_incr_length)