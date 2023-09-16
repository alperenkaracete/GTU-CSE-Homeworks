CC=gcc
CFLAGS= -c -std=c11 -D_DEFAULT_SOURCE -Wall

all: pCp 

pCp: main.o 
	$(CC) main.o -o pCp

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o pCp