#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "project1.h"

Board::Board(int yCoordinates[], int xCoordinates[], int coordinateLength) {
  
  // Initialize Border and set the inside of the frame to empty
  for (int i = 0; i < totalRows; i++) {
    for (int j = 0; j < totalCols; j++) {
      if (i == 0 || i == totalRows - 1 || j == 0 || j == totalCols - 1) {
        boardState[i][j] = BORDER;
      } else {
        boardState[i][j] = NONE;
      }
    }
  }
  
  // Set the user inputted coordinates to LIVING
  for (int i = 0; i < coordinateLength; i++) {
    boardState[yCoordinates[i]][xCoordinates[i]] = LIVING;
  }
};

Organism Board::getOrganism(int yCoordinate, int xCoordinate) {
  return boardState[yCoordinate][xCoordinate];
};

void Board::setOrganism(int yCoordinate, int xCoordinate, Organism state) {
  boardState[yCoordinate][xCoordinate] = state;
};

void printBoard(Board board) {
  // Print the border to the special characters representing the border
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
        if (board.getOrganism(i, j) == LIVING) {
          cout << "*";
        } else if (board.getOrganism(i, j) == NONE) {
          cout << " ";
        }
      }
    }
  }
};

int countLivingNeighbors(int yCoordinate, int xCoordinate, Board* board) {
  int count = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      // Ignore 0, 0
      if ((i != 0) || (j != 0)) {
        if (board->getOrganism(yCoordinate + i, xCoordinate + j) == LIVING) {
          count++;
        }
      }
    }
  }
  return count;
}

int main() {
  // Set up board

  // increment index
  // take the input from user
  // ask for input for another point
  // end if they do not add another point
  int numberOfOrganisms;
  int generations;

  cout << "How many organisms initially? ";
  cin >> numberOfOrganisms;
  int yCoordinates [numberOfOrganisms];
  int xCoordinates [numberOfOrganisms];

  cout << "Locations? ";
  int x, y;
  for (int i = 0; i < numberOfOrganisms; i++) {
    cin >> x >> y;
    yCoordinates[i] = y;
    xCoordinates[i] = x;
  }

  cout << "Generations? ";
  cin >> generations;

  while (cin.get() != '\n') { }
 
  // Initial board
  Board* board = new Board(yCoordinates, xCoordinates, numberOfOrganisms);
  cout << ESC << "[H" << ESC << "[J" << "Initial:" << endl;

  // board loop
  printBoard(*board);
  // missing line here from implementation notes
  cout << ESC << "[23;1H" << ESC << "[K" << "Press RETURN to continue";
  while (cin.get() != '\n') { /* Intentionally empty loop body */ };

  return 0;
};