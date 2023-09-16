CC=gcc
CFLAGS= -c -std=c11 -D_DEFAULT_SOURCE -Wall

all: BibakBOXClient BibakBOXServer

BibakBOXClient: client.o 
	$(CC) client.o -o BibakBOXClient

client.o: client.c
	$(CC) $(CFLAGS) client.c

BibakBOXServer: server.o 
	$(CC) server.o -o BibakBOXServer

server.o: server.c
	$(CC) $(CFLAGS) server.c	

clean:
	rm -rf *.o BibakBOXClient BibakBOXServer