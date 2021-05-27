//-------------------------------------------
// Created by Patrick Mbanusi on 05 /05/2021.
//-------------------------------------------

#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef MAIN_C_MAIN_H
#define MAIN_C_MAIN_H

enum {
    Up, Up_Right, Right, Down_Right, Down, Down_Left, Left, Up_Left
};

// Node that represent single position on board
struct Node {
    char letter;
    int digit;
    char disk;
};

// Structure for player
struct Player {
    char player[100];
    int score;
};

// Structure for board that contains player and 2-D array of nodes
struct Board {
    struct Node node[8][8];
    struct Player black;
    struct Player white;
};


// Structure to store valid positions for current player;
struct PossiblePoints {
    char letter;
    int digit;
    int count;
    int direction;
};

struct Board board;
struct PossiblePoints possiblePoints[64];

// Function to print board and score
void printTable();

// Function that initialises board and places 4 disks on the board
void setUpGame();

// Function to calculate score after every move to update score
void scoreCalculate();

// Function to check the format of input enter by user
// and convert into array index to be used by program
int nodeInput(char *, int *, int *);

// Function that check for the valid position to place a disk by current player
int validMoves(char);

// Sort the array on the bases of max number of disk
void sortValidNode(int num);

// Function to place new disk and change the disk in between them
void moveDisk(int, char, int, int);

// Function to print final result and store data to file
void printResult();


#endif //MAIN_C_MAIN_H
