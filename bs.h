/**
 * @file bs.h
 * @author Caleb Carter / Aaron Jarnes / Malik Robinson / Lyle Nelson
 * @brief contains function prototypes and globals for Battleship game
 * @date 2022-03-21
 */
#ifndef BS_H
#define BS_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <unistd.h>

using namespace std;

// Global variables and arrays useful in the program
const int NUM_ROWS = 10;  // number of rows of the battleship game board
const int NUM_COLS = 10;  // number of columns of the battleship game board
const int NUM_SHIPS = 5;  // number of ships in the battelship game
const int PLAYER_TIME = 2; //used to slow player functions into a readable speed
const int CPU_TIME = 3; //used to slow bot functions into a readable speed

// Each of the ships information in 3 arrays (parallel arrays)
const string SHIP_NAMES[] = {"carrier", "battleship", "cruiser", "submarine", "destroyer"};
const char SHIP_SYMBOLS[] = {'c', 'b', 'r', 's', 'd'};
const int SHIP_SIZES[] = {5, 4, 3, 3, 2};

//void's
void welcomeScreen(int i); //Graphical display of tutorial
void displayBoard(char board[][NUM_COLS]); //Visually displays inputed array
void initializeBoard(char board[][NUM_COLS]); //Generates specified board at beginning of game
void shipPlacementInfo(); //HOW-TO for placing ships
void placeShips(char array[][10], int row, int lane, char face, char ship, bool &dontCoutCom); //Function for placing ships in array
void playersTurn(int person); //Determines whose turn it is and displays a graphic accordingly
void computerPlaceShips(char array[][10], int row, int lane, char ship); //Randomly places bot ships in invisible array
void checkShotIsAvailable(); //Checks to see if a shot is available or allowed
void updateBoardPlayer(char array[][NUM_COLS], char array1[][NUM_COLS], int i, int k, bool &shootAgain, int &hits, int &misses); //Updates arrays with most recent changes such as a hit or miss
void updateBoardCPU(char array[][NUM_COLS] ,int i, int k, bool &shootAgain, int &hits, int &misses); //Updates cpu board(Invisible)
void shipUserInput(char &enterXLetter, int &enterY, char &vertOrHori, char &enterShip, int &enterXInt); //Where ships will be placed by player
void logFile(int turns, int miss, int hit, int winner); //Records important game info at the end
void cpuMove(char array[][NUM_COLS], bool &shootAgain, int &hits, int &misses); //Random attack generator for CPU moves
void randomlyPlaceShips(char array[][NUM_COLS]); //Randomly places ships for bot and for player if they choose so
void manuallyPlaceShips(char array[][NUM_COLS], char &enterXLetter, int &enterY, char &vertOrHori, char &enterShip, int &enterXInt, bool &dontCoutCom); //Allows player to manually place all ships on their board
void shipMath(char shipArray[], char letter, bool boolean, int shipSize, string shipName, int & tick); //Unseen rules for placing ships
//ints
int coinFlip(); //Chooses who gets the first turn
int isWinner(); //Checks to see if there is a winner yet and announces when there is one
int botMove(); //Bot attack
//bools
bool isCapital(int enterXInt);
bool isLowercase(int enterXInt);
bool isCorrectValue(int enterXInt);
bool playerBot(char board[][NUM_COLS], int i, int k);
bool areShipsPlaced(char array[][NUM_COLS], int rows, int cols);






#endif
