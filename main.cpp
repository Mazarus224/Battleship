/**
 * @file main.cpp
 * @author Caleb Carter / Aaron Jarnes / Malik Robinson / Lyle Nelson
 * @brief main game loop and calls for Battleship game
 * @date 2022-03-22
 */
                                                    //headers and inclusions
#include "bs.h"


int main() 
{
                                                    //SETUP VARIABLES
    //game boards
    char gameBoard[NUM_ROWS][NUM_COLS];  // your ships + enemy hits/misses (bottom board)
    char guessBoard[NUM_ROWS][NUM_COLS]; // your hits and misses (top board)
    char botBoard[NUM_ROWS][NUM_COLS];   // invisible - for mapping bot locations. (enemy board)


                                                    //local variables
    srand(time(NULL)); //for all rand() functions
    bool isDone = false,
         dontCoutCom = false,
         whileReset = false;
    int enterY = 0,
        enterXInt = 0;
    char vertOrHori = ' ',
         enterShip = ' ',
         enterXLetter = ' ';
    string enterString = " ";

    int winner = 0,
    misses = 0,
    hits = 0,
    turns = 0;

                                                    //INITIALIZATION
    welcomeScreen(0);
    //set all boards to '-'
    initializeBoard(gameBoard);
    initializeBoard(guessBoard);
    initializeBoard(botBoard);
    //press enter to continue from menu
    cout << " _______________ \n"
         << "|  ___________  |\n"
         << "| |           | |\n"
         << "| | P R E S S | |\n"
         << "| | E N T E R | |\n"
         << "| |___________| |\n"
         << "|_______________|\n";
    cin.ignore();

                                                    //PLACING SHIPS
    whileReset = false;
    while(!whileReset){
        cout << "WOULD YOU LIKE TO MANUALLY PLACE SHIPS, OR RANDOMLY? (m/r): ";
        getline(cin, enterString);
        if (enterString == "m" || enterString == "M"){
            enterString = " ";
            manuallyPlaceShips(gameBoard, enterXLetter, enterY, vertOrHori, enterShip, enterXInt, dontCoutCom);
            displayBoard(gameBoard);
        } else if (enterString == "r" || enterString == "R") {
            enterString = " ";
            randomlyPlaceShips(gameBoard);
        } else {
            cout << "..Invalid input..restarting sequence..\n";
        }
        cout << "THESE ARE YOUR SHIPS, WOULD YOU LIKE TO RESET YOUR SHIPS? (y/n) ";
        getline(cin, enterString);
        if (enterString != "y" || enterString == "Y"){ // y or Y to reset.
            whileReset = true;
        }
        enterString = " ";
    }
    enterString = " ";
    displayBoard(gameBoard);

    //Randomly places bot ships on invisible board
    randomlyPlaceShips(botBoard);

                                                    //game loop setup
    welcomeScreen(1);
    //loops coinFlip until you pick a valid choice.
    // 0 = player1 starts | 1 = computer starts | 2 = invalid input
    int tick;
    do {
        tick = coinFlip();
    } while (tick == 2);

                                                    //GAME LOOP
    while(!isDone){
        //re-initilize variables every time
        bool shootAgain = false;
        enterXLetter = ' ';
        enterShip = ' ';
        enterXInt = 0;
        enterY = 0;

        if (tick % 2 == 0){ //player1 starts first
            playersTurn(0);
            sleep(PLAYER_TIME);
            cout << "Shoot Board:\n";
            displayBoard(guessBoard);
            //getInput
            while (!isCorrectValue(static_cast<int>(enterXLetter))){
                cout << "TIME TO SHOOT\nPlease enter a character value (a-j): ";
                cin >> enterXLetter;
            }
            bool isInputCorrect = false;
            while (!isInputCorrect){
                cout << "Enter a Y value (1-10): ";
                cin >> enterY;
                if (enterY >= 1 && enterY <= 10){isInputCorrect = true;}
            }
            //modify values for array to read
            enterXInt = static_cast<int>(enterXLetter);
            if (enterXInt >= 65 && enterXInt <= 90){ //capital case
                enterXInt -= 65;
            } else if (enterXInt >= 97 && enterXInt <= 122){ //lower case
                enterXInt -= 97;
            }
            --enterY;
            updateBoardPlayer(botBoard, guessBoard, enterXInt, enterY, shootAgain, hits, misses);
            cout << "Shoot Board:\n";
            displayBoard(guessBoard);
            sleep(PLAYER_TIME);
            if(isWinner() == 1){          //if return 1, player 1 wins
                cout << "Player Wins!\n";
                winner = 1;
                isDone = true;
            }
        } else { // cpu starts first
            playersTurn(1);
            cpuMove(gameBoard, shootAgain, hits, misses);
            if (isWinner() == 2){           //if return 1, player 1 wins 
                cout << "Computer Wins!\n";
                winner = 2;
                isDone = true;
            }
        }
        if (!shootAgain){
            ++tick;
        }
        ++turns;
    }
    logFile(turns, misses, hits, winner);
                                                    //PLAY AGAIN?
    cout << "Congrats! Would you like to play again? (y/n)\n";
    cin >> enterString;
    if (enterString == "y" || enterString == "Y"){
        main();
        return 0;
    }
    return 0;
}