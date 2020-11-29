#include <iostream>
#include <windows.h>
#include "Variables.h"
#include <conio.h>
#include <fstream>
#include <string>
#include <time.h>

void Password();
void PasswordCompare();
void PasswordChange();
void play();
void multiplay();
void makeEmptyBoard();
int randomRow();
int randomColumn();
void writeLetters();
void printBoard();
void makeBoard(int numberOfShips);
void printPlayerBoard();
void shoot();
int letterToNumber(char playerShotColumn);
void makeBoard3(int numberOfShips);
void printMultiBoard();
void AItargeting();
void makeAIBoard3(int numberOfShips);
void makeEmptyAIBoard();

int main()
{ 
    srand((unsigned)time(0));
    Password();
    do {
        system("cls");
        std::cout << "Please select an option.\n 1: Change password.\n 2: Play Battleship.\n 4: Play Battleship vs AI. \n 4: Quit. \n";
        std::cin >> MenuSelection;
        switch (MenuSelection) {
        case 1: {
            PasswordChange();
            break;
        }
        case 2: {
            play();
            break;
        }
        case 3: {
            multiplay();
            break;
        }
        case 4: {
            MenuLoop = false;
            break;
        }
        default: {
            break;
        }
        }
    } while (MenuLoop == true);
}

void Password() {
    do {
        PlayerX = 0;
        PlayerY = 0;
        PasswordCodeNumber = 0;
        PasswordLoop = true;
        do {
            PasswordLetter = 'A';
            system("cls");
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    std::cout << "[";
                    if (PlayerX == j && PlayerY == i) {
                        std::cout << "*";
                        StoredPasswordLetter = PasswordLetter;
                    }
                    else {
                        std::cout << PasswordLetter;
                    }
                    std::cout << "]";
                    PasswordLetter++;
                }
                std::cout << "\n";
            }
            for (int o = 0; o < PasswordCodeNumber; o++) {
                std::cout << PasswordArray[o] << " ";
            }
            PasswordInput = _getch();
            if (PasswordInput == KEY_LEFT && PlayerX != 0) {
                PlayerX--;
            }
            if (PasswordInput == KEY_RIGHT && PlayerX != 3) {
                PlayerX++;
            }
            if (PasswordInput == KEY_UP && PlayerY != 0) {
                PlayerY--;
            }
            if (PasswordInput == KEY_DOWN && PlayerY != 3) {
                PlayerY++;
            }
            if (PasswordInput == ENTER) {
                PasswordArray[PasswordCodeNumber] = StoredPasswordLetter;
                PasswordCodeNumber++;
            }
            if (PasswordCodeNumber == 10) {
                PasswordLoop = false;
            }
        } while (PasswordLoop == true);
        PasswordCompare();
        if (Unlocked == true) {
            system("cls");
            std::cout << "Unlocked!\n";
            system("pause");
        }
        else {
            system("cls");
            std::cout << "Password Failure!\n";
            system("pause");
        }
    } while (Unlocked != true);
}

void PasswordCompare() {
    PasswordCorrect = 0;
    std::ifstream myfile;
    myfile.open("password.txt");
    for (int u = 0; u < 9; u++) {
        myfile >> PasswordCorrectArray[u];
    }
    myfile.close();
    for (int k = 0; k < 10; k++) {
        if (PasswordArray[k] == PasswordCorrectArray[k]) {
            PasswordCorrect++;
        }
    }
    if (PasswordCorrect == 9) {
        Unlocked = true;
    }
}

