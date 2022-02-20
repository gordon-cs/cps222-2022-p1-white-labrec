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
}

Organism Board::getOrganism(int yCoordinate, int xCoordinate) {
  return boardState[yCoordinate][xCoordinate];
}

void Board::setOrganism(int yCoordinate, int xCoordinate, Organism state) {
  boardState[yCoordinate][xCoordinate] = state;
}

void printBoard(Board board) {

  // Print the border to the special characters representing the border
  for (int i = 0; i < totalRows; i++) {
    for (int j = 0; j < totalCols; j++) {
      if (i == 0 || i == totalRows - 1) {

        // Check if it is the border, and print the proper symbol
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

        // Check the inside of the board for LIVING or NONE cells
        if (board.getOrganism(i, j) == LIVING) {
          cout << "*";
        } else if (board.getOrganism(i, j) == NONE) {
          cout << " ";
        }
      }
    }
  }
}


void doGeneration(Board* boardWrite, Board boardRead) {
  // Initialize local variables
  Organism state;
  int neighborCount;
  for (int i = 1; i < totalRows - 1; i++) {
    for (int j = 1; j <  totalCols - 1; j++) {

      //RT This would be better as a private helper method

      // Count number of LIVING organisms around organism
      neighborCount = 0;
      for (int y = -1; y < 2; y++) {
        for (int x = -1; x < 2; x++) {
          // Ignore 0, 0
          if ((y != 0) || (x != 0)) {
            if (boardRead.getOrganism(i + y, j + x) == LIVING) {
              neighborCount++;
            }
          }
        }
      }

      // Get the state and according to the rules, set it as LIVING or NONE
      Organism currentState = boardRead.getOrganism(i, j);
      if (currentState == LIVING) {
        if (neighborCount < 2 || neighborCount > 3) {
          state = NONE;
        } else {
          state = LIVING;
        }
      } else {
        if (neighborCount == 3) {
          state = LIVING;
        } else {
          state = NONE;
        }
      }

      boardWrite->setOrganism(i, j, state);
    }
  }
}

//RT main() should be in a separate file.  The reasons are more
//apparent in larger projects, but include catching certain types of
//errors.

int main() {
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

  // Initialize boards to user inputted values
  Board* boardEven = new Board(yCoordinates, xCoordinates, numberOfOrganisms);
  Board* boardOdd = new Board(yCoordinates, xCoordinates, numberOfOrganisms);

  cout << ESC << "[H" << ESC << "[J" << "Initial:" << endl;
  // Initial print
  printBoard(*boardEven);

  cout << ESC << "[23;1H" << ESC << "[K" << "Press RETURN to continue";
  while (cin.get() != '\n') { };

  for (int generation = 1; generation < generations + 1; generation++) {
    cout << ESC << "[H" << "Generation " << generation << ":" << endl;

    // Stair step the boards to make sure rules are enforced properly
    if (generation % 2 == 0) {
      doGeneration(boardEven, *boardOdd);
      printBoard(*boardEven);
    } else {
      doGeneration(boardOdd, *boardEven);
      printBoard(*boardOdd);
    }

    // Wait for user input to continue
    cout << ESC << "[23;1H" << ESC << "[K" << "Press RETURN to continue";
    while (cin.get() != '\n') { };
  }

  // End program
  return 0;
}
