
output: main.o utility.o edgeFunctions.o bfs.o circles.o kruskal.o primm.o 
	gcc -o outputProgram main.o utility.o edgeFunctions.o bfs.o circles.o kruskal.o primm.o

main.o: main.c
	gcc -c main.c

utility.o: utility.c utility.h
	gcc -c utility.c

edgeFunctions.o: edgeFunctions.c edgeFunctions.h 
	gcc -c edgeFunctions.c 

bfs.o: bfs.c bfs.h
	gcc -c bfs.c 

circles.o: circles.c circles.h
	gcc -c circles.c 

kruskal.o: kruskal.c kruskal.h
	gcc -c kruskal.c 

primm.o: primm.c primm.h 
	gcc -c primm.c 

exec:
	outputProgram.exe 

clean:
	del *.o *.exe 

