all: func.o
	gcc func.o main.c -o main

func.o: func.h
	gcc -c func.c

clean:
	rm -rf *.o
