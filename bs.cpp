/**
 * @file bs.cpp
 * @author Caleb Carter / Aaron Jarnes / Malik Robinson / Lyle Nelson
 * @brief Contains all functions and their dictation for main.cpp
 * @date 2022-03-21
 */

                                                    //HEADERS AND INCLUSIONS
#include "bs.h"


//player ship ID'S
char pShipD[2] = {'d', 'd'};
char pShipS[3] = {'s', 's', 's'};
char pShipR[3] = {'r', 'r', 'r'};
char pShipB[4] = {'b', 'b', 'b', 'b'};
char pShipC[5] = {'c', 'c', 'c', 'c', 'c'};

//computer ship ID'S
char cShipD[2] = {'d', 'd'};
char cShipS[3] = {'s', 's', 's'};
char cShipR[3] = {'r', 'r', 'r'};
char cShipB[4] = {'b', 'b', 'b', 'b'};
char cShipC[5] = {'c', 'c', 'c', 'c', 'c'};

//Booleans that declare if a ship has been sunk where 'p' stands for player and 'c' stands for cpu
bool pshipD = false, pshipS = false, pshipR = false, pshipB = false, pshipC = false;
bool cshipD = false, cshipS = false, cshipR = false, cshipB = false, cshipC = false;


                                                    //GAMEBOARD GRAPHICS AND VISUALS
/**
 * @brief Holds the graphical display for the intro of the game
 * 
 * @param i //Makes it so that the latter half of the welcomes screen only prints one time ever
 */
void welcomeScreen(int i){
    cout << " ____________________________________________________________________________________________ \n"
         << "|  ________________________________________________________________________________________  |\n"
         << "| |    _____      ___   _____  _____  _      ______       ____   _    _   _____   ____     | |\n"
         << "| |   [  _  \\    / _ \\ [_   _][_   _][ ]    [ _____]     / ___] [ ]  [ ] [_   _] |  _ \\    | |\n"
         << "| |   | |_|  }  / [_] \\  | |    | |  | |    | |__       | |___  | |__| |   | |   | [_] |   | |\n"
         << "| |   |  __ <  /  ___  \\ | |    | |  | |    | ___}      |___  | |  __  |   | |   |  __/    | |\n"
         << "| |   | |__| }|  /   \\  || |    | |  | |___ | |____      ___| | | |  | |  _| |_  | |       | |\n"
         << "| |   [_____/ |__|   |__|[_]    [_]  [_____][______]    |____/  [_]  [_] [_____] [_]       | |\n"
         << "| |________________________________________________________________________________________| |\n"
         << "|____________________________________________________________________________________________|\n"
         << "\n";
    if (i == 0){
        cout << " ____________________________________________________________________________________________ \n"
             << "|  ________________________________________________________________________________________  |\n"
             << "| |                                                                                        | |\n"
             << "| |  HOW TO PLAY BATTLE SHIP!                                                              | |\n"
             << "| |                                                    __/___                              | |\n"
             << "| |  Carrier    - 5 Weakpoints                   _____/______|                             | |\n"
             << "| |  Battleship - 4 Weakpoints               ___/____/_______|____________                 | |\n"
             << "| |  Cruiser    - 3 Weakpoints              |_______/__________________   |                | |\n"
             << "| |  Submarine  - 3 Weakpoints              \\              < < <       | /                 | |\n"
             << "| |  Destroyer  - 2 Weakpoints           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                | |\n"
             << "| |                                                                                        | |\n"
             << "| |  OBJECT OF THE GAME: Be the first to sink all 5 of your opponent's ships.              | |\n"
             << "| |                                                                                        | |\n"
             << "| |  HOW TO PLAY                                                                           | |\n"
             << "| |    INPUT YOUR SHOT                                                                     | |\n"
             << "| |      - A-J for x-coordinate and 1-10 for y-coordinate                                  | |\n"
             << "| |      - On your turn, you may chose any space in the grid to attack. Shoot your shot    | |\n"
             << "| |        and wait to see if you HIT or MISS an opponents ships. Use the fired shots to   | |\n"
             << "| |        keep track of where you have hit and where you haven't.                         | |\n"
             << "| |                                                                                        | |\n"
             << "| |    HIT                                                                                 | |\n"
             << "| |      - A hit indicates that a part of the opponents battleship was in the square you   | |\n"
             << "| |        where your next move should be.                                                 | |\n"
             << "| |                                                                                        | |\n"
             << "| |    SINKING A SHIP                                                                      | |\n"
             << "| |      - When all the weakpoints on a ship have been discovered and HIT, a ship will     | |\n"
             << "| |        be SUNK and the total of SUNK ships adds up.                                    | |\n"
             << "| |________________________________________________________________________________________| |\n"
             << "|____________________________________________________________________________________________|\n"
             << "\n";
    }
}

