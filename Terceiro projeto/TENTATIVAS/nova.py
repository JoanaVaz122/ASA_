from pulp import LpProblem, LpMaximize, LpVariable, lpSum, LpBinary

def maximizar_lucro(n, brinquedos, max_brinquedos_diarios, pacotes_especiais):
    # Problema
    problema = LpProblem("Maximizar_Lucro", LpMaximize)

    # Variáveis de decisão
    brinquedos_produzidos = [LpVariable(f'x_{i}', lowBound=0, cat=LpBinary) for i in range(n)]
    pacotes_vendidos = [LpVariable(f'y_{i}_{j}_{k}', lowBound=0, cat=LpBinary) for _, _, _, k in pacotes_especiais]

    # Objetivo
    problema += lpSum(brinquedos[i][1] * brinquedos_produzidos[i] for i in range(n)) + \
                lpSum(pacotes_especiais[k][3] * pacotes_vendidos[k] for _, _, _, k in pacotes_especiais)

    # Restrições de Produção
    for i in range(n):
        problema += brinquedos_produzidos[i] <= brinquedos[i][0]

    problema += lpSum(brinquedos_produzidos) <= max_brinquedos_diarios

    # Restrições Pacotes Especiais
    for k, (i, j, l, _) in enumerate(pacotes_especiais):
        # Restrição: Se um brinquedo faz parte do pacote, deve ser produzido
        problema += pacotes_vendidos[k] <= brinquedos_produzidos[i]
        problema += pacotes_vendidos[k] <= brinquedos_produzidos[j]
        problema += pacotes_vendidos[k] <= brinquedos_produzidos[l-1]

        # Restrição: Se o pacote é vendido, todos os brinquedos devem estar presentes
        problema += brinquedos_produzidos[i] >= pacotes_vendidos[k]
        problema += brinquedos_produzidos[j] >= pacotes_vendidos[k]
        problema += brinquedos_produzidos[l-1] >= pacotes_vendidos[k]

    # Restrição: Pelo menos um brinquedo deve ser produzido diariamente
    problema += lpSum(brinquedos_produzidos) >= 1

    # Resolver o problema
    problema.solve()

    # Imprimir resultado
    print(f"Lucro máximo diário: {round(problema.objective.value(), 2)}")

def main():
    t, p, max_brinquedos_diarios = map(int, input().split())

    toys = []
    packages = []

    for _ in range(t):
        values = input().split()
        if len(values) != 2:
            print("Error not two values")
            return
        toys.append((int(values[0]), int(values[1])))

    for _ in range(p):
        values = input().split()
        if len(values) != 4:
            print("Error not four values")
            return
        packages.append((int(values[0]), int(values[1]), int(values[2]), int(values[3])))

    maximizar_lucro(t, toys, max_brinquedos_diarios, packages)

if __name__ == "__main__":
    main()
