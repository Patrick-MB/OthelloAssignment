//-------------------------------------------
// Created by Patrick Mbanusi on 05/05/2021.
//-------------------------------------------

#include "game.h"

void printResult(){
    FILE *file;
    file = fopen("othello-results.txt","a");

    time_t t;   // not a primitive datatype
    time(&t);

    char *gameTime = ctime(&t);

    printf("\n** Game Over ** - Time %s\n",gameTime);
    // if both players have the same score...
    if (board.black.score == board.white.score) {

        fprintf(file,"%s, %d, %s\n","draw",board.white.score,gameTime);
        printf("\n** Match Draw **\n");

    } else if (board.black.score > board.white.score) {

        printf("\n** %s (Black) Won The Match **\n", board.black.player);
        fprintf(file,"%s, %d, %s\n",board.black.player,board.black.score,gameTime);

    } else {

        printf("\n** %s (White) Won The Match **\n", board.white.player);
        fprintf(file,"%s, %d, %s\n",board.white.player,board.white.score,gameTime);

    }
    fclose(file);
}

void moveDisk(int i, char color, int m, int n) {

    if (possiblePoints[i].direction == Up) {
        for (int j = 0; j <= possiblePoints[i].count; ++j) {
            board.node[m - j][n].disk = color;
        }
    } else if (possiblePoints[i].direction == Down) {
        for (int j = 0; j <= possiblePoints[i].count; ++j) {
            board.node[m + j][n].disk = color;
        }
    } else if (possiblePoints[i].direction == Right) {
        for (int j = 0; j <= possiblePoints[i].count; ++j) {
            board.node[m][n + j].disk = color;
        }
    } else if (possiblePoints[i].direction == Left) {
        for (int j = 0; j <= possiblePoints[i].count; ++j) {
            board.node[m][n - j].disk = color;
        }
    } else if (possiblePoints[i].direction == Up_Right) {
        for (int j = 0; j <= possiblePoints[i].count; ++j) {
            board.node[m - j][n + j].disk = color;
        }
    } else if (possiblePoints[i].direction == Down_Left) {
        for (int j = 0; j <= possiblePoints[i].count; ++j) {
            board.node[m + j][n - j].disk = color;
        }
    } else if (possiblePoints[i].direction == Down_Right) {
        for (int j = 0; j <= possiblePoints[i].count; ++j) {
            board.node[m + j][n + j].disk = color;
        }
    } else if (possiblePoints[i].direction == Up_Left) {
        for (int j = 0; j <= possiblePoints[i].count; ++j) {
            board.node[m - j][n - j].disk = color;
        }
    }
}