/**
 * @brief Visibly displays inputed board which can be either the player board or the guess board.
 * 
 * @param board //dictates which board will be displayed at function call
 */
void displayBoard(char board[][NUM_COLS]){
    int tick = 0; //for 'public' i placeholder
    cout << " _______________________________________________ \n";
    cout << "|  ___________________________________________  |\n";
    cout << "| |    1   2   3   4   5   6   7   8   9   10 | |\n";
    cout << "| |                                           | |\n";
    for (int i = 0; i < NUM_ROWS; ++i){
        cout << "| | " << static_cast<char>('A'+i) << "  ";
        for (int k = 0; k < NUM_COLS; ++k){
            cout << board[i][k] << "  ";
            ++tick;
            if (tick%10 != 0){
                cout << " ";
            }
        }
        cout << "| |\n";
        if (tick != 100){
            cout << "| |                                           | |\n";
        }
    }
    cout << "| |___________________________________________| |\n";
    cout << "|_______________________________________________|\n\n";
}

/**
 * @brief Created different game boards for different use. (Player board, guess board, and cpu board)
 * 
 * @param board //Dictates which board is generated
 */
void initializeBoard(char board[][NUM_COLS]){
    for (int i = 0; i < NUM_ROWS; ++i){
        for (int k = 0; k < NUM_COLS; ++k){
            board[i][k] = '-';
        }
    }
}

//game rule functions and internals
/**
 * @brief 
 * 
 * @param array //Array that ships are to be placed on (Player board or CPU board)
 * @param row //Which row the ship will be placed
 * @param lane //Which lane the ship will be placed
 * @param face //Which direction the ship will face when placed
 * @param ship //Which ship will be placed
 * @param dontCoutCom //A boolean that tells program if a ship is already occupying a space
 */
void placeShips(char array[][10], int row, int lane, char face, char ship, bool &dontCoutCom)
{
    int shipSize=0, count = 0;
    if (ship == 'd')
    {
        shipSize = 2;
    }
    else if (ship == 's' || ship == 'r')
    {
        shipSize = 3;
    }
    else if (ship == 'b')
    {
        shipSize = 4;
    }
    else if (ship == 'c')
    {
        shipSize = 5;
    }
    else
    {
        if (dontCoutCom == true){
            cout << "no valid ship type.\n";
        }
    }
    if( face == 'h')
    {
        if (shipSize > (9 - lane) + 1 )
        {
            for(int t = 0; t < shipSize; ++t)
            {
                if (array[row][lane - t] != '-')
                {
                    count +=1;
                }
            }
        }
        else
        {
            for(int t = 0; t < shipSize; ++t)
            {
                if (array[row][lane + t] != '-')
                {
                    count +=1;
                }
            }
        }
    }
    if( face == 'v')
    {
        if (shipSize > (9 - row) + 1 )
        {
            for(int t = 0; t < shipSize; ++t)
            {
                if (array[row - t][lane] != '-')
                {
                    count +=1;
                }
            }
        }
        else
        {
            for(int t = 0; t < shipSize; ++t)
            {
                if (array[row + t][lane] != '-')
                {
                    count +=1;
                }
            }
        }
    }
    if(count == 0)
    {
        if (array[row][lane] == '-' && face == 'h')
        {
            if (shipSize > (9 - lane) + 1 )
            {
                for (int i = 0; i < shipSize; ++i)
                {
                array[row][lane - i] = ship;
                }
            }
            else
            {
                for (int i = 0; i < shipSize; ++i)
                {    
                    array[row][lane + i] = ship;
                }
            }
        }
        if (array[row][lane] == '-' && face == 'v')
        {
            if (shipSize > (9 - row) + 1 )
            {
                for (int j = 0; j < shipSize; ++j)
                {
                array[row - j][lane] = ship;
                }
            }
            else
            {
                for (int j = 0; j < shipSize; ++j)
                {    
                    array[row + j][lane] = ship;
                }
            }
        }
    }
    else
    {
        if (dontCoutCom == true){
            cout << "already a ship there. try again.\n";
        }
    }
}


