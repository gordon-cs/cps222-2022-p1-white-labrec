// Declares classes and functions to be used for simulating Conway's
// Game of Life for CPS222 Data Structures and Algorithms at Gordon College

// Authors: Silas White nad Gavin Labrec

// WIP
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

// Holds the information about the board of organisms and is respobsible for simulating generations, counting neighbors,
// and providing accessors and mutators for the data
class Board {
  public:
    // Constructor
    Board(int yCoordinates[], int xCoordinates[], int coordinateLength);
    // ~Board();
    int countLivingNeighbors(int yCoordinate, int xCoordinate, Board board);
    Organism getOrganism(int yCoordinate, int xCoordinate);
    void setOrganism(int yCoordinate, int xCoordinate, Organism state);
  private:
    // Private matrix (array of arrays) representing the board, including
    // border, living, and dead parts of the board
    Organism boardState[totalRows][totalCols];
};

#endif // PROJECT1_H_