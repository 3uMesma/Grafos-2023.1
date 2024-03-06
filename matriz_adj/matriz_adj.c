# include "matriz_adj.h"

// objetivo: criar a matriz de adjacencias
int **criar_matriz_adj(FILE *arq, int q_vertices, int q_arestas){
	// criando o vetor de adjacencias:
	int **matriz_adj;

	// aloca um vetor de ponteiros para linhas
	matriz_adj = malloc (q_vertices * sizeof (int*));
	// aloca cada uma das linhas:
	for (int i = 0; i < q_vertices; i++){
		matriz_adj[i] = malloc (q_vertices * sizeof (int));
	}

	// inicialmente, vou considerar que nenhum vertice tem conexão entre si:
	for(int i = 0; i < q_vertices; i++){
		for (int j = 0; j < q_vertices; j++){
			matriz_adj[i][j] = 0;
		}
	}

	// lendos os dados para ver os vertices que tem conexão:
	for (int i = 0; i < q_arestas; i++){
		int a1, a2;
		fscanf(arq, "%d %d", &a1, &a2);
		// como é um grafo não-orientado, serão preenchidos dois locais da matriz (a1, a2) e (a2, a1):
		matriz_adj[a1][a2] = 1;
		matriz_adj[a2][a1] = 1;
	}
	return matriz_adj;
}

// objetivo: imprimir a matriz de adjacencias
void imprimir_matriz_adj(int **matriz_adj, int q_vertices){
	for(int i = 0; i < q_vertices; i++){
		for (int j = 0; j < q_vertices; j++){
			printf("%d ", matriz_adj[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//objetivo: liberar mamória alocada para matriz de adjacências
void apagar_matriz_adj(int **matriz_adj, int q_vertices){
	// liberando memoria de cada linha da matriz:
	for (int i = 0; i < q_vertices; i++){
		free(matriz_adj[i]);
	}
	// liberando a memoria do que sobrou da matriz
	free(matriz_adj);
}

// objetivo: criar um vetor contendo o grau de cada cada vértice
int *calcular_grau_vertices(int **matriz_adj, int q_vertices){
	// criando o vetor:
	int *grau_vertices = (int*) malloc(q_vertices * sizeof(int));

	// contabilizando o grau:
	for (int i = 0; i < q_vertices; i++){
		int grau = 0;
		for (int j = 0; j < q_vertices; j++){
			grau += matriz_adj[i][j];
		}
		grau_vertices[i] = grau;
	}
	return grau_vertices;
}

// objetivo: imprimir vetor dos graus de cada vertice
void imprimir_grau_vertices(int *grau_vertices, int q_vertices){
	printf("Grau dos vertices: ");
	for (int i = 0; i < q_vertices; i++){
		printf("%d ", grau_vertices[i]);
	}
	printf("\n");
}

// objetivo: escolher a aresta certa para completar o circuito euleriano, pois quando há duas arestas, uma é um caminho normal, mas
// o outro é só para voltar e devemos escolher o caminho normal
bool eh_seguro(int **matriz_adj, int q_vertices, int a){
	int grau = 0;
	for(int i = 0; i < q_vertices; i++){
		if(matriz_adj[a][i]){
			grau++;
		}
	    if (grau > 1){
	    	return false; // se o grau é maior que zero, esse caminho não é o ideal para completar o circuito
	    }
	}
    return true;
}

// objetivo: encontrar e escrever o caminho euleriano, para desenvolver a lógica foi utilizado o método de Fleury
void circuito_euleriano(int **matriz_adj, int inicio, int q_arestas, int q_vertices){
   for(int i = 0; i < q_vertices; i++){
    	if(matriz_adj[inicio][i]){ // se entre os dois vertices tem uma aresta então:
      		// se só resta a aresta de voltar pro vertice inicial ou se o caminho entre os dois vertices é seguro, então:
        	if(q_arestas <= 1 || !eh_seguro(matriz_adj, q_vertices, i)){ 
        		printf("%d ", inicio);
            	matriz_adj[inicio][i] = 0;
            	matriz_adj[i][inicio] = 0; //removendo do grafo nas duas posições, pois é um grafo não-direcionado
            	q_arestas--; //eliminando essa aresta da nossa quantidade, pois já a percorremos 
            	circuito_euleriano(matriz_adj, i, q_arestas, q_vertices); // essa função é recursiva, funcionando até o circuito ser terminado
        	}
    	}
   	}
}

// objetivo: verificar se o grafo é um grafo euleriano
void eh_euleriano(int **matriz_adj, int q_vertices, int q_arestas){
	// chamando a função para verificar o grau de todos os vertices:
	int *grau_vertices = calcular_grau_vertices(matriz_adj, q_vertices);

	// percorrendo o vetor para ver se algum tem grau impar, pois vertices com grau impar impossibilitam a existencia de um circuito euleriano
	// usando uma flag para verificar se há algum grau impar:
	int euleriano;
	for (int i = 0; i < q_vertices; i++){
		if (grau_vertices[i] % 2 != 0){
			euleriano = false;
		}
	}
	if (euleriano){
		printf("Sim\n");
		circuito_euleriano(matriz_adj, 0, q_arestas, q_vertices);
		printf("%d\n", 0); // imrpimrindo o ultimo vertice, que é o sempre começa em zero
	}
	else{
		printf("Não\n");
	}
}