CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: program

program: main.o proje.o
	$(CC) $(CFLAGS) -o program main.o proje.o

main.o: main.c proje.h
	$(CC) $(CFLAGS) -c main.c

Proje1.o: proje.c proje.h
	$(CC) $(CFLAGS) -c proje.c

clean:
	rm -f *.o program kategoriler.txt kitaplar.txt