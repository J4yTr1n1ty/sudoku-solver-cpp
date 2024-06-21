CC=g++
CFLAGS=-Wall -Wextra -std=c++14

all: SudokuSolver

SudokuSolver: main.cpp
	$(CC) $(CFLAGS) -o build/solver main.cpp

clean:
	rm -f SudokuSolver
