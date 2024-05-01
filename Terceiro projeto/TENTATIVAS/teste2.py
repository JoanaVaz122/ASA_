from pulp import LpProblem, LpMaximize, LpVariable, lpSum

def solve_max_profit(input_data):
    # Parse do input
    lines = input_data.strip().split('\n')
    t, p, max_brinquedos = map(int, lines[0].split())

    lucro_produtos = [tuple(map(int, line.split())) for line in lines[1:t+1]]
    lucro_pacotes = [tuple(map(int, line.split()[1:])) for line in lines[t+1:t+p+1]]

    # Criação do problema de programação linear
    prob = LpProblem("Maximize_Profit", LpMaximize)

    # Variáveis de decisão
    x = [LpVariable(f"x{i}", lowBound=0, cat="Integer") for i in range(1, t+1)]
    y = [LpVariable(f"y{i}", lowBound=0, cat="Binary") for i in range(1, p+1)]

    # Função objetivo
    prob += lpSum(x[i-1] * lucro_produtos[i-1][0] for i in range(1, t+1)) + lpSum(y[j-1] * lucro_pacotes[j-1][0] for j in range(1, p+1))

    # Restrições de produção diária
    prob += lpSum(x) <= max_brinquedos

    for i in range(t):
        prob += x[i] <= lucro_produtos[i][1]

    # Restrições de pacotes
    for j in range(p):
        i, k = lucro_pacotes[j][1], lucro_pacotes[j][2]

        # Adiciona variáveis de decisão para os pacotes
        z = LpVariable(f"z{j}", lowBound=0, cat="Binary")

        # Adiciona restrições para garantir que o pacote seja escolhido
        prob += z <= x[i-1]
        prob += z <= x[j-1]
        prob += z <= x[k-1]
        prob += x[i-1] + x[j-1] + x[k-1] - 2 * z >= 0  # Restrição para garantir que z seja 1 se pelo menos dois xi forem 1

        # Função objetivo para maximizar o lucro dos pacotes
        prob += z * lucro_pacotes[j][0]




    # Resolve o problema
    prob.solve()

    # Retorna o resultado
    return int(lpSum(x[i-1].value() * lucro_produtos[i-1][0] for i in range(1, t+1)).value())

# Exemplo de uso
input_data_1 = """5 2 150
50 27
30 33
45 30
40 37
35 35
1 3 5 130
2 3 4 130"""
output_1 = solve_max_profit(input_data_1)
print(output_1)  # Saída esperada: 6440

input_data_2 = """5 2 15
50 27
30 33
45 30
40 37
35 35
1 3 5 129
2 3 4 130"""
output_2 = solve_max_profit(input_data_2)
print(output_2)  # Saída esperada: 750
