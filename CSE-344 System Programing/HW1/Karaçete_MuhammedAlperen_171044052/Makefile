CC=gcc
CFLAGS= -c -Wall

all: appendMeMore part2 part3

part3: part3.o 
	$(CC) part3.o -o part3	

part3.o: part3.c
	$(CC) $(CFLAGS) part3.c

part2: part2.o 
	$(CC) part2.o -o part2	

part2.o: part2.c
	$(CC) $(CFLAGS) part2.c

appendMeMore: appendMeMore.o 
	$(CC) appendMeMore.o -o appendMeMore

appendMeMore.o: appendMeMore.c
	$(CC) $(CFLAGS) appendMeMore.c

clean:
	rm -rf *.o part2 part3 appendMeMore f* secondFile