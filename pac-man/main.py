import BFS
import grafo
#main só pra testar

matriz = [
    [0, 0, 0],
    [0, 0, 0],
    [0, 0, 0]
]

#criando uma matriz com valores que eu quero:
G = grafo.grafo_create(matriz)

#determinando qual vertice é o fantasma
G[(0,1)].status["fantasma"] = 1

