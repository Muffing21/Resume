#include "names.h"

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED           2021
#define DEFAULTPLAYERS 2
int playerPoints[10];

int player_turn(int x, int y) { // function for calculating the player turn
    int answer = x % y;
    return answer;
}

typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

int main(void) {

    int input_num_players = 0;
    printf("How many players? ");
    scanf("%d", &input_num_players); //check later on how to check for integers only
    if ((input_num_players < 2) || (input_num_players > 10)) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        input_num_players = DEFAULTPLAYERS;
    }

    long int inputSeed;
    printf("Random seed: ");
    long int data_read = scanf("%ld", &inputSeed);

    if (data_read == false) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        inputSeed = SEED;
    }
    if (inputSeed < 0 || inputSeed > UINT_MAX) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        inputSeed = SEED;
    }

    srandom(inputSeed);

    bool winner = false;

    int player_counter = 0; //initializing player count, always start at 0

    printf("%s rolls the pig... ", names[player_counter]); //always print the initial player

    while (
        true) { //no specific condition, the loop will alternate players and play the game till someone wins

        int randomRoll = random() % 7; //make a pseudo random roll for the pig
        int rollResult = pig[randomRoll];
        int players_turn = player_turn(player_counter,
            input_num_players); //player can be decided like randomRoll, say input_num_players is 2, 0 mod 2 = 0, 1 mod 2 = 1, 2 mod 2 = 0

        if (rollResult == RAZORBACK) {
            playerPoints[players_turn] += 10;
            printf("pig lands on back ");
            if (playerPoints[players_turn] >= 100) {
                winner = true;
                goto WIN;
            }
            continue;
        }

        if (rollResult == TROTTER) {
            playerPoints[players_turn] += 10;
            printf("pig lands upright ");
            if (playerPoints[players_turn] >= 100) {
                winner = true;
                goto WIN;
            }
            continue;
        }

        if (rollResult == SNOUTER) {
            playerPoints[players_turn] += 15;
            printf("pig lands on snout ");
            if (playerPoints[players_turn] >= 100) {
                winner = true;
                goto WIN;
            }
            continue;
        }

        if (rollResult == JOWLER) {
            playerPoints[players_turn] += 5;
            printf("pig lands on ear ");
            if (playerPoints[players_turn] >= 100) {
                winner = true;
                goto WIN;
            }
            continue;
        }

        if (rollResult == SIDE) {
            printf("pig lands on side \n");
            player_counter += 1;
            int players_turn = player_turn(player_counter, input_num_players);
            printf("%s rolls the pig... ", names[players_turn]);
            continue;
        }

    WIN:
        if (winner == true) {
            printf("\n%s wins with %d points!\n", names[players_turn], playerPoints[players_turn]);
            break;
        }
    }
    return 0;
}
