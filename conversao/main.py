import pprint
from tabela_transicao_afnd import Si, Fi, Ti, alfabeto, tabela_i

# S_inicial_nd = {0}
# F = {10}
# T = set(range(0, 11))

# sigma = {"a", "b"}
# tabela = {
#     0: { "epsilon": {1, 7}, "a": set(), "b": set() },
#     1: { "epsilon": {2, 4}, "a": set(), "b": set() },
#     2: { "epsilon": set(), "a": {3}, "b": set() },
#     3: { "epsilon": {6}, "a": set(), "b": set() },
#     4: { "epsilon": set(), "a": set(), "b": {5} },
#     5: { "epsilon": {6}, "a": set(), "b": set() },
#     6: { "epsilon": {1, 7}, "a": set(), "b": set() },
#     7: { "epsilon": set(), "a": {8}, "b": set() },
#     8: { "epsilon": set(), "a": set(), "b": {9} },
#     9: { "epsilon": set(), "a": set(), "b": {10} },
#     10: { "epsilon": set(), "a": set(), "b": set() }
# }


S_inicial_nd, F, T, sigma, tabela = Si, Fi, Ti, alfabeto, tabela_i


'''
=-=-=-=-=-=-=-=-=-=-=-= FUNÇÃO PARA CONVERTER O AFND EM AFD =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
----------------------- FUNÇÕES AUXILIARES ----------------------------------------------
'''
def move(estado, caractere):
    return tabela[estado][caractere]

def moveT(estados, caractere):
    T = set()
    for estado in estados:
        fecho = e_closure({estado})
        for e in fecho:
            ss = move(e, caractere)
            for elemento in ss:
                T.add(elemento)

    return T


'''
------------------------------- FUNÇÃO FECHO ---------------------------------------------
'''
def e_closure(T):
    P = list()
    Fecho = set()

    for t in T:
        P.append(t)
        Fecho.add(t)

    while P:
        t = P.pop() # desempilha o topo
        for s in move(t, "epsilon"):
            if s not in S_inicial_nd:
                Fecho.add(s)
                P.append(s)

    return Fecho


'''
------------------------------ VARIÁVEIS GLOBAIS -----------------------------------------
'''
tabela_transicao = {}
S_inicial_d = set()
F_d = set()


'''
------------------------------- FUNÇÃO DE CONVERSÃO --------------------------------------
'''
def converte():
    S_d = [e_closure(S_inicial_nd)]
    S_inicial_d.add(tuple(e_closure(S_inicial_nd)))
    M = set()
    while any(tuple(T) not in M for T in S_d): 
        T = next(T for T in S_d if tuple(T) not in M)
        M.add(tuple(T))
        
        for simbolo in sigma:
            T_ = e_closure( moveT(T, simbolo) )
            if T_ not in S_d:
                S_d.append(T_)
            tabela_transicao[tuple(T), simbolo] = T_

    for T in S_d:
        for s in T:
            if s in F:
                F_d.add(tuple(T))


'''
--------------------------- FUNÇÃO PARA ORGANIZAR A TABELA ---------------------------
'''
# Função para transformar a tabela de transição
def transformar_tabela(tabela_transicao):
    nova_tabela = {}
    
    for (estado, simbolo), destino in tabela_transicao.items():
        if estado not in nova_tabela:
            nova_tabela[estado] = {}
        nova_tabela[estado][simbolo] = destino
    
    return nova_tabela


'''
--------------------------- BLOCO PRINCIPAL -------------------------------------------
'''
converte()
estados_d = set(e[0] for e in set(tabela_transicao.keys()))
tabela_organizada = transformar_tabela(tabela_transicao)

print("Estados finais:",F_d)
print("Estado inicial:",S_inicial_d)
print("Sigma:",sigma,"\n")
for i in tabela_organizada.keys():
    print(f"{i}\n{tabela_organizada[i]}\n\n")

'''
    Execute com: python3 main.py > diagrama_det.txt
    Coloque esse nome para o arquivo de saída, pois é o
    nome que outros programas estão usando para acessar
    esse arquivo gerado.
    
    TODO
        (1) Alterar o código de modo a criar um arquivo, e não
        depender do redirecionamento de saída;
        
        (2) Adicionar as convenções de Python (if __name__ == '__main__').
'''