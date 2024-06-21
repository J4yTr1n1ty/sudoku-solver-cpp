#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

const int BOARD_SIZE = 9;
const int TOTAL_CELLS = BOARD_SIZE * BOARD_SIZE;

vector<int> collectInput() {
  vector<int> newBoard(TOTAL_CELLS, 0);
  newBoard[3] = 8;
  newBoard[5] = 1;
  newBoard[16] = 4;
  newBoard[17] = 3;
  newBoard[18] = 5;
  newBoard[31] = 7;
  newBoard[33] = 9;
  newBoard[42] = 1;
  newBoard[46] = 2;
  newBoard[49] = 3;
  newBoard[54] = 6;
  newBoard[61] = 7;
  newBoard[62] = 5;
  newBoard[65] = 3;
  newBoard[66] = 4;
  newBoard[75] = 2;
  newBoard[78] = 6;
  return newBoard;
}

pair<int, int> indexToRowColumn(int index) {
  return {index / BOARD_SIZE, index % BOARD_SIZE};
}

int rowColumnToIndex(int row, int column) { return row * BOARD_SIZE + column; }

bool acceptable(const vector<int> &board, int index, int value) {
  auto [row, column] = indexToRowColumn(index);

  // Check column
  for (int r = 0; r < BOARD_SIZE; ++r) {
    if (board[rowColumnToIndex(r, column)] == value) {
      return false;
    }
  }

  // Check row
  for (int c = 0; c < BOARD_SIZE; ++c) {
    if (board[rowColumnToIndex(row, c)] == value) {
      return false;
    }
  }

  // Check 3x3 box
  int startRow = (row / 3) * 3;
  int startCol = (column / 3) * 3;
  for (int r = startRow; r < startRow + 3; ++r) {
    for (int c = startCol; c < startCol + 3; ++c) {
      if (board[rowColumnToIndex(r, c)] == value) {
        return false;
      }
    }
  }

  return true;
}

vector<int> getPossibleMoves(const vector<int> &board, int index) {
  vector<int> moves;
  for (int value = 1; value <= BOARD_SIZE; ++value) {
    if (acceptable(board, index, value)) {
      moves.push_back(value);
    }
  }

  return moves;
}

void writeSolveTimeToFile(microseconds duration) {
  ofstream file("solve_time.txt", ios::app);
  file << duration.count() << " μs,";
  file.close();
}

bool solve(vector<int> &board, int index, int &backtrack) {
  while ((index < TOTAL_CELLS) && (board[index] != 0)) {
    ++index;
  }
  if (index >= TOTAL_CELLS) {
    return true;
  }
  auto moves = getPossibleMoves(board, index);
  if (moves.empty()) {
    return false;
  }

  for (auto move_ : moves) {
    board[index] = move_;
    if (solve(board, index, backtrack)) {
      return true;
    }
  }

  board[index] = 0;
  ++backtrack;
  return false;
}

void solveBruteForce() {
  auto board = collectInput();
  int backtrack = 0;
  int index = 0;
  auto startTime = high_resolution_clock::now();

  bool solutionFound = solve(board, index, backtrack);
  auto endTime = high_resolution_clock::now();
  auto solutionTime = duration_cast<microseconds>(endTime - startTime);

  cout << "Solution found: " << (solutionFound ? "Yes" : "No") << endl;
  cout << "Backtrack count: " << backtrack << endl;
  cout << "Solution time: " << solutionTime.count() << " μs" << endl;

  writeSolveTimeToFile(solutionTime);
}

int main() {
  cout << "Solving..." << endl;
  solveBruteForce();
  return 0;
}
