#include "names.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED           2021
#define DEFAULTPLAYERS 2
int playerPoints[10];


typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

int main(void) {
    
    int input_num_players = 0; 
    printf("How many players? ");
    scanf("%d", &input_num_players); //check later on how to check for integers only
    if (input_num_players < 2 || input_num_players > 10){
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        input_num_players = DEFAULTPLAYERS;
    }

    int inputSeed;
    printf("Random seed: ");
    int data_read = scanf("%d", &inputSeed);
    
    if (data_read != 1) { //check if scan fail, change to default
     fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
     inputSeed = SEED;
    }
    
    srandom(inputSeed);


  
    int randomRoll = random() % 7;  //make a pseudo random roll for the pig
        
    Position rollResult = pig[randomRoll]; //result of new player's result stored
      
      
      
      int player_counter = 0;
      
      int player = player_counter % input_num_players;
       
      printf("\n%s rolls the pig... ", names[player]);
     	while (true) {
     	        
                if (rollResult == RAZORBACK){
                 playerPoints[player] += 10;
                 if (playerPoints[player] >= 100){
                  printf("\n%s wins with %d points!\n", names[player],playerPoints[player]);
                  return 0;
                } 
                 printf("pig lands on back ");
                 randomRoll = rand() % 7;
                 rollResult = pig[randomRoll];
   }
               if (rollResult == TROTTER){
                playerPoints[player] += 10;
                if (playerPoints[player] >= 100){
                 printf("\n%s wins with %d points!\n", names[player], playerPoints[player]);
                 return 0;

                }
                printf("pig lands upright ");
                randomRoll = rand() % 7;
                rollResult = pig[randomRoll];
   }
               if (rollResult == SNOUTER){
                playerPoints[player] += 15;
                if (playerPoints[player] >= 100){
                 printf("\n%s wins with %d points!\n", names[player], playerPoints[player]);
                 return 0;

                } 
                printf("pig lands on snout ");
                randomRoll = rand() % 7;
                rollResult = pig[randomRoll];
   }
               if (rollResult == JOWLER){
                playerPoints[player] += 5;
                if (playerPoints[player] >= 100){
                printf("\n%s wins with %d points!\n", names[player], playerPoints[player]);
                return 0;
                } 
                printf("pig lands on ear ");
                randomRoll = rand() % 7;
                rollResult = pig[randomRoll];
   }
               if (rollResult == SIDE){
                player_counter += 1;
                int player = player_counter % input_num_players;
                printf("\n%s rolls the pig... ", names[player]);
                rollResult = pig[randomRoll];
               }
        
 }
}