void PasswordChange() {
    PlayerX = 0;
    PlayerY = 0;
    PasswordCodeNumber = 0;
    PasswordLoop = true;
    do {
        PasswordLetter = 'A';
        system("cls");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << "[";
                if (PlayerX == j && PlayerY == i) {
                    std::cout << "*";
                    StoredPasswordLetter = PasswordLetter;
                }
                else {
                    std::cout << PasswordLetter;
                }
                std::cout << "]";
                PasswordLetter++;
            }
            std::cout << "\n";
        }
        for (int o = 0; o < PasswordCodeNumber; o++) {
            std::cout << PasswordArray[o] << " ";
        }
        PasswordInput = _getch();
        if (PasswordInput == KEY_LEFT && PlayerX != 0) {
            PlayerX--;
        }
        if (PasswordInput == KEY_RIGHT && PlayerX != 3) {
            PlayerX++;
        }
        if (PasswordInput == KEY_UP && PlayerY != 0) {
            PlayerY--;
        }
        if (PasswordInput == KEY_DOWN && PlayerY != 3) {
            PlayerY++;
        }
        if (PasswordInput == ENTER) {
            PasswordArray[PasswordCodeNumber] = StoredPasswordLetter;
            PasswordCodeNumber++;
        }
        if (PasswordCodeNumber == 10) {
            PasswordLoop = false;
        }
    } while (PasswordLoop == true);
    std::ofstream myfile;
    myfile.open("password.txt");
    for (int u = 0; u < 10; u++) {
        myfile << PasswordArray[u];
    }
    myfile.close();
}

void play() {
    std::cout << "Please enter the number of ships you want to face off against:";
    std::cin >> numberOfShips;
    std::cout << "Now enter the amount of shots you want to have:";
    std::cin >> numberOfShots;
    numberOfHits = 1;
    makeEmptyBoard();
    do {
        system("cls");
        printPlayerBoard();
        if (numberOfShots == 0 || numberOfShips == 0) {
            GameLoop = false;
        }
        if (GameLoop == true) {
            shoot();
        }
    } while (GameLoop == true);
    if (numberOfShips == 0) {
        std::cout << "\nCongratulations! You win!\n";
        system("pause");
    }
    else {
        std::cout << "\nYou lose...\n";
        system("pause");
    }
}

void makeEmptyBoard() {
    for (int a = 0; a < height; a++) {
        for (int b = 0; b < width; b++) {
            board[b][a] = BLANK; 
        }
    }
    makeBoard3(numberOfShips);
}

void printBoard() {
    sideNumbers = height;
    for (int a = 0; a < height; a++) {
        for (int b = 0; b < width+1; b++) {
            if (b == 0) {
                std::cout << sideNumbers;
                sideNumbers--;
            }
            else {
                std::cout << "[" << board[b][a] << "]";
            }
        }
        std::cout << "\n";
    }
    writeLetters();
}

int randomRow() {
    row = (rand() % height) + 1;
    return row;
}

int randomColumn() {
    column = (rand() % width) + 1;
    return column;
}

void writeLetters() {
    bottomLetters = 'A';
    std::cout << "-";
    int numberOfLetters = width+1;
    for (int v = 1; v < numberOfLetters; v++) {
        std::cout << "---";
    }
    std::cout << "\n";
    for (int u = 0; u < numberOfLetters; u++) {
        if (u == 0) {
            std::cout << " ";
        }
        else {
            std::cout << "[" << bottomLetters << "]";
            bottomLetters++;
        }
    }
}

void makeBoard(int numberOfShips) {
    for (int h = 0; h < numberOfShips; h++) {
         int ShipRandomRow = (rand() % width);
         int ShipRandomColumn = (rand() % height);
         if (board[ShipRandomRow][ShipRandomColumn] == BLANK) {
             board[ShipRandomRow][ShipRandomColumn] = SHIP;
         }
         else {
             h--;
         }
    }
}

void printPlayerBoard() {
    sideNumbers = height;
    for (int a = 0; a < height; a++) {
        std::cout << sideNumbers;
        sideNumbers--;
        for (int b = 0; b < width; b++) {
            if (board[b][a] == SHIP) {
                std::cout << "[" << BLANK << "]";
            }
            else {
                std::cout << "[" << board[b][a] << "]";
            }
        }
        std::cout << "\n";
    }
    writeLetters();
    std::cout << "\nRemaining ships: " << numberOfShips << " Shots left: " << numberOfShots << " Number of hits: " << numberOfHits-1; //For some reason setting numberOfHits to 0 messes up the std::cout.
}

