#ifndef _GRAFO_H
#define _GRAFO_H

    #include<iostream>
    #include<vector>
    #include<array>
    #include <bits/stdc++.h>

    using namespace std;
    #define GRAFO_INF INT16_MAX
    #define ARESTA_M1 -1    /** marcação de aresta inclusa na árvore mínima*/
    #define ARESTA_M2 -2    /** marcação de aresta nao-inclusa na árvore mínima*/
    typedef struct grafo{
        int num_vertices;
        int **matriz_adj;
    }GRAFO;

    GRAFO *grafo_criar(int num_vertices);
    void grafo_add_aresta(GRAFO *grafo, int v1, int v2, int valor);
    void grafo_imprimir (GRAFO *grafo);
    void grafo_free(GRAFO *grafo);

    void grafo_djikistra(GRAFO *g, int inicio, int *anteriores, int *distancias);

    vector<vector<int>> grafo_sort_arestas(GRAFO *g);
    vector<vector<int>> grafo_kruskal(GRAFO *g);
#endif