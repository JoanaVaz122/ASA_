import pulp

def maximizar_lucro(t, p, max_brinquedos, brinquedos, pacotes):
    # Criação do problema de maximização
    problema = pulp.LpProblem("Maximizar_Lucro", pulp.LpMaximize)

    # Variáveis de decisão para a quantidade de cada brinquedo
    quantidade_brinquedo = [pulp.LpVariable(f"x{i}", lowBound=0, cat=pulp.LpInteger) for i in range(1, t+1)]

    # Variáveis de decisão para a quantidade de cada pacote especial
    quantidade_pacote = [pulp.LpVariable(f"p{i}", lowBound=0, cat=pulp.LpInteger) for i in range(1, p+1)]

    # Função objetivo
    problema += pulp.lpSum(brinquedos[i-1][0] * quantidade_brinquedo[i-1] for i in range(1, t+1)) + \
                 pulp.lpSum(pacotes[i-1][3] * quantidade_pacote[i-1] for i in range(1, p+1))

    # Restrições de capacidade de produção de cada brinquedo
    for i in range(1, t+1):
        problema += quantidade_brinquedo[i-1] <= brinquedos[i-1][1]

    # Restrição de capacidade total de produção
    problema += pulp.lpSum(quantidade_brinquedo) <= max_brinquedos

    # Restrições para os pacotes especiais
    for i in range(1, p+1):
        # A quantidade de cada pacote deve ser maior ou igual a zero
        problema += quantidade_pacote[i-1] >= 0
        # A quantidade total de brinquedos em cada pacote deve ser igual a 3
        problema += pulp.lpSum([quantidade_brinquedo[j-1] for j in pacotes[i-1][:3]]) >= 3 * quantidade_pacote[i-1]
        # Garante que a quantidade de cada pacote não seja maior do que 1
        problema += quantidade_pacote[i-1] <= 1

    # Resolva o problema
    problema.solve()

    # Resultados
    resultado = {
        "Lucro Máximo": pulp.value(problema.objective),
        "Quantidade de cada Brinquedo": [pulp.value(var) for var in quantidade_brinquedo],
        "Quantidade de cada Pacote": [pulp.value(var) for var in quantidade_pacote]
    }

    return resultado

# Exemplo de utilização com os dados de entrada fornecidos
t, p, max_brinquedos = 5, 2, 150
brinquedos = [(50, 27), (30, 33), (45, 30), (40, 37), (35, 35)]
pacotes = [(1, 3, 5, 130), (2, 3, 4, 130)]

# Resolver o problema
resultado = maximizar_lucro(t, p, max_brinquedos, brinquedos, pacotes)

# Imprimir resultados
print("Lucro Máximo:", resultado["Lucro Máximo"])
print("Quantidade de cada Brinquedo:", resultado["Quantidade de cada Brinquedo"])
print("Quantidade de cada Pacote:", resultado["Quantidade de cada Pacote"])
