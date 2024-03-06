#ifndef _GRAFO_H
#define _GRAFO_H

    #include<iostream>
    #include<list>
    #include <bits/stdc++.h>
    using namespace std;

    typedef struct no NO;

    // typedef struct lista_conectada{
    //     NO *raiz;
    // }LISTA_CONECTADA;

    // struct no{
    //     int valor;
    //     NO *prox;
    // };

    typedef struct grafo{
        int num_vertices;
        list<int>* adj;
    }GRAFO;

    GRAFO* grafo_criar(int vertices);
    void aresta_adicionar(GRAFO* grafo, int vertice1, int vertice2) ;
    void grafo_imprimir(GRAFO* grafo);
    GRAFO *grafo_transposto(GRAFO *grafo);
    void grafo_DFS(GRAFO *grafo, int v, bool visitado[], vector<int> &vetor);

#endif