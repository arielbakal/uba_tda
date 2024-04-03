def formacion_bt(i, cant_jugadores, formacion_actual, suma_actual, suma_max, atacantes_comb_max, defensores_comb_max, sample):
    if cant_jugadores == 5:  # Caso base: llegue al límite de solo 5 atacantes
        actualizar_max(formacion_actual, suma_actual, suma_max, atacantes_comb_max, defensores_comb_max, sample)
        return
    if i == len(sample):
        return

    # Incluir jugador y explorar
    formacion_bt(i + 1, cant_jugadores + 1, formacion_actual + [sample[i]], suma_actual + sample[i][1], suma_max, atacantes_comb_max, defensores_comb_max, sample)
    # Excluir jugador y explorar
    formacion_bt(i + 1, cant_jugadores, formacion_actual, suma_actual, suma_max, atacantes_comb_max, defensores_comb_max, sample)

def actualizar_max(formacion_actual, suma_actual, suma_max, atacantes_comb_max, defensores_comb_max, sample):
    if suma_actual > suma_max[0]:  # Si encontramos una nueva combinación que maximiza el valor de ataque
        atacantes_comb_max.clear()  # Limpiar la lista de combinaciones anteriores
        atacantes_comb_max.append((formacion_actual[:], suma_actual))  # Agregar esta combinación como la única que maximiza hasta ahora
        suma_max[0] = suma_actual  # Actualizar la suma máxima de habilidades de ataque
    elif suma_actual == suma_max[0]:  # Si la suma actual es igual a la suma máxima
        atacantes_comb_max.append((formacion_actual[:], suma_actual))  # Agregar esta combinación a la lista de combinaciones que maximizan el valor de ataque

# función para obtener los defensores
def obtener_defensores(atacantes, sample):
    defensores = []
    for jugador in sample:
        if jugador not in atacantes:
            defensores.append(jugador)
    return defensores

# función para imprimir el resultado
def imprimir_resultado(atacantes, defensores, caso):
    print(f"Case {caso}:")
    print("(", ", ".join(sorted([jugador[0] for jugador in atacantes])), ")", sep="")
    print("(", ", ".join(sorted([jugador[0] for jugador in defensores])), ")", sep="")

# función principal para procesar cada caso de prueba
def procesar_caso(caso, sample):
    atacantes_comb_max = []  # Lista para almacenar la combinación de atacantes que maximizan el valor de ataque
    suma_max = [float('-inf')]  # Lista para almacenar la suma máxima de habilidades de ataque encontrada
    formacion_bt(0, 0, [], 0, suma_max, atacantes_comb_max, [], sample)  # Ejecutar el backtracking

    atacantes_optimos = atacantes_comb_max[0][0]  # Tomar la primera combinación de atacantes (se asume que hay al menos una)
    defensores_optimos = obtener_defensores(atacantes_optimos, sample)  # Obtener los defensores correspondientes
    imprimir_resultado(atacantes_optimos, defensores_optimos, caso)  # Imprimir el resultado

# Leer el número de casos de prueba
T = int(input())
jugadores = [] # Lista para almacenar la información de los jugadores
# Leer la información de los jugadores
for _ in range(T):
    jugadores_temp = []
    for i in range(10):
        nombre, ataque, defensa = input().split()
        jugadores_temp.append((nombre, int(ataque), int(defensa)))
    jugadores.append(jugadores_temp)

# Procesar cada caso de prueba
for caso in range(1, T + 1):
    procesar_caso(caso, jugadores[caso-1])  # Procesar el caso de prueba actual
