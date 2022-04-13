CFLAGS = -Wall -std=c89 -ggdb
EXEC = szuno

all: $(EXEC)

szuno: szuno.o main.o
	$(CC) szuno.o main.o -o $(EXEC)

szuno.o: szuno.c szuno.h
	$(CC) $(CFLAGS) -c szuno.c -o szuno.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

.PHONY: run clean todo

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f *.o $(EXEC)

todo:
	@grep -r "TODO" --exclude="Makefile"
