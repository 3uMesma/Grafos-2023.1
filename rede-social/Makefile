all: grafo.o kosaraju.o main.o
	g++ grafo.o kosaraju.o main.o -o meuPrograma

grafo.o: grafo.cpp grafo.h
	g++ -c grafo.cpp

kosaraju.o: kosaraju.cpp kosaraju.h
	g++ -c kosaraju.cpp
	 
main: main.cpp
	g++ -c main.cpp
	 
clean:
	rm *.o meuPrograma

run:
	./meuPrograma