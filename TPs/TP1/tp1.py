T = int(input()) # Leer el número de casos de prueba
jugadores = [] # Lista para almacenar la información de los jugadores

# Leer la información de los jugadores
for _ in range(T):
    jugadores_temp = []
    for i in range(10):
        nombre, ataque, defensa = input().split()
        jugadores_temp.append((nombre, int(ataque), int(defensa)))
    jugadores.append(jugadores_temp)

for caso in range(1, T + 1): # Resolver caso por caso
    sample = jugadores[caso-1]

    def formacion_bt(i, cant_jugadores, formacion_actual, suma_actual, suma_max):
        if cant_jugadores == 5:  # Caso base: llegue al límite de solo 5 atacantes
            actualizar_max(formacion_actual, suma_actual, suma_max) # Actualizo la lista de combinaciones que maximizan y la suma
            return
        if i == len(sample):
            return

        # Incluir jugador y explorar
        formacion_bt(i + 1, cant_jugadores + 1, formacion_actual + [sample[i]], suma_actual + sample[i][1], suma_max)
        # Excluir jugador y explorar
        formacion_bt(i + 1, cant_jugadores, formacion_actual, suma_actual, suma_max)

    def actualizar_max(formacion_actual, suma_actual, suma_max):
        if suma_actual > suma_max[0]:  # Si encontramos una nueva combinación que maximiza el valor de ataque
            atacantes_comb_max.clear()  # Limpiar la lista de combinaciones anteriores
            atacantes_comb_max.append(formacion_actual[:])  # Agregar esta combinación como la única que maximiza hasta ahora
            suma_max[0] = suma_actual  # Actualizar la suma máxima de ataque
        elif suma_actual == suma_max[0]:  # Si la suma actual es igual a la suma máxima
            atacantes_comb_max.append(formacion_actual[:])  # Agregar esta combinación a la lista de combinaciones que maximizan el valor de ataque

    # Inicializo result
    atacantes_final = []
    defensores_final = []

    # Inicializo combinaciones
    atacantes_comb_max = []
    defensores_comb_max = []

    # Inicio backtracking
    suma_max = [float('-inf')]
    formacion_bt(0, 0, [], 0, suma_max) # Backtracking

    # Chequeo si hay combinaciones multiples
    # De serlo, decido en base a la suma de las defensas
    if len(atacantes_comb_max) > 1:
        suma_defensa_max = 0
        for combinacion in atacantes_comb_max: # Recorro las combinaciones de atacantes
            defensores_temp = list(filter(lambda jugador: jugador not in combinacion, sample)) # Armo lista de defensores por combinacion de atacantes
            suma_defensa_temp = sum([jugador[2] for jugador in defensores_temp]) # Sumatoria del valor de defensa de los defensores
            # Verifico si encuentro una o mas defensas que maximicen
            if suma_defensa_temp > suma_defensa_max:
                suma_defensa_max = suma_defensa_temp
                defensores_comb_max.clear()
                defensores_comb_max.append(defensores_temp)
            elif suma_defensa_temp == suma_defensa_max:
                defensores_comb_max.append(defensores_temp)
        defensores_final = min(defensores_comb_max)[0] # De haber varias defensas que maximicen, elijo una por orden alfabetico 
    else: # Unica combinacion de atacantes, simplemente creo lista de defensores
        defensores_temp = []
        for jugador in sample:
            if jugador not in atacantes_comb_max[0]:
                defensores_temp.append(jugador)
        defensores_comb_max.append(defensores_temp)

    # Defino mi result y las ordeno alfabeticamente
    defensores_final = sorted(defensores_comb_max[0])
    atacantes_final = sorted(list(filter(lambda jugador: jugador not in defensores_final, sample)))

    print(f"Case {caso}:")
    print("(", ", ".join([jugador[0] for jugador in atacantes_final]), ")", sep="")
    print("(", ", ".join([jugador[0] for jugador in defensores_final]), ")", sep="")