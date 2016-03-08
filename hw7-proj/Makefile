

CC = gcc
CFLAGS = -Wall -g -pthread 
OBJS = csapp.o

all: client

client:	 $(OBJS) client.o 
	  $(CC) $(CFLAGS) $(OBJS)  client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) -c client.c



csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c


clean:
	rm -f *.o
	rm -f client