/**
 * @brief Program that randomly places ships on invisible bot array
 * 
 * @param array //Dictates which array ships will be randomly placed(Should always be CPU's array)
 * @param row //Which row a ship is placed
 * @param lane //Which lane a ship is placed
 * @param ship //Which ship will be placed
 */
void computerPlaceShips(char array[][10], int row, int lane, char ship){
    int f = rand() % 2;
    char face;
    if(f == 0){
        face = 'v';
    }
    else{
        face = 'h';
    } 
    // ^ This is if face = 1.
    bool dontCoutCom = false;
    placeShips(array, row, lane, face, ship, dontCoutCom);
    dontCoutCom = false;
}


/**
 * @brief If all ships within a given passed array have their corresponding ship booleans all return true. Function chooses a winner
 * 
 * @return int //1 means CPU wins, 2 means Player wins, 0 means nobody has won yet
 */
int isWinner()
{
    if (pshipD == true && pshipS == true && pshipR == true && pshipB == true && pshipC == true )
    {
        return 1;
    }
    else if (cshipD == true && cshipS == true && cshipR == true && cshipB == true && cshipC == true )
    {
        return 2;   
    }
    else
    {
        return 0; 
    }
}


/**
 * @brief Checks to see how many hitpoints remain on a given ship and whether its been sunk yet.
 * 
 * @param shipArray //Which array it will check
 * @param letter // Which ship it is checking for
 * @param boolean //Whether the ship has sunk yet or not
 * @param shipSize //How many hitpoints the ship has
 * @param shipName //Official name of the ship
 * @param tick //Helps track back to back turns for each consecutive hit
 */
void shipMath(char shipArray[], char letter, bool boolean, int shipSize, string shipName, int & tick){
    for(int i = 0; i < shipSize; ++i) //size of ship
    {
        if(shipArray[i] == letter)
        {
            shipArray[i] = '*';
            break;
        }
    }
    for(int i = 0; i < shipSize; ++i) //size of ship
    {
        if(shipArray[i] == '*')
        {
            tick += 1;
        }
        if(shipArray[i] == letter)
        {
            tick -= 1;
        }
    }
    if(tick == shipSize)
    {
        cout << shipName << " has be sunk!\n";
        boolean = true;
    }
}

/**
 * @brief Updates board with most recent changes like a hit or miss for CPU
 * 
 * @param array //Array that is being updated
 * @param i //X position of update on 2d array
 * @param k //Y position of update on 2d array
 * @param shootAgain //Whether or not a player is allowed to shoot again after a successful hit
 * @param hits //How many hits are made throughout the game
 * @param misses //How many misses are made throughout the game
 */
