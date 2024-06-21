CC=g++
CFLAGS=-Wall -Wextra -std=c++14 -O3 -Ofast -march=native -mtune=native -ffast-math -flto

all: SudokuSolver

SudokuSolver: main.cpp
	$(CC) $(CFLAGS) -o build/solver main.cpp

clean:
	rm -f SudokuSolver
