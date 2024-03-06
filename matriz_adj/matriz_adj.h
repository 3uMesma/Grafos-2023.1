#ifndef MATRIZ_ADJ_H
#define MATRIZ_ADJ_H
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>

  int **criar_matriz_adj(FILE *arq, int q_vertices, int q_arestas);
  void imprimir_matriz_adj(int **matriz_adj, int q_vertices);
  void apagar_matriz_adj(int **matriz_adj, int q_vertices);
  int *calcular_grau_vertices(int **matriz_adj, int q_vertices);
  void imprimir_grau_vertices(int *grau_vertices, int q_vertices);
  int percorrer_aresta(int **matriz_adj, int q_vertices, int atual);
  bool todas_arestas_percorridas(int **matriz_adj, int q_vertices);
  void eh_euleriano(int **matriz_adj, int q_vertices, int q_arestas);

#endif