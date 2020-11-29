#pragma once
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ENTER 13

bool PasswordLoop = true;
char PasswordLetter = 'A';
char PasswordInput = 'A';
char StoredPasswordLetter = ' ';
char PasswordArray[10];
char PasswordCorrectArray[10];
int PasswordCodeNumber = 0;
int PlayerX = 0;
int PlayerY = 0;
char EnteredCode = ' ';
int PasswordCorrect = 0;
bool Unlocked = false;

bool MenuLoop = true;
int MenuSelection = 0;

bool GameLoop = true;

const int width = 6;
const int height = 6;
char board[width][height];
char AIboard[width][height];

int sideNumbers = height;
char bottomLetters = 'A';

int numberOfShips = 11;
int numberOfHits = 1;
int numberOfShots = 20;
int numberOfPlayerShips = 11;

const char BLANK = ' ';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = '-';

int ShipRandomRow;
int ShipRandomColumn;

char playerShotColumn;
int playerShotRow;
int playerShotColumnNumber;

int row = 0;
int column = 0;