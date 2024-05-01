from pulp import LpProblem, LpMaximize, LpVariable, lpSum

class Brinquedo:
    def __init__(self, lucro, capacidade):
        self.lucro = lucro
        self.capacidade = capacidade

def ler_entrada():
    t, p, max_prod = map(int, input().split())
    
    brinquedos = []
    for _ in range(t):
        lucro, capacidade = map(int, input().split())
        brinquedos.append(Brinquedo(lucro, capacidade))

    pacotes_especiais = []
    for _ in range(p):
        i, j, k, lucro = map(int, input().split())
        produtos = (i, j, k)
        pacotes_especiais.append((lucro, produtos))

    return t, p, max_prod, brinquedos, pacotes_especiais

def resolver_problema_lp(brinquedos, pacotes_especiais, max_prod):
    
    problema = LpProblem("MaximizarLucro", LpMaximize)

    quantidades = [LpVariable(f"x{i}", lowBound=0, cat="Integer") for i in range(1, len(brinquedos) + 1)]
    
    # Adicionar variáveis de decisão para os pacotes especiais
    pacotes_vars = [LpVariable(f"p{i}", cat="Binary") for i in range(1, len(pacotes_especiais) + 1)]

    # Adicionar restrições para os brinquedos individuais
    for i in range(1, len(brinquedos) + 1):
        problema += quantidades[i - 1] <= max_prod  # Restrição de produção diária

    # Adicionar restrições para os pacotes especiais
    for i, (lucro, produtos) in enumerate(pacotes_especiais):
        problema += lpSum([quantidades[p - 1] for p in produtos]) >= pacotes_vars[i]  # Restrição de escolher ou não um pacote especial

    # Adicionar função objetivo
    problema += lpSum([brinquedos[i - 1].lucro * quantidades[i - 1] for i in range(1, len(brinquedos) + 1)]) + lpSum([lucro * pacotes_vars[i - 1] for i, (lucro, _) in enumerate(pacotes_especiais)])

    problema.solve()

    return int(round(problema.objective.value()))

def main():
    t, _, max_prod, brinquedos, pacotes_especiais = ler_entrada()

    # Calcular o lucro máximo usando PuLP
    lucro_max = resolver_problema_lp(brinquedos, pacotes_especiais, max_prod)

    print("Lucro máximo diário:", lucro_max)

if __name__ == "__main__":
    main()
