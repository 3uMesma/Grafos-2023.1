#include "grafo.h"

// Objetivo: criar um grafo
GRAFO* grafo_criar(int vertices) {
    GRAFO* novo_grafo = new GRAFO;
    novo_grafo->num_vertices = vertices;
    novo_grafo->adj = new list<int>[vertices];
    return novo_grafo;
}

// Objetivo: adicionar uma aresta
void aresta_adicionar(GRAFO* grafo, int vertice1, int vertice2) {
    grafo -> adj[vertice1].push_back(vertice2);
}

// Busca DFS recursiva
void grafo_DFS(GRAFO *grafo, int v, bool visitado[], vector<int> &vetor){
	// marcando o nó atual como visitado e guardando ele no vetor
	visitado[v] = true;
    vetor.push_back(v);


	// chamar recursivamente até toda a lista de adjacencias ser
    // percorrida
	list<int>::iterator i;
	for (i = grafo->adj[v].begin(); i != grafo->adj[v].end(); ++i)
		if (!visitado[*i])
			grafo_DFS(grafo, *i, visitado, vetor);
}

GRAFO *grafo_transposto(GRAFO *grafo){
    // Criando a estrutura para um grafo composto
	GRAFO *grafo_trans = grafo_criar(grafo->num_vertices);

    // Percorrendo todos os vértices adjacentes
	for (int v = 0; v < grafo->num_vertices; v++){
		list<int>::iterator i;
		for(i = grafo->adj[v].begin(); i != grafo->adj[v].end(); ++i)
		{
			grafo_trans->adj[*i].push_back(v);
		}
	}
	return grafo_trans;
}