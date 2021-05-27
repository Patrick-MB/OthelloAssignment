//-------------------------------------------
// Created by Patrick Mbanusi on 05/05/2021.
//-------------------------------------------

#include "game.h"

int main() {

    // Initialise game board and other components
    setUpGame();

    printf("\n* * * * * * * * * * * * * * *\n");
    printf ("*    WELCOME TO OTHELLO     * ");
    printf("\n* * * * * * * * * * * * * * *\n\n");


    // Input for players names
    printf("Enter Player 1's name: ");
    scanf("%s", board.black.player);

    printf("Enter Player 2's name: ");
    scanf("%s", board.white.player);

    // Calculating initial score and printing starting board
    scoreCalculate();
    printTable();

    // Starting game loop
    do {

        int flag, m, n;

        /*
         * checking for valid moves for both players
         * If no further moves are available for both players, the game will
         * end
         */
        int blackValid = validMoves('W');
        int whiteValid = validMoves('B');

        if (blackValid == 0 && whiteValid == 0) {
            break;
        }

        blackValid = validMoves('W');

        // Move for black player
        do {
            flag = 0;
            char input[10];

            // ask for input move
            printf("\n%s (Black): Enter position to place disk : ", board.black.player);
            scanf("%s", input);

            if (blackValid > 0) {

                // checking format of input
                flag = nodeInput(input, &m, &n);
                if (flag != 0) {

                    flag = 0;
                    // checking if input is valid to move
                    for (int i = 0; i < blackValid; ++i) {

                        if (possiblePoints[i].letter == input[0] && possiblePoints[i].digit == (input[1] - 48)) {

                            // moving the disk
                            moveDisk(i, 'B', m, n);

                            // calculating new score
                            scoreCalculate();

                            flag = 1;

                        }
                    }
                    if (flag == 0) {
                        printf("\n** Error - Not A Valid Move **\n");
                    }
                    else{
                        printTable();
                    }
                }
            }
                // if and only if there is no valid move a player can pass
            else {
                if (strcmp(input, "p") == 0) {
                    flag = 1;
                    printTable();
                } else {
                    printf("\n** Error - Not A Position Or Pass **\n");
                }
            }
        } while (flag == 0);

        // same above procedure for white player
        whiteValid = validMoves('B');
        do {
            flag = 0;
            char input[10];
            printf("\n%s (White): Enter position to place disk : ", board.white.player);
            scanf("%s", input);
            if (whiteValid > 0) {

                flag = nodeInput(input, &m, &n);

                if (flag != 0) {

                    flag = 0;
                    for (int i = 0; i < whiteValid; ++i) {

                        if (possiblePoints[i].letter == input[0] && possiblePoints[i].digit == (input[1] - 48)) {
                            moveDisk(i, 'W', m, n);
                            scoreCalculate();
                            flag = 1;
                        }
                    }

                    if (flag == 0) {
                        printf("\n** Error - Not A Valid Move **\n");
                    }
                    else{
                        printTable();
                    }
                }

            } else {
                if (strcmp(input, "p") == 0) {
                    flag = 1;
                    printTable();
                } else {
                    printf("\n** Error - Not A Position Or Pass **\n");
                }
            }
        } while (flag == 0);

    } while (1);


    // printing final table
    printResult();

    // printing result and writing to file
    printTable();

    return 0;
}
