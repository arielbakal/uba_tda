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

def skyline_incr_bt(i, last_height, suma_actual):
    if i == N:
        if suma_actual >= suma_max[0]:
            suma_max[0] = suma_actual
        return

    # Incluir la barra actual si es creciente
    if heights[0][i] > last_height:
        skyline_incr_bt(i + 1, heights[0][i], suma_actual + widths[0][i])

    # Excluir la barra actual y continuar con la siguiente
    skyline_incr_bt(i + 1, last_height, suma_actual)

# Inicio backtracking
suma_max = [float('-inf')]
skyline_incr_bt(0, float('-inf'), 0) # Backtracking
    
N = len(widths[0])

widths_sum = sum(widths[0])

print(suma_max)