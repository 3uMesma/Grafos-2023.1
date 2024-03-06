#include "grafo.h"

/* Objetivo: inicializar matriz*/
GRAFO *grafo_criar(int num_vertices){
    /* Declarando estrutura*/
    GRAFO *grafo = new GRAFO;

    /* Definindo o número de vértices*/
    grafo->num_vertices = num_vertices;

    /* Alocando a matriz de adjacencias do grafo*/
    grafo->matriz_adj = new int*[num_vertices];
    for (int i = 0; i < num_vertices; ++i) {
        grafo->matriz_adj[i] = new int[num_vertices];
    }

    /* Pré-declarando todos os números como GRAFO_INF*/
    for (int i = 0; i < num_vertices; i++){
        for (int j = 0; j < num_vertices; j++){
            grafo->matriz_adj[i][j] = GRAFO_INF;
        }
    }

    return grafo;
}

/* Objetivo: adicionar aresta*/
void grafo_add_aresta(GRAFO *grafo, int v1, int v2, int valor){
    /* Por ser uma matriz, define nos dois lugares*/
    grafo->matriz_adj[v1][v2] = valor;
    grafo->matriz_adj[v2][v1] = valor;
}


/* Objetivo: imprimir matriz*/
void grafo_imprimir (GRAFO *grafo){
    for (int i = 0; i < grafo->num_vertices; i++){
        for (int j = 0; j < grafo->num_vertices; j++){
            if(grafo->matriz_adj[i][j]==GRAFO_INF){
                cout << "X" << " ";    
            }else{
                cout << grafo->matriz_adj[i][j] << " ";
            }
            
        }
        cout << endl;
    }
}

/* Objetivo: apagar grafo (liberar memória)*/
void grafo_free(GRAFO *grafo){
    for (int i = 0; i < grafo->num_vertices; i++) {
        delete[] grafo->matriz_adj[i];
    }
    delete[] grafo->matriz_adj;
}


/** Função para verificar se um inteiro está em um vetor de inteiros **/
bool vector_contains(vector<int> vec, const int& elem){
    return find(vec.begin(),vec.end(),elem)!=vec.end();
}
/** Função que adiciona todo o conteúdo de vec2 em vec1 **/
void vector_extend(vector<int>* vec1, vector<int>* vec2){
    for(int i=0;i<(int)(*vec2).size();i++){
        (*vec1).push_back((*vec2)[i]);
    }
}
/** Função que retira uma floresta do vetor de florestas **/
void grafo_remove_floresta(vector<vector<int>> *vec, int index){
    vector<vector<int>>::iterator it = (*vec).begin();
    advance(it,index);
    (*vec).erase(it);
}


vector<vector<int>> grafo_sort_arestas(GRAFO *g){
    vector<vector<int>> arestas;// = new vector<array<int,2>>();
    /** Fazendo uma lista de arestas **/
    for(int i=0;i<g->num_vertices;i++){
        for(int j=0;j<g->num_vertices;j++){
            if(i!=j && g->matriz_adj[i][j]!=GRAFO_INF){
                arestas.push_back(vector<int> {i,j,g->matriz_adj[i][j]});
            }
        }
    }
    
    /** Ordenando essas arestas pelo peso*/
    sort(arestas.begin(), arestas.end(),
            [](const vector<int>& a, const vector<int>& b) {
                return a[2] < b[2];
    });
    return arestas;
}

/** Função que faz uma busca de um vértice em várias florestas,
 * retornando o índice da floresta que ele apareceu (-1 caso não apareça) **/
int grafo_procura_nas_arvores(vector<vector<int>> florestas, int vertice){
    for(int i=0;i<(int)florestas.size();i++){
        if(vector_contains(florestas[i],vertice)){
            /** Se a árvore contiver o vértice, retorna o índice **/
            return i;    
        }
    }
    /** caso não tenha encontrado nenhuma, retorna -1 **/
    return -1;
}