void shoot() {
    std::cout << "\nPlease select a row to fire in (1-" << height << "): ";
    std::cin >> playerShotRow;
    playerShotRow = height - playerShotRow;
    std::cout << "Please select a column to fire in (A-" << bottomLetters << "); \n";
    std::cin >> playerShotColumn;
    numberOfShots--;
    if (islower(playerShotColumn)) {
        playerShotColumn = toupper(playerShotColumn);
    }
    playerShotColumnNumber = letterToNumber(playerShotColumn);
    if (board[playerShotColumnNumber][playerShotRow] == HIT) {
        std::cout << "You have already fired there.\n";
    }
    else if (board[playerShotColumnNumber][playerShotRow] == MISS) {
        std::cout << "You have already fired there.\n";
    }
    else if (board[playerShotColumnNumber][playerShotRow] == BLANK) {
        std::cout << "MISS!\n";
        board[playerShotColumnNumber][playerShotRow] = MISS;
    }
    else if (board[playerShotColumnNumber][playerShotRow] == SHIP) {
        std::cout << "SUCCESSFUL HIT!\n";
        numberOfHits++;
        numberOfShips--;
        board[playerShotColumnNumber][playerShotRow] = HIT;
    }
    system("pause");
}

int letterToNumber(char playerShotColumn) // only big letters
{
    return static_cast<int>(playerShotColumn) - 64;
}

void makeBoard3(int numberOfShips) {
    for (int h = 0; h < numberOfShips; h++) {
        ShipRandomRow = (rand() % width)+1;
        ShipRandomColumn = (rand() % height);
        if (ShipRandomRow < width && board[ShipRandomRow][ShipRandomColumn] == BLANK) {
            if (board[ShipRandomRow + 1][ShipRandomColumn] == BLANK) {
                if (board[ShipRandomRow - 1][ShipRandomColumn] == BLANK) {
                    board[ShipRandomRow][ShipRandomColumn] = SHIP;
                    board[ShipRandomRow+1][ShipRandomColumn] = SHIP;
                    board[ShipRandomRow-1][ShipRandomColumn] = SHIP;
                }
                else {
                    h--;
                }
            }
            else {
                h--;
            }
        }
        else if (ShipRandomRow >= width || board[ShipRandomRow][ShipRandomColumn] != BLANK) {
            h--;
        }
        ShipRandomRow = (rand() % width);
        ShipRandomColumn = (rand() % height);
        if (ShipRandomColumn < height && board[ShipRandomRow][ShipRandomColumn] == BLANK) { //The vertical ships will sometimes go down too far and end up on the top to the right. Couldn't figure out why that happened.
            if (board[ShipRandomRow][ShipRandomColumn + 1] == BLANK) {
                if (board[ShipRandomRow][ShipRandomColumn - 1] == BLANK) {
                    board[ShipRandomRow][ShipRandomColumn] = SHIP;
                    board[ShipRandomRow][ShipRandomColumn + 1] = SHIP;
                    board[ShipRandomRow][ShipRandomColumn - 1] = SHIP;
                }
                else {
                    h--;
                }
            }
            else {
                h--;
            }
        }
        else if (ShipRandomColumn >= height || board[ShipRandomRow][ShipRandomColumn] != BLANK) {
            h--;
        }
    }
}

void multiplay() {
    std::cout << "Please enter the number of ships you want each side to have:";
    std::cin >> numberOfShips;
    std::cout << "Now enter the amount of shots you want to have:";
    std::cin >> numberOfShots;
    numberOfHits = 1;
    makeEmptyBoard();
    makeEmptyAIBoard();
    do {
        system("cls");
        printPlayerBoard();
        if (numberOfShots == 0 || numberOfShips == 0) {
            GameLoop = false;
        }
        if (GameLoop == true) {
            shoot();
        }
        AItargeting();
        printMultiBoard();
    } while (GameLoop == true);
    if (numberOfShips == 0 && numberOfPlayerShips > 0) {
        std::cout << "\nCongratulations! You win!\n";
        system("pause");
    }
    else if (numberOfShots == 0 && numberOfShips < numberOfPlayerShips) {
        std::cout << "\nCongratulations! You win!\n";
        system("pause");
    }
    else {
        std::cout << "\nYou lose...\n";
        system("pause");
    }
}

