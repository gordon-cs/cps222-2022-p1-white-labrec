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


// Creates the board that our Conway's Game of Life will use to create its simulation
// Contains accessor, mutator, and constructor to manipulate the board
class Board {
  public:
  
    // Constructor for the board. Takes yCoordinates and xCoordinates array along with the length of those arrays.
    // The board will then be constructed with organisms set to living at the coordinates specified by the yCoordinates
    // and xCoordinates array.
    //
    // Example:
    //  Board* board = new Board({ 1, 2 }, {2, 1}, 2);
    //  Which creates a new Board with ogranisms set to living at coordinates 1, 2 and 2, 1
    Board(int yCoordinates[], int xCoordinates[], int coordinateLength);

    // Accessor method for an organism specified by yCoordinate and xCoordinate.
    // Returns organism enum state for the cell corresponding to that location
    //
    // Example:
    //  Board* board = new Board({ 1, 2 }, { 1, 2 }, 2);
    //  Organism state = board->getOrganism(1, 1);
    // 
    // state now holds value LIVING returned from getOrganism
    Organism getOrganism(int yCoordinate, int xCoordinate);

    // Mutator method for changing the enum value of an organism at a particular cell
    // specified by yCoordinate, xCoordinate and an organism state
    // 
    // Example:
    //  Board* board = new Board({ 1, 2 }, { 1, 2 }, 2);
    //  Organism state = board->getOrganism(1, 1);
    // 
    // state now holds value LIVING returned from getOrganism
    //
    //  board.setOrganism(1, 1, NONE);
    //  Organism state = board->getOrganism(1, 1);
    // 
    // state now holds value None returned from getOrganism
    void setOrganism(int yCoordinate, int xCoordinate, Organism state);

  private:

    // Private matrix (array of arrays) of enums representing the board 
    // Includes BORDER, LIVING, and NONE parts of the board
    Organism boardState[totalRows][totalCols];
};

// Takes a board object and prints it to the terminal according the rules given in 
// in project introduction. Will print * for alive organism, whitespace for dead 
// cell, + for corner, | for right or left side, and _ for top or bottom.
// Example:
// 
//  Board* newBoard = new Board({ 1, 2 }, { 1, 2 }, 2);
//  printBoard(newBoard);
// 
// OUTPUT:
// +--------------------------------------------------+
// |*                                                 |
// | *                                                |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// |                                                  |
// +--------------------------------------------------+
void printBoard(Board board);

// Updates board according to set rules to perform a generation
// Each generation is an iteration of Conway's Game of Life
// Takes a Board pointer to write into and Board object to read from
// Iterates through each cell, changing enum value according to rules
void doGeneration(Board* boardWrite, Board boardRead);


#endif // PROJECT1_H_
