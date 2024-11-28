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

for case in range(1, T+1):
    N = len(widths[case-1])

    def skyline_incr_bt(i, last_height, suma_actual, case):
        if i == N:
            if suma_actual >= max_incr_length[0]:
                max_incr_length[0] = suma_actual
            return

        # Incluir la barra actual si es creciente
        if heights[case-1][i] > last_height:
            skyline_incr_bt(i + 1, heights[case-1][i], suma_actual + widths[case-1][i], case)

        # Excluir la barra actual y continuar con la siguiente
        skyline_incr_bt(i + 1, last_height, suma_actual, case)

    def skyline_decr_bt(i, last_height, suma_actual, case):
        if i == N:
            if suma_actual >= max_decr_length[0]:
                max_decr_length[0] = suma_actual
            return

        # Incluir la barra actual si es creciente
        if heights[case-1][i] < last_height:
            skyline_decr_bt(i + 1, heights[case-1][i], suma_actual + widths[case-1][i], case)

        # Excluir la barra actual y continuar con la siguiente
        skyline_decr_bt(i + 1, last_height, suma_actual, case)

    max_incr_length = [float('-inf')]
    max_decr_length = [float('-inf')]

    skyline_incr_bt(0, float('-inf'), 0, case)
    skyline_decr_bt(0, float('+inf'), 0, case)

    if max_incr_length[0] >= max_decr_length[0]:
        print(f"Case {case}. Increasing ({max_incr_length[0]}). Decreasing ({max_decr_length[0]}).")
    else:
        print(f"Case {case}. Decreasing ({max_decr_length[0]}). Increasing ({max_incr_length[0]}).")