void updateBoardCPU(char array[][NUM_COLS] ,int i, int k, bool &shootAgain, int &hits, int &misses)
{
    int tick = 0;
    if(array[i][k] == 'd' || array[i][k] == 's' || array[i][k] == 'r' || array[i][k] == 'b' || array[i][k] == 'c')
    {
        cout << "HIT!\n";
        ++hits;
        array[i][k] = '*';
        shootAgain = true; //every hit, you get to try again.
        if(array[i][k] == 'd')
        {
            //checks through Destroyer array[], tells when sunk.
            shipMath(cShipD, 'd', cshipD, 2, "Destroyer", tick);
        }
        if(array[i][k] == 's')
        {
            //checks through Submarine array[], tells when sunk.
            shipMath(cShipS, 's', cshipS, 3, "Submarine", tick);
        }
        if(array[i][k] == 'r')
        {
            //checks through Cruiser array[], tells when sunk.
            shipMath(cShipR, 'r', cshipR, 3, "Cruiser", tick);
        }
        if(array[i][k] == 'b')
        {
            //checks through Battleship array[], tells when sunk.
            shipMath(cShipB, 'b', cshipB, 4, "Battleship", tick);
        }
        if(array[i][k] == 'c')
        {
            //checks through Carrier array[], tells when sunk.
            shipMath(cShipC, 'c', cshipC, 5, "Carrier", tick);
        }
        array[i][k] = '*';
    }
    else
    {
        cout << "MISS!\n";
        ++misses;
        array[i][k] = 'o';
    }
}


/**
 * @brief Updates board with most recent changes like a hit or miss for Player
 * 
 * @param array //Array that is being updated
 * @param i //X position of update on 2d array
 * @param k //Y position of update on 2d array
 * @param shootAgain //Whether or not a player is allowed to shoot again after a successful hit
 * @param hits //How many hits are made throughout the game
 * @param misses //How many misses are made throughout the game
 */
void updateBoardPlayer(char array[][NUM_COLS], char array1[][NUM_COLS], int i, int k, bool &shootAgain, int &hits, int &misses)
{
    int tick = 0;
    if(array[i][k] == 'd' || array[i][k] == 's' || array[i][k] == 'r' || array[i][k] == 'b' || array[i][k] == 'c')
    {
        cout << "HIT!\n";
        ++hits;
        array[i][k] = '*';
        array1[i][k] = '*';
        shootAgain = true; //every hit, you get to try again.
        if(array[i][k] == 'd')
        {
            //checks through Destroyer array[], tells when sunk.
            shipMath(pShipD, 'd', pshipD, 2, "Destroyer", tick);
        }
        if(array[i][k] == 's')
        {
            //checks through Submarine array[], tells when sunk.
            shipMath(pShipS, 's', pshipS, 3, "Submarine", tick);
        }
        if(array[i][k] == 'r')
        {
            //checks through Cruiser array[], tells when sunk.
            shipMath(pShipR, 'r', pshipR, 3, "Cruiser", tick);
        }
        if(array[i][k] == 'b')
        {
            //checks through Battleship array[], tells when sunk.
            shipMath(pShipB, 'b', pshipB, 4, "Battleship", tick);
        }
        if(array[i][k] == 'c')
        {
            //checks through Carrier array[], tells when sunk.
            shipMath(pShipC, 'c', pshipC, 5, "Carrier", tick);
        }
        array[i][k] = '*';
    }
    else
    {
        cout << "MISS!\n";
        ++misses;
        array[i][k] = 'o';
        array1[i][k] = 'o';
    }
}


/**
 * @brief Checks to see if Bot Players move is valid. If not, repeats.
 * 
 * @param array // Game Board
 * @param i // X coordinate
 * @param k // Y coordinate
 * @return true // Move is valid
 * @return false // Move is not valid
 */
