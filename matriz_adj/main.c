// Nome: Amanda Kasat Baltor
// NUSP: 13727210

# include "matriz_adj.h"

int main(){
	// abrindo o arquivo:
	FILE *arq_entrada;
	char nome_arquivo[50];
	scanf("%s",nome_arquivo);
	arq_entrada = fopen(nome_arquivo, "r");

	// caso o arquivo nao exista:
	if (arq_entrada == NULL){
		printf("Erro de leitura do arquivo [%s]\n",nome_arquivo);
		exit(1);
	}

	// lendo os dados da entrada:
	// vertices e arestas
	int q_vertices, q_arestas;
	fscanf(arq_entrada, "%d %d", &q_vertices, &q_arestas);

	// criando e imprimindo a matriz de adjacencias:
	int **matriz_adj = criar_matriz_adj(arq_entrada, q_vertices, q_arestas);

	// verificando se o grafo é um grafo euleriano:
	eh_euleriano(matriz_adj, q_vertices, q_arestas);

	// agora que já fizemos tudo, fechamos o arquivo e desalocamos memória:
	apagar_matriz_adj(matriz_adj, q_vertices);
	fclose(arq_entrada);
	return 0;
}