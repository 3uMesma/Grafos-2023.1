#include "kosaraju.h"

// Objetivo: preencher a pilha Stack com os vértices do grafo em ordem
// crescente de tempos de finalização
void pilha_preencher(GRAFO *grafo, int v, bool visitado[], stack<int> &pilha)
{
	// Marca o nó atual como visitado
	visitado[v] = true;

	// Chama recursivamente todos os nós adjacentes a esse vértice
	list<int>::iterator i;
	for(i = grafo->adj[v].begin(); i != grafo->adj[v].end(); ++i)
		if(!visitado[*i])
			pilha_preencher(grafo, *i, visitado, pilha);

	// Após processar todos, coloca-los na pilha
	pilha.push(v);
}

// Função auxiliar para setar todos os vértices iniciais
// como não visitados
void vertices_set_nao_vistados(GRAFO *grafo, bool visitado[]){
	for(int i = 0; i < grafo->num_vertices; i++){
        visitado[i] = false;
    }
}

// Função principal que encontra os componentes fortemente conexos
void comp_fort_con(GRAFO *grafo){
	// Para printar os resultados em ordem crescente, vamos criar uma matriz
	// dinâmica e depois ordena-la 
	int linhas = 0;
	vector<vector<int> > matriz;

    // criando uma pilha para armazenar as informações
	stack<int> pilha;

	// marcando todos os vértices iniciais como não visitados
    bool *visitado = new bool[grafo->num_vertices];
    vertices_set_nao_vistados(grafo, visitado);

	// Colocando os vértices na pikha de acordo com o tempo de processamento
	for(int i = 0; i < grafo->num_vertices; i++){
        if(visitado[i] == false){
            pilha_preencher(grafo, i, visitado, pilha);
        }
    }

	// Criando o grafo transposto
	GRAFO *grafo_trans = grafo_transposto(grafo);

	// Setando novamente todos como não visitados, para a segunda busca DFS
    vertices_set_nao_vistados(grafo, visitado);

	// Agora, processando todos os vértices na ordem da pilha
	int j = 0;
	while (!pilha.empty()){
		// salvamos numa variável o topo da pilha para depois retira-lo

		int vertice_atual = pilha.top();
		pilha.pop();

		// printando oa componentes fortemente conexos
		if (!visitado[vertice_atual]){
			// o 1 é para não realocarmos algo para zero
			vector<int> linha;
			grafo_DFS(grafo_trans, vertice_atual, visitado, linha);
			//ordenando cada linha		
			sort(linha.begin(), linha.end());
			// Fazendo uma verificação para que as linhas só sejam incrementadas
			// caso o tamanho do vetor do resultado da busca não for zero
			if (linha.size() > 0){
				matriz.push_back(linha);
				linhas++;
				j++;
			}
		}
	}

	// Agora, ordenando as linhas da nossa matriz
	sort(matriz.begin(), matriz.end());

	cout << linhas << endl;
	// Por último, iremos imprimir nossas informações da matriz
	for (int i = 0; i < linhas; i++) {
		// cout << matriz[i].size() << endl;
		for (int j = 0; j < matriz[i].size(); j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
    }

}