bool botCheck(char array[][NUM_COLS] ,int i, int k) 
{
    if(i > static_cast<int>('A')  && i < static_cast<int>('J') && k > 0 && k < 11)
    {
        if(array[i][k] == 'm' || array[i][k] == '*')
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

/**
 * @brief Randomly selects a location for the CPU to attack on Player's board
 * 
 * @return int //integer equivelent of a location to attack
 */
int botMove() 
{
    srand(time(NULL));
    int move = (rand()%10);
    return move;
}


/**
 * @brief Checks to see if all ships for all boards have been placed before game begins
 * 
 * @param array //Which board its checking to see if all ships are placed
 * @param rows //Runs down each row to check
 * @param cols //Runs down each column to check
 * @return true //All ships are placed
 * @return false //Not all ships are placed
 */
bool areShipsPlaced(char array[][NUM_COLS], int rows, int cols){
    int tick = 0;
    for (int i = 0; i < NUM_ROWS; ++i){ //double nested loop that checks if all ships have been placed.
        for (int k = 0; k < NUM_COLS; ++k){
            if (array[i][k] == SHIP_SYMBOLS[0] 
             || array[i][k] == SHIP_SYMBOLS[1] 
             || array[i][k] == SHIP_SYMBOLS[2] 
             || array[i][k] == SHIP_SYMBOLS[3] 
             || array[i][k] == SHIP_SYMBOLS[4]){
                ++tick;
            }
        }
    }
    if (tick == 17){
        if(tick > 17)
        {
            cout<<"Duplicate ship detected! Please replace ships..."<<endl;
            initializeBoard(array);
            return false;
        }
        return true;
    }
    return false;
}

/**
 * @brief Brief explanation of how to place each ship
 * 
 */
void shipPlacementInfo(){
    cout << "ITS TIME TO INITILIZE YOUR SHIPS:\n"
         << "   CHOOSE A LOCATION.\n"
         << "   EITHER VERTICAL OR HORIZONTAL.\n"
         << "   AND A SHIP CHARACTER\n"
         << "      c = carrier,\n"
         << "      b = battleship,\n"
         << "      r = cruiser,\n"
         << "      s = submarine,\n"
         << "      d = destroyer.\n"
         << "EX: (x y v/h ship) .. (b 9 v c)\n"
         << "    it will place a carrier in b9 vertically.\n";
}


/**
 * @brief Checks to see if player has entered an appropriate response to ship placement and/or attack location(Not case sensitive)
 * 
 * @param enterXInt //Chosen value
 * @return true //Input is valid
 * @return false //Input is invalid
 */
bool isCorrectValue(int enterXInt){
    if (isCapital(enterXInt)){
        return true;
    }
    if (isLowercase(enterXInt)){
        return true;
    }
    return false;
}


/**
 * @brief Takes user input for EXACTLY where player wants each ship to be placed on player board
 * 
 * @param enterXLetter //X coordinate of ship head
 * @param enterY //Y coordinate of ship head
 * @param vertOrHori //Direction ship will face
 * @param enterShip //Which ship is being placed
 * @param enterXInt // X coordinate of ship head, converted from letter to integer
 */
void shipUserInput(char &enterXLetter, int &enterY, char &vertOrHori, char &enterShip, int &enterXInt){
    enterXLetter = ' ';
    enterXInt = -1;
    while(!isCorrectValue(static_cast<int>(enterXLetter))){
        cout << "Please enter an X value (a-j): ";
        cin >> enterXLetter;
    }
    bool isInputDone = false;
    while(!isInputDone){
        cout << "Please enter a Y value (1-10): ";
        cin >> enterY;
        if (enterY >= 1 && enterY <= 10){isInputDone = true;}
    }
    isInputDone = false;
    while(!isInputDone){
        cout << "Please enter a ship orientation (v/h): ";
        cin >> vertOrHori;
        if(vertOrHori != 'v' || vertOrHori != 'h' || vertOrHori != 'V' || vertOrHori != 'H'){isInputDone = true;}
    }
    isInputDone = false;
    while(!isInputDone){
        cout << "Please enter a ship character (c, b, r, s, d): ";
        cin >> enterShip;
        if(enterShip != 'c' || enterShip != 'b' || enterShip != 'r' || enterShip != 's' || enterShip != 'd' || 
           enterShip != 'C' || enterShip != 'B' || enterShip != 'R' || enterShip != 'S' || enterShip != 'D')
            {isInputDone = true;}
    }
    //logic for capital or lowercase input.
    enterXInt = static_cast<int>(enterXLetter);
    if (enterXInt >= 65 && enterXInt <= 74){ //capital case
        enterXInt -= 65;
    }
    if (enterXInt >= 97 && enterXInt <= 106){ //lower case
        enterXInt -= 97;
    }
    --enterY;
}


/**
 * @brief 'Tosses a coin' to see who has the first turn at the start of the game
 * 
 * @return int Value represents heads or tails based on what the player 'called'
 */
int coinFlip(){
    char headsOrTails = ' ';
    cout << "\nALL SHIPS HAVE BEEN PLACED, COIN FLIP:\n PLEASE ENTER 'h' FOR HEADS OR 't' FOR TAILS!\n";
    cin >> headsOrTails;
    if (headsOrTails == 'h'){
        if (rand() % 2 == 0){
            cout << "Heads, Player 1 goes first\n";
            return 0;                               // 0 = player1 starts
        } else {
            cout << "Tails, Computer goes first\n";
            return 1;                               // 1 = computer starts
        }
    } else if (headsOrTails == 't') {
        if (rand() % 2 == 0){
            cout << "Tails, Player 1 goes first\n";
            return 0;                               // 0 = player1 starts
        } else {
            cout << "Heads, Computer goes first\n";
            return 1;                               // 1 = computer starts
        }
    } else {
        cout << "...Invalid Choice.. Choose again...\n";
        return 2;                                   // 2 = choose again
    }
    cout << "...Input not recieved.. Choose again...\n";
    return 2;                                       // 2 = choose again
}


/**
 * @brief Records any important game results int logFile.txt for summary use
 * 
 * @param turns //How many turns were taken through the game
 * @param miss //How many misses
 * @param hit //How many hits
 * @param winner //Winner of the game
 */
void logFile(int turns, int miss, int hit, int winner)
{
    double ratio = ((static_cast<double>(hit) / (hit + miss))*100);
    ofstream logFile;
    logFile.open("logfile.txt");

    if(!logFile)
    {
        cout<<"Error opening log file! Cannot record results. Please check to make sure 'logfile.txt' exists!!"<<endl;
    }
    else
    {
        logFile << "Player took " << turns <<" throughout the game, and fired "<<(miss + hit)<<" shots"<<endl;
        logFile << "Player missed "<< miss <<" shots,"<<endl;
        logFile << "and hit "<< hit <<" shots"<<endl;
        logFile << endl;
        if(cshipC == true)
        {
            logFile <<"Enemy Carrier(5) has been sunk"<<endl;
        }
        if(cshipB == true)
        {
            logFile << "Enemy Battleship(4) has been sunk"<<endl;
        }
        if(cshipR == true)
        {
            logFile << "Enemy Cruiser(3) has been sunk"<<endl;
        }
        if(cshipS == true)
        {
            logFile << "Enemy Submarine(3) has been sunk"<<endl;
        }
        if(cshipD == true)
        {
            logFile << "Enemy Destroyer(2) has been sunk"<<endl;
        }
        if(pshipC == true)
        {
            logFile <<"Player Carrier(5) has been sunk"<<endl;
        }
        if(pshipB == true)
        {
            logFile << "Player Battleship(4) has been sunk"<<endl;
        }
        if(pshipR == true)
        {
            logFile << "Player Cruiser(3) has been sunk"<<endl;
        }
        if(pshipS == true)
        {
            logFile << "Player Submarine(3) has been sunk"<<endl;
        }
        if(pshipD == true)
        {
            logFile << "Player Destroyer(2) has been sunk"<<endl;
        }
        logFile << "Accuracy Ratio: %"<<ratio<<endl;
        logFile << "Final Result: "<<endl;
        if(winner == 0) 
        {
            logFile << "Player won!" <<endl;
        }
        else
        {
            logFile << "CPU won!" <<endl;
        }
    }
}

/**
 * @brief Corrects case sensitive inputs from player
 * 
 * @param enterXInt letter input by player
 * @return true //Is a capital letter
 * @return false //Is not a capital letter
 */
bool isCapital(int enterXInt){
    if (enterXInt >= 65 && enterXInt <= 74){ //capital case
        return true;
    }
    return false;
}


/**
 * @brief Corrects case sensitive inputs from player
 * 
 * @param enterXInt letter input by player
 * @return true //Is a lower case letter
 * @return false //Is not a lower case letter
 */
bool isLowercase(int enterXInt){
    if (enterXInt >= 97 && enterXInt <= 106){ //lower case
        return true;
    }
    return false;
}


/**
 * @brief Uses random number generated from botMove to determine where the CPU will attack the player
 * 
 * @param array //Player array the CPU attacks
 * @param shootAgain //Whether there was a successful hit and if the CPU can go again
 * @param hits //Tracks hits for logFile()
 * @param misses //Tracks misses for logFile()
 */
void cpuMove(char array[][NUM_COLS], bool &shootAgain, int &hits, int &misses)
{
    int x = rand()%10,
    y = rand()%10;

    cout << "Firing at: " << static_cast<char>(x+65) << y+1 << "\n";
    sleep(PLAYER_TIME);
    updateBoardCPU(array, x, y, shootAgain, hits, misses);
    displayBoard(array);
    sleep(CPU_TIME);
}


/**
 * @brief Small graphic displaying whos turn it is
 * 
 * @param person //Turn based on 'tick' counter in main.cpp
 */
void playersTurn(int person){
    if(person == 0){
        cout << " _____________________ \n"
             << "|  _________________  |\n"
             << "| |                 | |\n"
             << "| | PLAYER 1'S TURN | |\n"
             << "| |_________________| |\n"
             << "|_____________________|\n\n";
    } else if (person == 1){
        cout << " _____________________ \n"
             << "|  _________________  |\n"
             << "| |                 | |\n"
             << "| | COMPUTER'S TURN | |\n"
             << "| |_________________| |\n"
             << "|_____________________|\n\n";
    }
}

/**
 * @brief Randomly places ships all over array if player does not want to do it manually or for initial bot placements
 * 
 * @param array //Which array ships are randomly placed=
 */
void randomlyPlaceShips(char array[][NUM_COLS]){
    while(!areShipsPlaced(array, NUM_ROWS, NUM_COLS)){//did they place correctly? if not:
        initializeBoard(array);//      it will restart the process
        for(int i = 0; i <= 5; i++){                     
            computerPlaceShips(array, rand() % 10 + 1, rand() % 10 + 1, SHIP_SYMBOLS[i]); //will place each
        }                                                                                    //  ship once
    }
}

/**
 * @brief Manually place ships gives the user total control of the input while placing ships.
 *          compressing long lines of sequences to 1 function.
 * @param array board that we are passing through to be modified
 * @param enterXLetter X coordinate of ship head
 * @param enterY Y coordinate of ship head
 * @param vertOrHori variable representing user's choice between vertical or horizontal, 
 * @param enterShip Which ship is being placed
 * @param enterXInt X coordinate of ship head, converted from letter to integer
 * @param dontCoutCom cout statements for placeShips will be played 
 *                    if bot uses the function too, this is to prevent that.
 */
void manuallyPlaceShips(char array[][NUM_COLS], char &enterXLetter, int &enterY, char &vertOrHori, char &enterShip, int &enterXInt, bool &dontCoutCom){    
    shipPlacementInfo();
    int placeShipInt = 0;
    while(!areShipsPlaced(array, NUM_ROWS, NUM_COLS)){ //while all ships arent placed
        if (placeShipInt > 0){cout << "Place your next ship.\n";} //only doesn't display first time
        ++placeShipInt;
        displayBoard(array);
        shipUserInput(enterXLetter, enterY, vertOrHori, enterShip, enterXInt);
        dontCoutCom = true; //this is a bool for only saying helpful cout's during players turn and not bot's.
        placeShips(array, enterXInt, enterY, vertOrHori, enterShip, dontCoutCom);
    }
    dontCoutCom = false;
    displayBoard(array);
}