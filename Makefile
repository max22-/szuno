CFLAGS = -Wall -std=c89 -ggdb
EXEC = prefix-lang

all: $(EXEC)

prefix-lang: lang.o main.o
	$(CC) lang.o main.o -o $(EXEC)

lang.o: lang.c lang.h
	$(CC) $(CFLAGS) -c lang.c -o lang.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f *.o $(EXEC)
