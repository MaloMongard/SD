graphs: graphs.o
	gcc -o graphs graphs.o

graphs.o: graphs.c graphs.h
	gcc -o graphs.o -c graphs.c -Wall