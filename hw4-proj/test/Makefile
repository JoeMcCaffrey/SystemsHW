CC = gcc
CFLAGS = -I/usr/include --std=c99 -Wall -g
LDFLAGS = -L/usr/lib/i386-linux-gnu -lrt -lm -lpthread
LDTESTFLAGS = -lcheck $(LDFLAGS)
OBJS = ../huffman.o ../bits-io.o ../pqueue.o ../tree.o ../table.o

all: public-test private-test private-test-aditya

public-test: public-test.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) public-test.o -o public-test $(LDTESTFLAGS)

public-test.o: public-test.c 
	$(CC) $(CFLAGS) -c public-test.c

private-test: private-test.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) private-test.o -o private-test $(LDTESTFLAGS)

private-test.o: private-test.c 
	$(CC) $(CFLAGS) -c private-test.c

private-test-aditya: private-test-aditya.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) private-test-aditya.o -o private-test-aditya $(LDTESTFLAGS)

private-test-aditya.o: private-test-aditya.c 
	$(CC) $(CFLAGS) -c private-test-aditya.c

clean:
	rm -f *.o
	rm -f public-test
	rm -f private-test
	rm -f private-test-aditya
