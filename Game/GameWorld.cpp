#include "GameWorld.h"

// Default constructor
GameWorld::GameWorld() : GameWorld(DEFAULT_ROWS, DEFAULT_COLS, DEFAULT_CHANCE) {
    // Delegate instantiation to the parameterized constructor
}

// Parameterized constructor
GameWorld::GameWorld(int intRows, int intCols, int intChance) {

    // Validate the dimensions of the grid
    validateDimensions(intRows, intCols);
    // Validate the probability of occurrence of a coin in each cell of the game grid
    validateChance(intChance);

    // Seed the random number generator
    srand(time(nullptr));

    this->intRows = intRows;
    this->intCols = intCols;
    this->intChance = intChance;
    this->intScore = 0;
    this->intNumCoins = 0;

    gameGrid = new GameEntity*[intRows];
    for (int r = 0; r < intRows; r++) {
        gameGrid[r] = new GameEntity[intCols];
        for (int c = 0; c < intCols; c++) {
            if (randomNumberGenerator(0, 100) <= intChance) {
                // Place the coins in the game grid
                gameGrid[r][c] = COIN;
                intNumCoins += 1; // Increment intNumCoins when a coin is generated
            }
            else {
                // Place the empty spaces in the game grid
                gameGrid[r][c] = SPACE;
            }
        }
    }
    // Place the player in a random location in the game grid that is not occupided by a coin
    intPlayerRow = randomNumberGenerator(0, intRows - 1);
    intPlayerCol = randomNumberGenerator(0, intCols - 1);
    while (gameGrid[intPlayerRow][intPlayerCol] == COIN) {
        // As long as the current player position coincides with a coin in the game grid, generate a new position
        intPlayerRow = randomNumberGenerator(0, intRows - 1);
        intPlayerCol = randomNumberGenerator(0, intCols - 1);
    }
    gameGrid[intPlayerRow][intPlayerCol] = PLAYER;
}

// Copy constructor for deep oopying
GameWorld::GameWorld(const GameWorld &objGameWorld) : GameWorld(objGameWorld.intRows, objGameWorld.intCols, objGameWorld.intChance) {
    // Delegate deep copying to the parameterized costructor
}

// Destructor
GameWorld::~GameWorld() {

    for (int r = 0; r < intRows; r++) {
        delete [] gameGrid[r];
    }
    delete [] gameGrid;
}

// This function returns the number of rows of the game grid
int GameWorld::getRows() const {
    return intRows;
}

// This function returns the number of columns of the game grid
int GameWorld::getCols() const {
    return intCols;
}

// This function returns the probability of occurrence of a coin in each cell of the game grid
int GameWorld::getChance() const {
    return intChance;
}

// This function returns the value of a cell in the game grid
int GameWorld::getCell(int intRow, int intCol) const {
    if (isInRange(intRow, intCol))
        return gameGrid[intRow][intCol];
    else
        exit(RANGE_ERROR);
}

// This function sets the number of rows of the game grid
void GameWorld::setRows(int intRows) {
    this->intRows = intRows;
}

// This function sets the number of columns of the game grid
void GameWorld::setCols(int intCols) {
    this->intCols = intCols;
}

// This function sets the probability of occurrence of a coin in each cell of the game grid
void GameWorld::setChance(int intChance) {
    this->intChance = intChance;
}

// This function sets the value of a cell in the game grid
void GameWorld::setCell(int intRow, int intCol, GameEntity gameEntity) {
    if (isInRange(intRow, intCol))
        gameGrid[intRow][intCol] = static_cast<GameEntity>(gameEntity);
    else
        exit(RANGE_ERROR);
}

// This function displays the game to the stdandard output stream
void GameWorld::displayGameWorld() const {

    cout<<"Score : "<<intScore<<" points"<<endl;

    cout<<endl;

    for (int r = 0; r < intRows; r++) {
        for (int c = 0; c < intCols; c++) {
            cout<<GAME_SYMBOLS[gameGrid[r][c]]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;

    if (intScore == intNumCoins * 5) {
        cout<<"Congratulationa. You win!!!!!!!!!!!!!"<<endl;
        cout<<"Your score : "<<intScore<<" points"<<endl;
        exit(SUCCESS);
    }
}

// This function validates the position of a cell in the game grid to ensure that the cell is not out of bounds
bool GameWorld::isInRange(int intRow, int intCol) const {
    if (intRow < 0)
        return false;
    if (intRow >= intRows)
        return false;
    if (intCol < 0)
        return false;
    if (intCol >= intCols)
        return false;
    else
        return true;
}

// This function moves the player in the game grid as per the user input
void GameWorld::movePlayer(char chDirection) {

    int intPR = intPlayerRow; // This variable stores the current row position of the player
    int intPC = intPlayerCol; // This variable stores the current column position of the player

    switch (chDirection) {
        case 'w':
            intPR--;
            break;
        case 'a':
            intPC--;
            break;
        case 's':
            intPR++;
            break;
        case 'd':
            intPC++;
            break;
    }

    if (isInRange(intPR, intPC)) {
        gameGrid[intPlayerRow][intPlayerCol] = SPACE; // Assign SPACE to the previous player position in the game grid
        intPlayerRow = intPR; // Update the player's row position
        intPlayerCol = intPC; // Update the player's column position
        if (gameGrid[intPlayerRow][intPlayerCol] == COIN) {
            intScore += 5; // Increment the score if the player collects a coin
        }
        gameGrid[intPlayerRow][intPlayerCol] = PLAYER; // Assign PLAYER to the new player position in the game grid
    }
}

// This function validates the size of the rows or columns of the dimensions
 void GameWorld::validateDimensions(int intRows, int intCols) const {
     if (intRows < MIN_DIM_SIZE) {
        cerr<<"Error. "<<intRows<<" is less than the minimum permissable row size of "<<MIN_DIM_SIZE<<endl;
        exit(ERROR_DIM_SIZE);
     }

     if (intRows > MAX_DIM_SIZE) {
         cerr<<"Error. "<<intRows<<" is greater than the maximum permissable row size of "<<MAX_DIM_SIZE<<endl;
         exit(ERROR_DIM_SIZE);
     }

     if (intCols < MIN_DIM_SIZE) {
         cerr<<"Error. "<<intCols<<" is less than the minimum permissable column size of "<<MIN_DIM_SIZE<<endl;
         exit(ERROR_DIM_SIZE);
     }

     if (intCols > MAX_DIM_SIZE) {
         cerr<<"Error. "<<intCols<<" is greater than the maximum permissable column size of "<<MAX_DIM_SIZE<<endl;
         exit(ERROR_DIM_SIZE);
     }
 }

// This function validates the probability of occurrence of a coin in each cell of the game grid
void GameWorld::validateChance(int intChance) const {
    if (intChance < MIN_CHANCE) {
        cerr<<"Error. "<<intChance<<" is less than the minimum permissable chance of occurrence of a coin of "<<MIN_CHANCE<<endl;
        exit(ERROR_CHANCE_SIZE);
    }
    if (intChance > MAX_CHANCE) {
        cerr<<"Error. "<<intChance<<" is greater than the maximum permissable chance of occurrence of a coin of "<<MAX_CHANCE<<endl;
        exit(ERROR_CHANCE_SIZE);
    }
}
