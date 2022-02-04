// Declares classes and functions to be used for simulating Conway's
// Game of Life for CPS222 Data Structures and Algorithms at Gordon College

// Authors: Silas White and Gavin LaBrec

#ifndef PROJECT1_H_
#define PROJECT1_H_

#include <iostream>
#include <string>

using std::string;

enum Organism { NONE, LIVING, BORDER };

static const int activeRows = 18;
static const int activeCols = 50;
static const int totalRows = activeRows + 2;
static const int totalCols = activeCols + 2;
static const char ESC = 27;


// Creates the board for Conway's Game of Life will use to create its simulation
// Contains accessor, mutator, and constructor to manipulate the board
class Board {
  public:
  
    // Constructor for the board. Takes yCoordinate and xCoordinate array along with the length of those arrays.
    // The board will then be constructed with organisms set to LIVINF at the coordinates specified by the yCoordinates
    // and xCoordinates array.
    //
    // Example:
    // Board* board = new Board({ 1, 2 }, {2, 1}, 2);
    // Which creates a new Board with organisms set to LIVING at coordinates 1, 2 and 2, 1
    Board(int yCoordinates[], int xCoordinates[], int coordinateLength);

    // Counts the living organisms that are around the cell indexed at yCoordinate
    // and xCoordinate. Board passed as pointer.
    int countLivingNeighbors(int yCoordinate, int xCoordinate, Board* board);

    // Accessor method for an organism specified by yCoordinate and xCoordinate
    Organism getOrganism(int yCoordinate, int xCoordinate);

    // Sets organism at cell to given state
    // Cell denoted by yCoordinate and xCoordinate
    // State can be NONE, LIVING, BORDER
    void setOrganism(int yCoordinate, int xCoordinate, Organism state);

  private:
    // Private matrix (array of arrays) of enums representing the board
    // Includes BORDER, LIVING, and NONE parts of the board
    Organism boardState[totalRows][totalCols];
};

#endif // PROJECT1_H_