int validMoves(char diskColor) {

    int digit = 0;
// check all positions in all directions
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board.node[i][j].disk == diskColor) {

                // Vertically Down
                if (i > 0 && board.node[i - 1][j].disk == ' ') {
                    int count = 1;
                    for (int k = i + 1; k < 8; ++k) {
                        if (board.node[k][j].disk != diskColor) {

                            if (board.node[k][j].disk == ' ') {
                                break;
                            } else {
                                possiblePoints[digit].letter = board.node[i - 1][j].letter;
                                possiblePoints[digit].digit = board.node[i - 1][j].digit;
                                possiblePoints[digit].count = count;
                                possiblePoints[digit].direction = Down;
                                digit++;
                                break;
                            }

                        } else {
                            count++;
                        }
                    }
                }

                // Vertically Up
                if (i < 7 && board.node[i + 1][j].disk == ' ') {
                    int count = 1;
                    for (int k = i - 1; k >= 0; --k) {
                        if (board.node[k][j].disk != diskColor) {

                            if (board.node[k][j].disk == ' ') {
                                break;
                            } else {
                                possiblePoints[digit].letter = board.node[i + 1][j].letter;
                                possiblePoints[digit].digit = board.node[i + 1][j].digit;
                                possiblePoints[digit].count = count;
                                possiblePoints[digit].direction = Up;
                                digit++;
                                break;
                            }

                        } else {
                            count++;
                        }
                    }
                }

                // Right
                if (j > 0 && board.node[i][j - 1].disk == ' ') {
                    int count = 1;
                    for (int k = j + 1; k < 8; ++k) {
                        if (board.node[i][k].disk != diskColor) {

                            if (board.node[i][k].disk == ' ') {
                                break;
                            } else {
                                possiblePoints[digit].letter = board.node[i][j - 1].letter;
                                possiblePoints[digit].digit = board.node[i][j - 1].digit;
                                possiblePoints[digit].count = count;
                                possiblePoints[digit].direction = Right;
                                digit++;
                                break;
                            }

                        } else {
                            count++;
                        }
                    }
                }

                // Left
                if (j < 7 && board.node[i][j + 1].disk == ' ') {
                    int count = 1;
                    for (int k = j - 1; k >= 0; --k) {
                        if (board.node[i][k].disk != diskColor) {

                            if (board.node[i][k].disk == ' ') {
                                break;
                            } else {
                                possiblePoints[digit].letter = board.node[i][j + 1].letter;
                                possiblePoints[digit].digit = board.node[i][j + 1].digit;
                                possiblePoints[digit].count = count;
                                possiblePoints[digit].direction = Left;
                                digit++;
                                break;
                            }

                        } else {
                            count++;
                        }
                    }
                }

                // Down Right
                if (j > 0 && i > 0 && board.node[i - 1][j - 1].disk == ' ') {
                    int k = 1;

                    while (i + k < 8 && j + k < 8) {

                        if (board.node[i + k][j + k].disk != diskColor) {

                            if (board.node[i + k][j + k].disk == ' ') {
                                break;
                            } else {
                                possiblePoints[digit].letter = board.node[i - 1][j - 1].letter;
                                possiblePoints[digit].digit = board.node[i - 1][j - 1].digit;
                                possiblePoints[digit].count = k;
                                possiblePoints[digit].direction = Down_Right;
                                digit++;
                                break;
                            }

                        } else {
                            k++;
                        }
                    }
                }

                // Up Right
                if (j > 0 && i < 7 && board.node[i + 1][j - 1].disk == ' ') {
                    int k = 1;

                    while (i - k > -1 && j + k < 8) {

                        if (board.node[i - k][j + k].disk != diskColor) {

                            if (board.node[i - k][j + k].disk == ' ') {
                                break;
                            } else {
                                possiblePoints[digit].letter = board.node[i + 1][j - 1].letter;
                                possiblePoints[digit].digit = board.node[i + 1][j - 1].digit;
                                possiblePoints[digit].count = k;
                                possiblePoints[digit].direction = Up_Right;
                                digit++;
                                break;
                            }

                        } else {
                            k++;
                        }
                    }
                }

                // Up Left
                if (j < 7 && i < 7 && board.node[i + 1][j + 1].disk == ' ') {
                    int k = 1;

                    while (i - k > 0 && j - k > 0) {

                        if (board.node[i - k][j - k].disk != diskColor) {

                            if (board.node[i - k][j - k].disk == ' ') {
                                break;
                            } else {
                                possiblePoints[digit].letter = board.node[i + 1][j + 1].letter;
                                possiblePoints[digit].digit = board.node[i + 1][j + 1].digit;
                                possiblePoints[digit].count = k;
                                possiblePoints[digit].direction = Up_Left;
                                digit++;
                                break;
                            }

                        } else {
                            k++;
                        }
                    }
                }

                // Down Left
                if (j < 7 && i > 0 && board.node[i - 1][j + 1].disk == ' ') {
                    int k = 1;

                    while (i + k < 8 && j - k > -1) {

                        if (board.node[i + k][j - k].disk != diskColor) {

                            if (board.node[i + k][j - k].disk == ' ') {
                                break;
                            } else {
                                possiblePoints[digit].letter = board.node[i - 1][j + 1].letter;
                                possiblePoints[digit].digit = board.node[i - 1][j + 1].digit;
                                possiblePoints[digit].count = k;
                                possiblePoints[digit].direction = Down_Left;
                                digit++;
                                break;
                            }

                        } else {
                            k++;
                        }
                    }
                }

            }
        }
    }

    sortValidNode(digit);

    return digit;
}

void sortValidNode(int digit) {
    struct PossiblePoints temp;
    for (int i = 0; i < digit - 1; ++i) {
        for (int j = i + 1; j < digit; ++j) {
            if (possiblePoints[i].count < possiblePoints[j].count) {
                temp = possiblePoints[i];
                possiblePoints[i] = possiblePoints[j];
                possiblePoints[j] = temp;
            }
        }
    }
}

int nodeInput(char input[], int *m, int *n) {

    if (strlen(input) != 2) {
        printf("\n** Error! Invalid Format **\n");
        return 0;
    }

    if (input[0] >= 97 && input[0] <= 104 && input[1] >= 49 && input[1] <= 56) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                // convert to array indexing
                if (board.node[i][j].letter == input[0] && board.node[i][j].digit == (input[1] - 48)) {
                    *m = i;
                    *n = j;
                    return 1;
                }
            }
        }
    }

    printf("\n** Error! Invalid Position **\n");
    return 0;
}

void scoreCalculate() {
    board.black.score = 0;
    board.white.score = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board.node[i][j].disk == 'B') {
                board.black.score = board.black.score + 1;
            } else if (board.node[i][j].disk == 'W') {
                board.white.score = board.white.score + 1;
            }
        }
    }
}

void setUpGame() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board.node[i][j].letter = (char) (j + 97);
            board.node[i][j].digit = i + 1;
            board.node[i][j].disk = ' ';
        }
    }
    // set starting positions of disks
    board.node[3][3].disk = 'W';
    board.node[3][4].disk = 'B';
    board.node[4][4].disk = 'W';
    board.node[4][3].disk = 'B';

}

void printTable() {

    printf("\n----------------------------------------------------\n");
    printf("Score: %10s (Black) %2d : %2d %10s (White)", board.black.player, board.black.score, board.white.score,
           board.white.player);
    printf("\n----------------------------------------------------\n");

    printf("    a   b   c   d   e   f   g   h");
    printf("\n   --------------------------------");
    for (int i = 0; i < 8; ++i) {
        printf("\n%d |", i + 1);
        for (int j = 0; j < 8; ++j) {
            printf(" %c |", board.node[i][j].disk);
        }
        printf("\n   --------------------------------");
    }
}