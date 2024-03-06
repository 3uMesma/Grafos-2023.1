/**
 * Integrantes:
 *  - Miguel Prates Ferreira de Lima Cantanhede - 13672745
 *  - Amanda Kasat Baltor - 13727210
 *  - Lucas Issao Omati - 13673090
*/

#include "grafo.h"

int main(){
    int num_vertices, num_arestas, vertice_final;
    cin >> num_vertices >> num_arestas;

    GRAFO *grafo = grafo_criar(num_vertices);

    /** Faz a leitura do grafo **/
    int vertice1, vertice2, peso;
    for (int i = 0; i < num_arestas; i++){
        cin >> vertice1 >> vertice2 >> peso;
        grafo_add_aresta(grafo, vertice1, vertice2, peso);
    }
    cin >> vertice_final;
    
    /** Aplica o algoritmo de kruskal, retornando um vetor
     * de arestas que conectam todos os nós e que juntas têm
     * o menor peso **/
    vector<vector<int>> geradora_minima = grafo_kruskal(grafo);

    /** Soma todos os pesos para obter o peso do caminhão sem o VIP **/
    int peso_semVIP = 0;
    for(int i=0;i<(int)geradora_minima.size();i++){peso_semVIP+=geradora_minima[i][2];}



    /** Aplica o algoritmo de djikistra com vetores que guardam 
     * as distancia de todos os vertices do vertice inicial e 
     * seus respectivos vertices anteriores **/
    int distancia[num_vertices];
    int anteriores[num_vertices];
    grafo_djikistra(grafo, 0, anteriores, distancia);
    // for(int i=0;i<num_vertices;i++){
    //     printf("i[%2d]: %2d %2d\n",i,distancia[i],anteriores[i]);
    // }

    /** Vai adicionando os pesos usados durante o caminho 
     * (faz de trás pra frente de acordo com os 'anteriores') 
     * Quando o 'anteriores' chega em -1, quer dizer que ele voltou
     * ao vértice 0 (ponto de partida).
     * **/
    int vertice_atual = vertice_final;
    int vertices_passados = 0;
    while(anteriores[vertice_atual] != -1 && vertices_passados < num_vertices){
        vertice_atual = anteriores[vertice_atual];
        vertices_passados++;
    }
    
    int peso_comVIP;
    if(vertices_passados <= num_vertices){
        peso_comVIP = distancia[vertice_final] * (num_vertices - vertices_passados - 1);
    }else{
        /** Caso em que ele não conseguiu chegar no vértice desejado **/
        peso_comVIP = GRAFO_INF;
    }
    
    if(peso_semVIP<peso_comVIP){
        printf("PADRAO\n%d\n",peso_semVIP);
    }else if(peso_semVIP>peso_comVIP){
        printf("VIP\n%d\n",peso_comVIP);
    }else{
        printf("NDA\n%d\n",peso_comVIP);
    }
    grafo_free(grafo);
}