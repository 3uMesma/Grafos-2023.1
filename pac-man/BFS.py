#chamando nossa própria biblioteca de grafos
import grafo

vertice = grafo.Vertice

cor_visitado_uma_vez = "cinza"
cor_visitado_duas_vezes = "preto"
cor_nao_visitado = "branco"
dir_esq = "E"
dir_cma = "C"
dir_dir = "D"
dir_bxo = "B"

# função auxiliar para a busca BFS
def visita_bfs(G, V):
    fila = [] # Fila para percorrer os vértices

    #pinta esse vértice como cinza e coloca a distância dele como zero, pois é dele que começamos
    V.cor = cor_visitado_uma_vez
    V.distancia = 0
    
    #adiciona na fila, no final
    fila.append(G[id])

    #enquanto a fila não estiver vazia, ir percorrendo os nós
    while(len(fila) != 0):
        #tira o nó da lista, ou seja, tira o primeiro elemento da fila
        V = fila.pop(0)
        #se ele tiver vértices adjacentes, continuamos a busca
        if (len(V.vizinhos) != 0):
            #Enquanto não for o fim da lista de ajacencias
            for id in V.vizinhos:
                #se aquele vértice não tiver sido visitado ainda
                if (G[id].cor == cor_nao_visitado):
                    #ele vai ser visitado e mudar de cor
                    G[id].cor = cor_visitado_uma_vez
                    G[id].distancia = V.distancia + 1
                    G[id].status["antecessor"] = V.id
                    fila.append(G[id].id)
    #mudar a cor para preto, pois já percorremos ele por completo
    V.cor = cor_visitado_duas_vezes


# Função principal BFS
def busca_largura(G, V, x_fantasma, y_fantasma):
    #definindo os vértices com as características default, essenciais para a execução do programa
    for V in G.vertices:
        V.cor = cor_nao_visitado
        V.distancia = -1
        V.status["antecessor"] = -1

    # fazer a busca enquanto ainda houverem vértices na cor branca e o vértice em função não for um fantasma
    for V in G.vertices:
        if (V.status["fantasma"]):
            break
        if (V.cor == cor_nao_visitado):
            visita_bfs(G,V)

    #salvando o id do fantasma
    id_fantasma = V.id
    
    #sendo o fantasma, vamos fazer a lógica para encontrar o próximo passo
    id_antecessor = V.status["antecessor"]
    while(V.status["fantasma"] != V.status["Pacman"]):
        id_antecessor = G[id_antecessor].status["antecessor"]

    #Quando ele achar o pŕoximo vértice que o Pacman deve percorrer, ele deve ver que direção isso significa e retornar
    # para verificar a direção, usamos uma função do TAD grafos
    return G[id_fantasma] >> G[id_antecessor] #MUDAR PELO FUNÇÃO DO MIGUEL
