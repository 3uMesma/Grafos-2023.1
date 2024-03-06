all: main.o grafo.o
	g++ main.o grafo.o -Wall -o Runnable

main.o: main.cpp grafo.o
	g++ -c main.cpp -Wall -o main.o
grafo.o: grafo.cpp grafo.h
	g++ -c grafo.cpp -Wall -o grafo.o

clear:
	rm *.o
run:
	./Runnable
run2:
	./Runnable < 1.in
zip:
	zip Grafos_Ex4.zip Makefile *.cpp *.h
test:
	clear
	make all
	make run2