/** implementação do kruskal **/
vector<vector<int>> grafo_kruskal(GRAFO *g){
    vector<vector<int>> geradora_minima;

    /** guarda todas as florestas do grafo 
     *  As florestas são 'vector<int>' e o 'int'
     *  guardado dentro significa 1 árvore (um vértice)
     *  
     *  No começo, todas as árvores começam com 1 nó dentro
     * */
    vector<vector<int>> florestas;
    for(int i=0;i<g->num_vertices;i++){
        florestas.push_back(vector<int> {i});
    }

    /** Cria o vetor que guarda as arestas ordenadas **/
    vector<vector<int>> arestas = grafo_sort_arestas(g);
    
    int f1,f2,f_troca;/** auxiliares de índice das florestas **/
    for(int i=0;i<(int)arestas.size();i++){
        /** Verifica a qual floresta pertence os dois vértices da aresta **/
        f1 = grafo_procura_nas_arvores(florestas, arestas[i][0]);
        f2 = grafo_procura_nas_arvores(florestas, arestas[i][1]);
        if(f1!=f2){
            /** Pequeno if para otimizar e não ficar transferindo
             * um monte de árvores o tempo todo, fazendo com que
             * o tamanho de f1 sempre seja maior que o de f2*/
            if(florestas[f1].size()<florestas[f2].size()){
                f_troca = f1;
                f1 = f2;
                f2 = f_troca;
            }

            /** Se eles conectarem florestas diferentes, as florestas
             * se juntam em uma só (f1 += f2 e f2 é deletado) e
             * a aresta é guardada na geradora mínima **/
            vector_extend(&florestas[f1],&florestas[f2]);
            grafo_remove_floresta(&florestas,f2);
            geradora_minima.push_back(arestas[i]);
        }
    }
    return geradora_minima;   
}



// Procura o vertice com a menor distância e que nao tenha sido visitado
int grafo_menor_distancias(int *distancias, int *visitados, int numero_vertices){
    int menor_idx = 0;
    int menor_valor = GRAFO_INF;
    bool nao_tem_nenhum=true;
    for(int i = 0; i < numero_vertices; i++){
        if(distancias[i] != GRAFO_INF && visitados[i] == 0){
            if(menor_valor >= distancias[i]){
                menor_idx = i;
                menor_valor = distancias[i];
                nao_tem_nenhum=false;
            }
        }
    }
    if(nao_tem_nenhum){menor_idx=-1;}
    return menor_idx;
}

/** Implementação de um Djikistra **/
void grafo_djikistra(GRAFO *g, int inicio, int *anteriores, int *distancias){
    int contador, numero_vertices, *visitados, v;
    contador = g->num_vertices;
    numero_vertices = g->num_vertices;
    visitados = (int *)malloc(numero_vertices * sizeof(int));

    // aloca os vetores que guardam os vertices anteriores, a distancias e se o vertice ja foi visitado
    for(int i = 0; i < numero_vertices; i++){
        anteriores[i] = -1;
        distancias[i] = GRAFO_INF;
        visitados[i] = 0;
    }
    distancias[inicio] = 0;

    // condicao para ele verificar pelo menos todas as possibilidades que conseguir
    while(contador > 0){
        /** v é o vértice com a menor "distancia" e que ainda não foi visitado **/
        v = grafo_menor_distancias(distancias, visitados, numero_vertices);

        /** Se não tiver nenhum vértice que ainda não tenha sido visitado **/
        if(v == -1){break;}
        visitados[v] = 1;

        /**atualiza a distancias dos vizinhos e seu anterior**/
        for(int i = 0; i < numero_vertices; i++){
            if(g->matriz_adj[v][i] != GRAFO_INF){
                /** Se existir um caminho entre v e i **/
                if(distancias[i] == GRAFO_INF){
                    /** Se ainda não tiver computado a distancia desse vértice i antes**/
                    distancias[i] = ((distancias[v]==GRAFO_INF)?0:distancias[v]) + g->matriz_adj[v][i];
                    anteriores[i] = v;
                } else if(distancias[i] > ((distancias[v]==GRAFO_INF)?0:distancias[v]) + g->matriz_adj[v][i]){
                    /** Se a distancias ja esta alocada, verifica se a nova distancias é menor que a atual **/
                    distancias[i] = ((distancias[v]==GRAFO_INF)?0:distancias[v]) + g->matriz_adj[v][i];
                    anteriores[i] = v;                    
                }
            }
        }
        contador--;
    }

    free(visitados);
}