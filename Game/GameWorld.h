#ifndef GAMEWORLD_H_INCLUDED
#define GAMEWORLD_H_INCLUDED

#include "helperFunctions.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <ctime>
using namespace std;

enum StatusCodes {
    RANGE_ERROR,
    SUCCESS,

};

enum GameEntity {
    SPACE,
    PLAYER,
    COIN,
    ERROR_DIM_SIZE,
    ERROR_CHANCE_SIZE
};

const char GAME_SYMBOLS[] = {'.', 'P', '$'};

class GameWorld {
public:
    static const int DEFAULT_ROWS = 10; // Default row size of the game grid
    static const int DEFAULT_COLS = 10; // Default column size of the grid
    static const int DEFAULT_CHANCE = 20; // Default probability of occurrence of a coin in each cell of the game grid
    static const int MIN_DIM_SIZE = 5; // Minimum permissable size of the rows or columns of the game grid
    static const int MAX_DIM_SIZE = 100; // Maximum permissable size of the rows or columns of the game grid
    static const int MIN_CHANCE = 10; // Minimum permissable probability of occurrence of a coin in each cell of the game grid
    static const int MAX_CHANCE = 50; // Maximum permissable probability of occurrence of a coin in each cell of the game grid

    // Overloaded constructors
    GameWorld(); // Default constructor
    GameWorld(int intRows, int intCols, int intChance); // Parameterized constructor
    GameWorld(const GameWorld &objGameWorld); // Copy constructor for deep oopying

    // Destructor
    ~GameWorld();

    // Accessors
    int getRows() const; // This function returns the number of rows of the game grid
    int getCols() const; // This function returns the number of columns of the game grid
    int getChance() const; // This function returns the probability of occurrence of a coin in each cell of the game grid
    int getCell(int intRow, int intCol) const;// This function returns the value of a cell in the game grid

    // Mutators
    void setRows(int intRows); // This function sets the number of rows of the game grid
    void setCols(int intCols); // This function sets the number of columns of the game grid
    void setChance(int intChance); // This function sets the probability of occurrence of a coin in each cell of the game grid
    void setCell(int intRow, int intCol, GameEntity gameEntity); // This function sets the value of a cell in the game grid

    // This function displays the game to the standard output stream
    void displayGameWorld() const;

    // This function moves the player in the game grid as per the user input
    void movePlayer(char chDirection);

private:
    int intRows; // Number of rows of the game grid
    int intCols; // Number of columns of the game grid
    int intChance; // Probability of occurrence of a coin in each cell of the game grid
    GameEntity** gameGrid; // Two dimensional game grid
    int intPlayerRow; // Row position of the player in the game grid
    int intPlayerCol; // Column position of the player in the game grid
    int intScore; // Player's score
    int intNumCoins; // Number of coins in the game grid at instantiation
    void validateDimensions(int intRows, int intCols) const; // This function validates the size of the rows or columns of the dimensions
    void validateChance(int intChance) const; // This function validates the probability of occurrence of a coin in each cell of the game grid
    bool isInRange(int intRow, int intCol) const ; // This function validates the position of a cell in the game grid to ensure that the cell is not out of bounds
};



#endif // GAMEWORLD_H_INCLUDED
