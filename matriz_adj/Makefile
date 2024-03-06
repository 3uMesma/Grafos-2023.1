all: matriz_adj.o main.o
	gcc matriz_adj.o main.o -o grafo_euleriano -std=c99 -Wall -lm

matriz_adj.o:
	gcc -c matriz_adj.c -o matriz_adj.o -lm
	 
main.o:
	gcc -c main.c -o main.o -lm
	 
clean:
	rm *.o grafo_euleriano

run:
	./grafo_euleriano