#include "kosaraju.h"

int main(){
    // Lendo do usuário o número de vértices e o número de arestas
    int num_vertices, num_arestas;
    cin >> num_vertices >> num_arestas;

    // Criando a estrutura do grafo:
    GRAFO *grafo = grafo_criar(num_vertices);

    // Lendo todas as conexões
    for (int i = 0; i < num_arestas; i++){
        // Lendo os vértices que fazem parte de cada conexão
        int vertice1, vertice2;
        cin >> vertice1 >> vertice2;

        // Adicionando essa aresta ao grafo
        aresta_adicionar(grafo, vertice1, vertice2);
    }

    // Encontrando elementos fortemente conexos
    comp_fort_con(grafo);
}