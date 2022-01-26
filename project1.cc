#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "project1.h"

Board::Board(int yCoordinates[], int xCoordinates[], int coordinateLength) {
  for (int i = 0; i < totalRows; i++) {
    for (int j = 0; j < totalCols; j++) {
      if (i == 0 || i == totalRows - 1 || j == 0 || j == totalCols - 1) {
        boardState[i][j] = BORDER;
      } else {
        boardState[i][j] = NONE;
      }
    }
  }
  
  for (int i = 0; i < coordinateLength; i++) {
    boardState[yCoordinates[i] + 1][xCoordinates[i] + 1] = LIVING;
  }
};

Organism Board::getOrganism(int yCoordinate, int xCoordinate) {
  return boardState[yCoordinate][xCoordinate];
};

void Board::setOrganism(int yCoordinate, int xCoordinate, Organism state) {
  boardState[yCoordinate][xCoordinate] = state;
};

void printBoard(Board board) {
  for (int i = 0; i < totalRows; i++) {
    for (int j = 0; j < totalCols; j++) {
      if (i == 0 || i == totalRows - 1) {
        if (j != 0 && j != totalCols - 1) {
          cout << "-";
        } else if (j == 0) {
          cout << "+";
        } else {
          cout << "+" << endl;
        }
      } else if (j == 0) {
        if (i != 0 || i != totalRows - 1) {
          cout << "|";
        }
      } else if (j == totalCols - 1) {
        if (i != 0 || i != totalRows - 1) {
          cout << "|" << endl;
        }
      } else {
        if (board.getOrganism(i, j)) {
          cout << "*";
        } else {
          cout << " ";
        }
      }
    }
  }
};

int main() {
  int yCoordinates [1];
  int xCoordinates [1];
  yCoordinates[0] = 1;
  xCoordinates[0] = 1;
  Board board = Board(yCoordinates, xCoordinates, 1);
  printBoard(board);

  return 0;
};