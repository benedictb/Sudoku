CC=		g++
CFLAGS=		-c -Wall -o $@ $^ 

TARGETS= main
SOURCES= Puzzle.o Sudoku.o

all: $(TARGETS)

sampleCharPuzzle: $(SOURCES) sampleCharPuzzle.o
	g++ Puzzle.o sampleCharPuzzle.o -o sampleCharPuzzle

sampleIntPuzzle: $(SOURCES) sampleIntPuzzle.o
	g++ Puzzle.o sampleIntPuzzle.o -o sampleIntPuzzle

main: $(SOURCES) main.o
	g++ Puzzle.o Sudoku.o main.o -o main

%.o: %.cpp 
	$(CC) $(CFLAGS)



clean:
	rm -f $(TARGETS) *.o
