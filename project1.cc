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

Organism getOrganismState(int yCoordinate, int xCoordinate, Board board) {
  int neighborCount = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      // Ignore 0, 0
      if ((i != 0) || (j != 0)) {
        if (board.getOrganism(yCoordinate + i, xCoordinate + j) == LIVING) {
          neighborCount++;
        }
      }
    }
  }
  Organism currentState = board.getOrganism(yCoordinate, xCoordinate);
  if (currentState == LIVING) {
    if (neighborCount < 2 || neighborCount > 3) {
      return NONE;
    } else {
      return LIVING;
    }
  } else {
    if (neighborCount == 3) {
      return LIVING;
    } else {
      return NONE;
    }
  }
};

void doGeneration(Board* boardWrite, Board boardRead) {
  Organism state;
  for (int i = 1; i < totalRows - 1; i++) {
    for (int j = 1; j <  totalCols - 1; j++) {
      state = getOrganismState(i, j, boardRead);
      boardWrite->setOrganism(i, j, state);
    }
  }
};


int main() {
  // Set up board

  // Get user input for number of organisms, locations of organisms and
  // number of generations
  int numberOfOrganisms;
  int generations;

  cout << "How many organisms initially? ";
  cin >> numberOfOrganisms;
  int yCoordinates [numberOfOrganisms];
  int xCoordinates [numberOfOrganisms];

  cout << "Locations? ";
  int x, y;
  for (int i = 0; i < numberOfOrganisms; i++) {
    cin >> y >> x;
    yCoordinates[i] = y;
    xCoordinates[i] = x;
  }

  cout << "Generations? ";
  cin >> generations;

  while (cin.get() != '\n') { }
 
  // Initial board
  Board* boardEven = new Board(yCoordinates, xCoordinates, numberOfOrganisms);
  Board* boardOdd = new Board(yCoordinates, xCoordinates, numberOfOrganisms);
  cout << ESC << "[H" << ESC << "[J" << "Initial:" << endl;
  // Initial print
  printBoard(*boardEven);

  cout << ESC << "[23;1H" << ESC << "[K" << "Press RETURN to continue";
  while (cin.get() != '\n') { };

  for (int generation = 1; generation < generations + 1; generation++) {
    cout << ESC << "[H" << "Generation " << generation << ":" << endl;
    if (generation % 2 == 0) {
      doGeneration(boardEven, *boardOdd);
      printBoard(*boardEven);
    } else {
      doGeneration(boardOdd, *boardEven);
      printBoard(*boardOdd);
    }

    cout << ESC << "[23;1H" << ESC << "[K" << "Press RETURN to continue";
    while (cin.get() != '\n') { };
  }

  return 0;
};