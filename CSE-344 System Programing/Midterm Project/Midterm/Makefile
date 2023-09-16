CC=gcc
CFLAGS= -c -Wall

all: server client

server: server.o 
	$(CC) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c

client: client.o 
	$(CC) client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) client.c

clean:
	rm -rf *.o client server