void printMultiBoard() {
    sideNumbers = height;
    for (int a = 0; a < height; a++) {
        std::cout << sideNumbers;
        sideNumbers--;
        for (int b = 0; b < width; b++) {
            if (AIboard[b][a] == SHIP) {
                std::cout << "[" << BLANK << "]";
            }
            else {
                std::cout << "[" << AIboard[b][a] << "]";
            }
        }
        std::cout << "\n";
    }
    writeLetters();
    std::cout << "\nYour ships left: " << numberOfPlayerShips;
    system("pause");
}

void makeEmptyAIBoard() {
    for (int a = 0; a < height; a++) {
        for (int b = 0; b < width; b++) {
            AIboard[b][a] = BLANK;
        }
    }
    makeAIBoard3(numberOfShips);
}

void makeAIBoard3(int numberOfShips) {
    for (int h = 0; h < numberOfShips; h++) {
        ShipRandomRow = (rand() % width) + 1;
        ShipRandomColumn = (rand() % height);
        if (ShipRandomRow < width && board[ShipRandomRow][ShipRandomColumn] == BLANK) {
            if (AIboard[ShipRandomRow + 1][ShipRandomColumn] == BLANK) {
                if (AIboard[ShipRandomRow - 1][ShipRandomColumn] == BLANK) {
                    AIboard[ShipRandomRow][ShipRandomColumn] = SHIP;
                    AIboard[ShipRandomRow + 1][ShipRandomColumn] = SHIP;
                    AIboard[ShipRandomRow - 1][ShipRandomColumn] = SHIP;
                }
                else {
                    h--;
                }
            }
            else {
                h--;
            }
        }
        else if (ShipRandomRow >= width || AIboard[ShipRandomRow][ShipRandomColumn] != BLANK) {
            h--;
        }
        ShipRandomRow = (rand() % width);
        ShipRandomColumn = (rand() % height);
        if (ShipRandomColumn < height && AIboard[ShipRandomRow][ShipRandomColumn] == BLANK) { //The vertical ships will sometimes go down too far and end up on the top to the right. Couldn't figure out why that happened.
            if (AIboard[ShipRandomRow][ShipRandomColumn + 1] == BLANK) {
                if (AIboard[ShipRandomRow][ShipRandomColumn - 1] == BLANK) {
                    AIboard[ShipRandomRow][ShipRandomColumn] = SHIP;
                    AIboard[ShipRandomRow][ShipRandomColumn + 1] = SHIP;
                    AIboard[ShipRandomRow][ShipRandomColumn - 1] = SHIP;
                }
                else {
                    h--;
                }
            }
            else {
                h--;
            }
        }
        else if (ShipRandomColumn >= height || AIboard[ShipRandomRow][ShipRandomColumn] != BLANK) {
            h--;
        }
    }
}

void AItargeting() {
    playerShotRow = (rand() % width);
    playerShotColumn = (rand() % height);
    for (int l = 0; l < 1; l++) {
        if (AIboard[playerShotColumnNumber][playerShotRow] == MISS || AIboard[playerShotColumnNumber][playerShotRow] == HIT) {
            playerShotRow = (rand() % width);
            playerShotColumn = (rand() % height);
            l--;
        }
    }
    if (AIboard[playerShotColumnNumber][playerShotRow] == BLANK) {
        AIboard[playerShotColumnNumber][playerShotRow] = MISS;
    }
    else if (board[playerShotColumnNumber][playerShotRow] == SHIP) {
        numberOfPlayerShips--;
        AIboard[playerShotColumnNumber][playerShotRow] = HIT;
    }
}
